#define CATCH_CONFIG_MAIN

#include <memory>
#include <string>

#include "serial/serial.h"
#include "ultra_flex/ultra_flex.hpp"
#include <catch.hpp>
#include <spdlog/spdlog.h>

static auto m_log = spdlog::stdout_color_mt("unit_test");
#define CONNECTED 1

TEST_CASE("HeaterControl should be created without error")
{
  using namespace ultra_flex;

  spdlog::set_level(spdlog::level::trace);
  HeaterControl h;

  // By default the heater is off when created.
  REQUIRE(h.is_on() == false);
}

TEST_CASE("::make_packet creates correct messages.")
{
  using namespace ultra_flex;

  spdlog::set_level(spdlog::level::trace);

  // By default the heater is off when created.
  REQUIRE(HeaterControl::make_packet(Command::WriteData, '3', "5164") == "S3C516467K");
  REQUIRE(HeaterControl::make_packet(Command::Off) == "S3347K");
  {
    const std::string test_message = "5164";
    CHECK_THROWS(HeaterControl::is_checksum_valid(test_message));
  }
  {
    const std::string test_message = "S3C516467K";
    REQUIRE(HeaterControl::is_checksum_valid(test_message) == true);
  }

  {
    // corrupted message
    const std::string test_message = "S3Cs16467K";
    REQUIRE(HeaterControl::is_checksum_valid(test_message) == false);
  }
}
TEST_CASE("::on command formating")
{
  using namespace ultra_flex;
  spdlog::set_level(spdlog::level::trace);

  const size_t     on_time_100ms = 100;
  const Mulitplier mulitpler     = Mulitplier::KILO;

  auto on_time = fmt::format("{:03x}{}", on_time_100ms, static_cast<char>(mulitpler));
  auto cmd     = HeaterControl::make_packet(Command::On, '3', on_time);

  m_log->info("On time format: \"{}\"", on_time);
  m_log->info("cmd: \"{}\"", cmd);
}

TEST_CASE("get_command works correctly.")
{
  using namespace ultra_flex;
  auto cmd = HeaterControl::make_packet(Command::WriteData, '3', "5164");
  REQUIRE(HeaterControl::get_command(cmd) == Command::WriteData);
}

TEST_CASE("Get payload works correctly.")
{
  using namespace ultra_flex;

  spdlog::set_level(spdlog::level::trace);
  SECTION("Basic examle")
  {
    auto packet = HeaterControl::make_packet(Command::GetError, '4', "0100");
    m_log->debug("Packet made: {}", packet);
    auto payload = HeaterControl::get_payload(packet);
    REQUIRE(payload == "0100");
    REQUIRE(HeaterControl::parse_numeric<uint8_t>(payload) == 1);
    REQUIRE(HeaterControl::parse_numeric<uint8_t>(payload, 1) == 0);
  }
}

#if CONNECTED
TEST_CASE("Messages can be sent and recieved")
{
  using namespace ultra_flex;

  spdlog::set_level(spdlog::level::trace);
  auto          heater_serial = std::make_shared<serial::Serial>("/dev/serial0", 9600, serial::Timeout::simpleTimeout(1000));
  HeaterControl heater(heater_serial);

  auto status = heater.get_status();
  m_log->info("Heater status: 0x{:x}", status);
}
#endif
