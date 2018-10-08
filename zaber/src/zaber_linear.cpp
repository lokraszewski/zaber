/*
 * @Author: Lukasz
 * @Date:   08-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 08-10-2018
 */
/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 05-10-2018
 */

#include "zaber/zaber_linear.h"

namespace zaber
{

Linear::Linear(Controller* const ctrl, const Address address, const DeviceID id) : Device(ctrl, address, id)
{
  m_limit_max = get_setting<uint>("limit.max");
  m_limit_min = get_setting<uint>("limit.min");
  m_range     = get_range(id);
  m_log->trace("{} id = {}, at {}", __FUNCTION__, static_cast<uint>(m_id), m_address);
  m_log->debug("Movement limits = [{},{}] steps. Range: {}m", m_limit_min, m_limit_max, m_range);
}
Linear::~Linear() {}

void Linear::move_to_location(const double real_location)
{
  m_log->trace("{} {}m", __FUNCTION__, real_location);

  /* The range of movement is m_limit_max - m_limit_min, so the location we need to move to is ((real_location/m_range) * (m_limit_max -
   * m_limit_min)) + m_limit_min
   */
  const auto microsteps = ((real_location / m_range) * (m_limit_max - m_limit_min)) + m_limit_min;
  m_log->trace("{} microsteps", microsteps);

  move_absolute(microsteps);
  /* We have to translate this to */
}

} // namespace zaber
