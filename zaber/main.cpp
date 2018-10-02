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
  spdlog::set_level(spdlog::level::trace);

  m_log->info("Zaber deivces: {}", zaber::Device::device_count());
  {
    zaber::Device stage1(1u);

    m_log->info("Zaber deivces: {}", zaber::Device::device_count());

    stage1.emergency_stop();
    stage1.help();
    stage1.help("home");
    stage1.home();
    stage1.get<int>("some_param_nameake");
  }
  m_log->info("Zaber deivces: {}", zaber::Device::device_count());

  /* TODO: Implement example. */
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
