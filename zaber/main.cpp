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
    options.add_options()("t,timeout", "Timeout level (ms)", cxxopts::value<int>()->default_value("100"));
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
    using namespace zaber;
    Controller control(port);

    m_log->info("{} zaber devices found. ", control.discover());

    {
      /* Rotary test. */
      auto rotary = control.make_device(DeviceID::X_RSW60A_E03);
      rotary->home();
      rotary->wait_until_idle();
      rotary->move_to_location(30.0);
      rotary->wait_until_idle();
      rotary->move_to_location(180.0);
      rotary->wait_until_idle();
      rotary->move_to_location(120.0);
      rotary->wait_until_idle();
      rotary->move_to_location(0.0);
      rotary->wait_until_idle();
      rotary->home();
    }
    {
      /* Linear test. */
      auto linear = control.make_device(DeviceID::X_LSQ300B_E01);
      // linear->setup();
      linear->home();
      // linear->wait_until_idle();
      // linear->move_to_location(30e-3); /*30mm*/
      // linear->wait_until_idle();
      // linear->move_to_location(0.0);
      // linear->wait_until_idle();
    }
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
