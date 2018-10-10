#define CATCH_CONFIG_MAIN

#include <memory>
#include <string>

#include "serial/serial.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <catch.hpp>

#include "zaber/zaber.h"

using namespace zaber;
static auto m_log = spdlog::stdout_color_mt("unit_test");

constexpr auto dev_id    = DeviceID::X_LSQ300B_E01; // Change to fit your system
constexpr auto port_path = "/dev/ttyUSB0";          // Change to fit your system.
auto           port      = std::make_shared<serial::Serial>(port_path, 115200, serial::Timeout::simpleTimeout(100));

TEST_CASE("Create controller and discover at least 1 device.")
{
  Controller control(port);
  REQUIRE(control.discover() > 1);
}

TEST_CASE("Non-existant device throws.")
{
  Controller control(port);
  REQUIRE_THROWS_WITH(control.make_device_from_id(static_cast<DeviceID>(0)), Catch::Contains("Device not found"));
}

TEST_CASE("Expected device is found and works correctly.")
{
  Controller control(port);
  control.discover();
  auto linear = control.make_device_from_id(dev_id);
  REQUIRE(linear != nullptr);

  const auto max           = linear->get_max();
  const auto min           = linear->get_min();
  const auto mid_point     = (max - min) / 2;
  const auto pos_increment = mid_point / 2;
  const auto home_pos      = linear->get_home_position();

  REQUIRE(max > min);
  REQUIRE(mid_point > min);
  REQUIRE(mid_point < max);

  SECTION("home goes to home_pos location.")
  {
    linear->home();
    linear->wait_until_idle();
    REQUIRE(linear->get_position() == home_pos);
  }

  SECTION("move_max goes to max location.")
  {
    linear->move_max();
    linear->wait_until_idle();
    REQUIRE(linear->get_position() == max);
  }

  SECTION("Moving to half way point, pos. ")
  {
    linear->move_absolute(mid_point);
    linear->wait_until_idle();
    REQUIRE(linear->get_position() == mid_point);
  }

  SECTION("move_min goes to min location.")
  {
    linear->move_min();
    linear->wait_until_idle();
    REQUIRE(linear->get_position() == min);
  }
  SECTION("Moving to half way point, real. ")
  {
    linear->move_to_location(linear->pos_to_real(mid_point));
    linear->wait_until_idle();
    REQUIRE(linear->get_position() == mid_point);
  }

  SECTION("Move relative, positive")
  {
    linear->move_relative(pos_increment);
    linear->wait_until_idle();
    REQUIRE(linear->get_position() == (mid_point + pos_increment));
  }

  SECTION("Move relative, negative")
  {
    linear->move_relative(pos_increment * -1);
    linear->wait_until_idle();
    REQUIRE(linear->get_position() == (mid_point));
  }

  SECTION("Move at half max velocity, positive.")
  {
    linear->home();
    linear->wait_until_idle();

    const auto vel = linear->get_max_velocity() / 2;
    linear->move_velocity(vel);
    while (linear->get_position() < mid_point)
      ;
    linear->stop();
  }
  SECTION("Move at half max velocity, negative.")
  {
    linear->move_max();
    linear->wait_until_idle();

    const auto vel = linear->get_max_velocity() * -1 / 2;
    linear->move_velocity(vel);
    while (linear->get_position() > mid_point)
      ;
    linear->stop();
  }
}

TEST_CASE("Park up stages.")
{
  Controller control(port);
  control.discover();
  control.broadcast(Command::Home);
}
