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

  const auto max      = linear->get_max();
  const auto min      = linear->get_min();
  const auto home_pos = linear->get_home_position();

  REQUIRE(max > min);

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

  SECTION("move_min goes to min location.")
  {
    linear->move_min();
    linear->wait_until_idle();
    REQUIRE(linear->get_position() == min);
  }
}
