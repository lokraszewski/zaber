/*
 * @Author: Lukasz
 * @Date:   02-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 02-10-2018
 */
#pragma once

#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/spdlog.h>

namespace zaber
{
namespace ascii
{

enum Protocol
{
  StartOfCommand = '/',
  EndOfCommand   = '\n',
};

class Messenger
{
public:
  Messenger() {}
  ~Messenger() {}
};

} // namespace ascii
} // namespace zaber
