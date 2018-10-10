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

constexpr auto dev_id    = DeviceID::X_RSW60A_E03; // Change to fit your system
constexpr auto port_path = "/dev/ttyUSB0";         // Change to fit your system.
auto           port      = std::make_shared<serial::Serial>(port_path, 115200, serial::Timeout::simpleTimeout(100));

TEST_CASE("Create controller and discover at least 1 device.")
{
  Controller control(port);
  REQUIRE(control.discover() > 0);
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
  auto dut = control.make_device_from_id(dev_id);
  REQUIRE(dut != nullptr);

  const auto max           = dut->get_max();
  const auto min           = dut->get_min();
  const auto home_pos      = dut->get_home_position();
  const auto mid_point     = dut->real_to_pos(180.0);
  const auto pos_increment = dut->real_to_pos(10.0);
  const auto default_speed = dut->get_velocity();

  REQUIRE(max > min);
  REQUIRE(dut->real_to_pos(0.0) == 0);

  SECTION("home goes to home_pos location.")
  {
    dut->home();
    dut->wait_until_idle();
    REQUIRE(dut->get_position() == 0);
  }

  SECTION("Moving to 90 deg. ")
  {
    dut->move_to_real(90.0);
    dut->wait_until_idle();
    REQUIRE(dut->get_position() == dut->real_to_pos(90.0));
  }

  SECTION("Moving to absolute. ")
  {
    dut->move_absolute(mid_point);
    dut->wait_until_idle();
    REQUIRE(dut->get_position() == mid_point);
  }

  SECTION("Move relative, positive")
  {
    dut->move_relative(pos_increment);
    dut->wait_until_idle();
    REQUIRE(dut->get_position() == (mid_point + pos_increment));
  }

  SECTION("Move relative, negative")
  {
    dut->move_relative(pos_increment * -1);
    dut->wait_until_idle();
    REQUIRE(dut->get_position() == (mid_point));
  }

  SECTION("Move at half max velocity, positive.")
  {
    dut->home();
    dut->wait_until_idle();

    const auto vel = dut->get_max_velocity() / 2;
    dut->move_velocity(vel);
    while (dut->get_position() < mid_point)
      ;
    dut->stop();
  }

  SECTION("Move at half max velocity, negative.")
  {
    dut->move_to_real(360.0);
    dut->wait_until_idle();

    const auto vel = dut->get_max_velocity() * -1 / 2;
    dut->move_velocity(vel);
    while (dut->get_position() > mid_point)
      ;
    dut->stop();
  }

  SECTION("Speed test, move at half max speed. ")
  {
    dut->home();
    dut->wait_until_idle();

    dut->set_velocity(dut->get_max_velocity() / 2);
    dut->move_to_real(180.0);
    dut->wait_until_idle();

    // Restore default speed.
    dut->set_velocity(default_speed);
  }
}

TEST_CASE("Park up stages.")
{
  Controller control(port);
  control.discover();
  control.broadcast(Command::Home);
}
