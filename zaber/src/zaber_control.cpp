/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 04-10-2018
 */

#include "zaber/zaber_control.h"
#include "zaber/zaber_device.h"
#include "zaber/zaber_rotary.h"

namespace zaber
{

std::shared_ptr<spdlog::logger> Controller::m_log = spdlog::stdout_color_mt("zaber");

Controller::Controller(const Port port) : m_port(port)
{
  m_log->trace("{}", __FUNCTION__);
  if (m_port == nullptr)
  {
    auto err = "Serial port cannot be null!";
    m_log->error(err);
    throw std::invalid_argument(err);
  }
}

Controller::~Controller() {}

std::unique_ptr<Device> Controller::make_device(const DeviceID id)
{
  const auto dev_addr = m_dev_map.at(static_cast<uint>(id));
  // const auto err = fmt::format("Device ID {} not found.", static_cast<uint>(id));
  // m_log->error(err);
  // throw std::runtime_error(err);
  //
  m_log->trace("{} id = {}, at {}", __FUNCTION__, static_cast<uint>(id), dev_addr);

  switch (id)
  {
  case DeviceID::X_RSW60A_E03:
    m_log->trace("Creating rotary device ({})", static_cast<uint>(id));
    return std::make_unique<Rotary>(this, dev_addr, id);
  default:
    m_log->warn("Unknown device id ({}), creating defeault device.", static_cast<uint>(id));
    return std::make_unique<Device>(this, dev_addr, id);
  }
}
} // namespace zaber
