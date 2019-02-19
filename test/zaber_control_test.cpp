#define CATCH_CONFIG_MAIN

#include <memory>
#include <string>

#include "serial/serial.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <catch2/catch.hpp>

#include "zaber/zaber.h"

using namespace zaber;
static auto m_log = spdlog::stdout_color_mt("unit_test");

TEST_CASE("Create default controller with no serial port.")
{
  Controller control;
  REQUIRE_THROWS(control.set_port(nullptr));
}
