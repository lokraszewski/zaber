/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 04-10-2018
 */
#pragma once
#include "zaber/zaber_device.h"
namespace zaber
{

class Rotary : public Device
{
public:
  using angle_t = double;

  Rotary(Controller* const ctrl, const Address address = 1, const DeviceID id = DeviceID::UNKNOWN);
  Rotary() = delete;
  virtual ~Rotary();

  virtual void move_to_location(const double real_location) override;
};
} // namespace zaber
