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
