/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 04-10-2018
 */

#include "zaber/zaber_rotary.h"

namespace zaber
{

Rotary::Rotary(Controller* const ctrl, const Address address, const DeviceID id) : Device(ctrl, address, id), m_limit_cycle_dist(0)
{
  m_log->trace("{} id = {}, at {}", __FUNCTION__, static_cast<uint>(m_id), m_address);
}
Rotary::~Rotary() {}

void Rotary::move_to_location(const double real_location)
{
  m_log->trace("{} {}deg", __FUNCTION__, real_location);

  /* We have to translate this to */
}

void Rotary::setup(void)
{
  // m_limit_cycle_dist = get_setting<uint>("limit.cycle.dist");

  // m_log->debug("m_limit_cycle_dist : {}", m_limit_cycle_dist);
  // For rotary stages we need to find the scaling factor.
}

} // namespace zaber
