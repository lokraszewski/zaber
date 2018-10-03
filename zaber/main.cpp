#include <cstdio>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "serial/serial.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <cxxopts.hpp>
#include <spdlog/spdlog.h>

#include "zaber/zaber.h"
#include "zaber/zaber_ascii.h"

using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::vector;

static auto m_log = spdlog::stdout_color_mt("app");

int run(int argc, char **argv)
{

  cxxopts::Options options("MyProgram", "One line description of MyProgram");
  {
    options.add_options()("h,help", "Show help.");
    options.add_options()("d,debug", "Debug level output.", cxxopts::value<int>()->default_value("2"));
    options.add_options()("p,port", "Serial port path.", cxxopts::value<std::string>()->default_value("/dev/ttyUSB0"));
    options.add_options()("t,timeout", "Timeout level (ms)", cxxopts::value<int>()->default_value("10"));
  }

  auto result = options.parse(argc, argv);
  spdlog::set_level(static_cast<spdlog::level::level_enum>(result["debug"].as<int>()));

  if (result["help"].count())
  {
    std::cout << options.help();
    return 0;
  }

  const auto port_path     = result["port"].as<std::string>();
  const auto timeout_level = result["timeout"].as<int>();

  m_log->info("Creating port: {}", port_path);
  auto port = std::make_shared<serial::Serial>(port_path, 115200, serial::Timeout::simpleTimeout(timeout_level));
  m_log->info("Port {} open.", port->isOpen() ? "" : "not");

  {
    zaber::Device stage(port);
    m_log->info("is_connected : {}", stage.is_connected());
    m_log->info("ID: {}", stage.get_device_id());

    stage.home();
    m_log->info("is_busy : {}", stage.is_busy());

    while (stage.is_busy()) m_log->info("Position : {}", stage.get_position());
    ;

    m_log->info("Position : {}", stage.get_position());

    // stage.move_min();
    // while (stage.is_busy()) m_log->info("Position : {}", stage.get_position());
    // ;
    // m_log->info("Position : {}", stage.get_position());

    // stage.move_max();
    // while (stage.is_busy()) m_log->info("Position : {}", stage.get_position());
    // ;
    // m_log->info("Position : {}", stage.get_position());

    // m_log->info("Stage at home", stage.is_busy());

    // stage.emergency_stop();
    // stage.help("home");
    // stage.home();
    // stage.get<int>("some_param_nameake");
    // stage.move_absolute(10);
    // stage.move_relative(10);
    // stage.move_min();
    // stage.move_max();
  }

  return 0;
}

int main(int argc, char **argv)
{
  m_log->info("{}", __FUNCTION__);
  try
  {
    return run(argc, argv);
  }
  catch (exception &e)
  {
    cerr << "Unhandled Exception: " << e.what() << endl;
  }
}
