/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 04-10-2018
 */

#include "zaber/zaber_rotary.h"

namespace zaber
{

Rotary::Rotary(Controller* const ctrl, const Address address, const DeviceID id) : Device(ctrl, address, id)
{
  m_log->trace("{} id = {}, at {}", __FUNCTION__, static_cast<uint>(m_id), m_address);
}
Rotary::~Rotary() {}

void Rotary::move_to_location(const double real_location) { m_log->trace("{} {}deg", __FUNCTION__, real_location); }

} // namespace zaber
