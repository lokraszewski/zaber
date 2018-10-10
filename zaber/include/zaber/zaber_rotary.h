/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 10-10-2018
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

  virtual void   move_to_real(const double real_location) override;
  virtual double pos_to_real(const int pos) const override;
  virtual int    real_to_pos(const double real) const override;
  virtual void   setup(void) override;

private:
  size_t m_limit_cycle_dist;
};
} // namespace zaber
