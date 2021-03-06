/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 18-02-2019
 */

#include "zaber/zaber_control.h"
#include "zaber/zaber_device.h"
#include "zaber/zaber_linear.h"
#include "zaber/zaber_rotary.h"

namespace zaber
{

std::shared_ptr<spdlog::logger> Controller::m_log = spdlog::stdout_color_mt("zaber");

Controller::Controller(const Port port) : m_port(port) { m_log->trace("{}", __FUNCTION__); }

Controller::Controller() : m_port(nullptr) { m_log->trace("{}", __FUNCTION__); }

Controller::~Controller() {}

std::unique_ptr<Device> Controller::make_device(const DeviceID id, const Address addr)
{
  m_log->trace("{} id = {}, at {}", __FUNCTION__, static_cast<uint>(id), addr);

  switch (id)
  {
  case DeviceID::X_LSQ075A:
  case DeviceID::X_LSQ075A_E01:
  case DeviceID::X_LSQ075B:
  case DeviceID::X_LSQ075B_E01:
  case DeviceID::X_LSQ075D:
  case DeviceID::X_LSQ075D_E01:
  case DeviceID::X_LSQ150A:
  case DeviceID::X_LSQ150A_E01:
  case DeviceID::X_LSQ150B:
  case DeviceID::X_LSQ150B_E01:
  case DeviceID::X_LSQ150D:
  case DeviceID::X_LSQ150D_E01:
  case DeviceID::X_LSQ300A:
  case DeviceID::X_LSQ300A_E01:
  case DeviceID::X_LSQ300B:
  case DeviceID::X_LSQ300B_E01:
  case DeviceID::X_LSQ300D:
  case DeviceID::X_LSQ300D_E01:
  case DeviceID::X_LSQ450A:
  case DeviceID::X_LSQ450A_E01:
  case DeviceID::X_LSQ450B:
  case DeviceID::X_LSQ450B_E01:
  case DeviceID::X_LSQ450D:
  case DeviceID::X_LSQ450D_E01:
  case DeviceID::X_LSQ600A:
  case DeviceID::X_LSQ600A_E01:
  case DeviceID::X_LSQ600B:
  case DeviceID::X_LSQ600B_E01:
  case DeviceID::X_LSQ600D:
  case DeviceID::X_LSQ600D_E01:
    m_log->trace("Creating linear device ({})", static_cast<uint>(id));
    return std::make_unique<Linear>(this, addr, id);
  case DeviceID::X_RSW60A:
  case DeviceID::X_RSW60A_E03:
  case DeviceID::X_RSW60A_S:
  case DeviceID::X_RSW60A_SE03:
  case DeviceID::X_RSW60A_SV1:
  case DeviceID::X_RSW60A_SV2:
  case DeviceID::X_RSW60C:
  case DeviceID::X_RSW60C_E03:
  case DeviceID::X_RSW60C_S:
  case DeviceID::X_RSW60C_SE03:
  case DeviceID::X_RSW60C_SV1:
  case DeviceID::X_RSW60C_SV2:
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

  {
    auto err = "Device not found!";
    m_log->error(err);
    throw std::runtime_error(err);
  }
}

} // namespace zaber
