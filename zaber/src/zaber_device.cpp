/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 09-10-2018
 */

#include "zaber/zaber_device.h"
#include "zaber/zaber_control.h"
namespace zaber
{

/**
 * \date       09-Oct-2018
 * \brief      Gets the range.
 *
 * \param[in]  id    Product ID
 *
 * \return     The range.
 *
 */
double get_range(const DeviceID id)
{
  switch (id)
  {

  case DeviceID::LRM025A_E03T3:
  case DeviceID::LRM025A_T3:
  case DeviceID::LRM025B_E03T3:
  case DeviceID::LRM025B_T3:
  case DeviceID::X_LHM025A:
  case DeviceID::X_LHM025A_E03:
  case DeviceID::X_LHM025A_S:
  case DeviceID::X_LHM025A_SE03: return 25e-3;
  case DeviceID::LRM050A_E03T3:
  case DeviceID::LRM050A_T3:
  case DeviceID::LRM050B_E03T3:
  case DeviceID::LRM050B_T3:
  case DeviceID::X_LHM050A:
  case DeviceID::X_LHM050A_E03:
  case DeviceID::X_LHM050A_S:
  case DeviceID::X_LHM050A_SE03: return 50e-3;
  case DeviceID::X_LSQ075A:
  case DeviceID::X_LSQ075A_E01:
  case DeviceID::X_LSQ075B:
  case DeviceID::X_LSQ075B_E01:
  case DeviceID::X_LSQ075D:
  case DeviceID::X_LSQ075D_E01: return 75e-3;
  case DeviceID::LRM100A_E03T3:
  case DeviceID::LRM100A_T3:
  case DeviceID::LRM100B_E03T3:
  case DeviceID::LRM100B_T3:
  case DeviceID::X_LHM100A:
  case DeviceID::X_LHM100A_E03:
  case DeviceID::X_LHM100A_S:
  case DeviceID::X_LHM100A_SE03: return 100e-3;
  case DeviceID::X_LHM150A:
  case DeviceID::X_LHM150A_E03:
  case DeviceID::X_LHM150A_S:
  case DeviceID::X_LHM150A_SE03:
  case DeviceID::X_LSQ150A:
  case DeviceID::X_LSQ150A_E01:
  case DeviceID::X_LSQ150B:
  case DeviceID::X_LSQ150B_E01:
  case DeviceID::X_LSQ150D:
  case DeviceID::X_LSQ150D_E01: return 150e-3;
  case DeviceID::LRM200A_E03T3:
  case DeviceID::LRM200A_T3:
  case DeviceID::LRM200B_E03T3:
  case DeviceID::LRM200B_T3:
  case DeviceID::X_LHM200A:
  case DeviceID::X_LHM200A_E03:
  case DeviceID::X_LHM200A_S:
  case DeviceID::X_LHM200A_SE03: return 200e-3;
  case DeviceID::X_LSQ300A:
  case DeviceID::X_LSQ300A_E01:
  case DeviceID::X_LSQ300B:
  case DeviceID::X_LSQ300B_E01:
  case DeviceID::X_LSQ300D:
  case DeviceID::X_LSQ300D_E01: return 300e-3;
  case DeviceID::X_LSQ450A:
  case DeviceID::X_LSQ450A_E01:
  case DeviceID::X_LSQ450B:
  case DeviceID::X_LSQ450B_E01:
  case DeviceID::X_LSQ450D:
  case DeviceID::X_LSQ450D_E01: return 450e-3;
  case DeviceID::X_LSQ600A:
  case DeviceID::X_LSQ600A_E01:
  case DeviceID::X_LSQ600B:
  case DeviceID::X_LSQ600B_E01:
  case DeviceID::X_LSQ600D:
  case DeviceID::X_LSQ600D_E01: return 600e-3;

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
 * \author     lokraszewski
 * \date       03-Oct-2018
 * \brief      Decelerates an axis and brings it to a halt.
 *
 * \details    { detailed_item_description }
 */
void Device::stop(void) const { (void)command(Command::Stop); }

/**
\author     lokraszewski
\date       02-Oct-2018
\brief      Instantly stops motorized movement.

\details    Firmware Versions 6.06+

The axis ignores the deceleration setting, immediately stops driving the motion,
and holds the current position. Example Usage :
\code
/1 1 estop↵
@01 1 OK BUSY-- 0
\endcode

\warning    The axis remains powered and will respond to future movement
            commands.

\warning    Excessive use of this command may result in potential damage to
            the product and reduced lifespan. Use sparingly if axis is under
            heavy load.
*/
void Device::emergency_stop(void) const { (void)command(Command::EmergencyStop); }

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
void Device::reset(void) const { (void)command(Command::SystemReset); }
void Device::restore_defaults(void) const { (void)command(Command::SystemRestore); }

void Device::store_position(const uint8_t number, const size_t pos) const
{
  (void)m_ctrl->command<>(m_address, Command::StorePosition, number, pos);
}

void Device::store_position(const size_t number) const { (void)command<>(Command::StorePosition, "current"); }

/**
 * \author     lokraszewski
 *
 * \date       03-Oct-2018
 * \brief      stored moves the axis to a previously stored position.Refer to
 *             the tools storepos command for more information.
 *
 * \param[in]  number  Number specifies the stored position number, from 1 -
 *                     16.
 *
 * \details    { detailed_item_description }
 */
void Device::move_stored(const uint8_t number) const { (void)command<>(Command::MoveStored, number); }

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

} // namespace zaber
