/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 08-10-2018
 */

#include "zaber/zaber_control.h"
#include "zaber/zaber_device.h"
#include "zaber/zaber_linear.h"
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

std::unique_ptr<Device> Controller::make_device(const DeviceID id, const Address addr)
{
  m_log->trace("{} id = {}, at {}", __FUNCTION__, static_cast<uint>(id), addr);

  switch (id)
  {
  case DeviceID::X_LSQ300B_E01:
    m_log->trace("Creating linear device ({})", static_cast<uint>(id));
    return std::make_unique<Linear>(this, addr, id);
  case DeviceID::X_RSW60A_E03:
    m_log->trace("Creating rotary device ({})", static_cast<uint>(id));
    return std::make_unique<Rotary>(this, addr, id);
  default:
    m_log->warn("Unknown device id ({}), creating defeault device.", static_cast<uint>(id));
    return std::make_unique<Device>(this, addr, id);
  }
}

std::unique_ptr<Device> Controller::make_device_from_address(const Address addr)
{
  const auto id = m_dev_map.at(static_cast<uint>(addr));
  return make_device(static_cast<DeviceID>(id), addr);
}

std::unique_ptr<Device> Controller::make_device_from_id(const DeviceID id)
{
  for (auto &device : m_dev_map)
  {
    if (device.second == static_cast<uint>(id))
    {
      return make_device(id, static_cast<Address>(device.first));
    }
  }

  // Maybe throw here since we would expect a device  to be found
  return nullptr;
}

} // namespace zaber
