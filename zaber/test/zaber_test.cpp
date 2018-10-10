#define CATCH_CONFIG_MAIN

#include <memory>
#include <string>

#include "serial/serial.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <catch.hpp>

#include "zaber/zaber.h"

static auto m_log = spdlog::stdout_color_mt("unit_test");
using namespace zaber;

TEST_CASE("Argument formatting.")
{
  m_log->info("{}", Controller::make_arg_string("foo"));
  m_log->info("{}", Controller::make_arg_string("foo", "bar"));
  m_log->info("{}", Controller::make_arg_string(42));
  m_log->info("{}", Controller::make_arg_string(42, 3, 5));
  m_log->info("{}", Controller::make_arg_string(42, 3, 5, "foo"));
}
