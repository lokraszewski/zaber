#define CATCH_CONFIG_MAIN

#include <memory>
#include <string>

#include "serial/serial.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <catch.hpp>

static auto m_log = spdlog::stdout_color_mt("unit_test");

TEST_CASE("Test1") {}
