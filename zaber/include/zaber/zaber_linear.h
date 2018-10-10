/*
 * @Author: Lukasz
 * @Date:   08-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 10-10-2018
 */
#pragma once
#include "zaber/zaber_device.h"
namespace zaber
{

class Linear : public Device
{
public:
  Linear(Controller* const ctrl, const Address address = 1, const DeviceID id = DeviceID::UNKNOWN);
  Linear() = delete;
  virtual ~Linear();

  virtual void move_to_location(const double real_location) override;

  void set_range(const double range) { m_range = range; }

private:
  size_t m_limit_max;
  size_t m_limit_min;
  double m_range;
};
} // namespace zaber
