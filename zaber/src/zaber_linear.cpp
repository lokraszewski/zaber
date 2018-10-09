/*
 * @Author: Lukasz
 * @Date:   08-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 09-10-2018
 */

#include "zaber/zaber_linear.h"

namespace zaber
{

/**
 * \date       09-Oct-2018
 * \brief      Constructs the object.
 *
 * \param      ctrl     Pointer to zaber controller.
 * \param[in]  address  Device address.
 * \param[in]  id       Device ID.
 *
 */
Linear::Linear(Controller* const ctrl, const Address address, const DeviceID id) : Device(ctrl, address, id)
{
  /* We cache the limits of the stage to save time with move calculations. Be
   * warned, this setting can be written by the user which invalidates these
   * cached values. */
  m_limit_max = get_setting<uint>("limit.max");
  m_limit_min = get_setting<uint>("limit.min");

  // The range is only returned for known IDs of stages. For unknown range use
  // set_range(); This is only neccessary for real location movement.
  m_range = get_range(id);
  if (m_range == 0.0)
  {
    m_log->warn("Device ID {} has unspecified range!", static_cast<uint>(m_id));
  }
  m_log->trace("{} id = {}, at {}", __FUNCTION__, static_cast<uint>(m_id), m_address);
  m_log->debug("Movement limits = [{},{}] steps. Range: {}m", m_limit_min, m_limit_max, m_range);
}

/**
 * \date       09-Oct-2018
 * \brief      Destroys the object.
 *
 */
Linear::~Linear() {}

/**
 * \date       09-Oct-2018
 * \brief      Moves to a real location in SI meters.
 *
 * \param[in]  real_location  The real location
 *
 * \details
 * \warning    Requires m_range to be known.
 */
void Linear::move_to_location(const double real_location)
{
  /* The range of movement is m_limit_max - m_limit_min, so the location we need
   * to move to is ((real_location/m_range) * (m_limit_max - m_limit_min)) +
   * m_limit_min.
   */
  if (m_range == 0.0)
  {
    const auto err = fmt::format("Device ID {} has unspecified range!", static_cast<uint>(m_id));
    m_log->error(err);
    throw std::runtime_error(err);
  }
  const auto microsteps = ((real_location / m_range) * (m_limit_max - m_limit_min)) + m_limit_min;
  m_log->trace("{} {}m, {} microsteps", __FUNCTION__, real_location, microsteps);
  move_absolute(microsteps);
}

} // namespace zaber
