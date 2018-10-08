/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 08-10-2018
 */

#include "zaber/zaber_device.h"
#include "zaber/zaber_control.h"
namespace zaber
{

double get_range(const DeviceID id)
{
  switch (id)
  {
  case DeviceID::X_LSQ300B_E01: return 300e-3;
  default: return 0e0;
  }
}

std::shared_ptr<spdlog::logger> Device::m_log = spdlog::stdout_color_mt("device");

Device::Device(Controller* const ctrl, const Address address, const DeviceID id) : m_ctrl(ctrl), m_address(address), m_id(id)
{

  m_log->trace("{} id = {}, at {}", __FUNCTION__, static_cast<uint>(m_id), m_address);

  if (ctrl == nullptr)
  {
    m_log->error("Controller cannot be null!");
    throw std::invalid_argument("Controller cannot be null!");
  }
}

Device::~Device() {}

bool Device::is_busy(void) const { return ((command(Command::None))->status == Status::BUSY); }

void Device::wait_until_idle(void) const
{
  while (is_busy())
    ;
}

/**
 \author     lokraszewski
 \date       02-Oct-2018
 \brief      Moves the axis to the home position.

 \details    The axis is moved towards the home position(closest to the motor
             generally) at the lesser of the limit.approach .maxspeed and
             maxspeed settings.Once the home position is reached, the current
             position is reset to the limit.home.preset.Additionally,
             limit.home.triggered is set to 1, and the No Reference
             Position(WR) warning flag is cleared.This command is equivalent
             to tools gotolimit home neg 2 0. Example Usage :
 \code
 / home↵
 01 0 OK BUSY WR 0
 \endcode
 \warning    Upon power up or setting changes, this command should be issued
             to obtain a reference position.Otherwise, motion commands may
             respond with a rejection reply or behave unexpectedly.
*/
void Device::home(void) const { (void)command(Command::Home); }

/**
 * \author     lokraszewski
 * \date       03-Oct-2018
 * \brief      abs moves to the absolute position of value.
 *
 * \param[in]  value  Value must be in the range [ limit.min, limit.max ].
 *
 * \details    { detailed_item_description }
 */
void Device::move_absolute(const int value) { (void)command<>(Command::MoveAbsolute, value); }

std::shared_ptr<Reply> Device::command(const Command cmd) const { return m_ctrl->command(m_address, cmd); }

// template <typename T>
// std::shared_ptr<Reply> Device::test(const Command cmd, const T param) const
// {
//   return m_ctrl->command<T>(m_address, cmd, param);
// }

} // namespace zaber
