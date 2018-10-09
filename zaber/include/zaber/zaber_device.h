#pragma once
/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 09-10-2018
 */

#include "zaber/zaber_control.h"
#include "zaber/zaber_includes.h"
#include "zaber/zaber_types.h"

namespace zaber
{

double get_range(const DeviceID id);

class Device
{

public:
  typedef uint8_t                         Address; /** Address type. */
  typedef std::string                     Setting; /** Setting*/
  typedef std::shared_ptr<serial::Serial> Port;    /** Serial port type. */

  Device(Controller* const ctrl, const Address address = 1, const DeviceID id = DeviceID::UNKNOWN);
  Device() = delete; // Delete default constructor.
  virtual ~Device();

  std::unique_ptr<Device> make_device(Controller* const ctrl, const Address address = 1, const DeviceID id = DeviceID::UNKNOWN);
  bool                    is_busy(void) const;
  void                    wait_until_idle(void) const;

  bool is_connected(void);
  void stop(void) const;
  void emergency_stop(void) const;
  void home(void) const;
  void reset(void) const;
  void restore_defaults(void) const;

  void move_absolute(const int value);
  /**
   * \author     lokraszewski
   * \date       03-Oct-2018
   * \brief      rel moves the axis by value microsteps, relative to the current
   *             position.
   *
   * \param[in]  value  Value must be in the range [ limit.min - pos, limit.max -
   *                    pos ].
   *
   * \details    { detailed_item_description }
   */
  void move_relative(int value);
  /**
   * \author     lokraszewski
   * \date       03-Oct-2018
   * \brief      vel moves the axis at the velocity specified by value until a
   *             limit is reached.
   *
   * \param[in]  value  Value must be in the range [ -resolution * 16384,
   *                    resolution * 16384 ].
   *
   * \details    { detailed_item_description }
   */
  void move_velocity(int value);
  /**
   * \author     lokraszewski
   * \date       03-Oct-2018
   * \brief      min moves the axis to the minimum position, as specified by
   *             limit.min.
   *
   * \details    { detailed_item_description }
   */
  void move_min(void);
  /**
   * \author     lokraszewski
   * \date       03-Oct-2018
   * \brief      max moves the axis to the maximum position, as specified by
   *             limit.max.
   *
   * \details    { detailed_item_description }
   */
  void move_max(void);

  void store_position(const uint8_t number, const size_t pos) const;
  void store_position(const uint8_t number) const;

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
  void move_stored(const uint8_t number) const;

  /**
   * \author     lokraszewski
   * \date       03-Oct-2018
   * \brief      index moves the axis to an index position. For a provided
   *             number, this command directs the axis to move to the absolute
   *             position (number - 1) * motion.index.dist.
   *
   * \param[in]  index  Note that only positive values of number are accepted.
   *
   * \details    For rotary devices with a non-zero limit.cycle.dist, the
   *             command will be accepted if the targeted position is greater or
   *             equal to 0 and less than limit.cycle.dist. The device will move
   *             either clockwise or counter-clockwise, depending on which
   *             direction yields the shortest distance to the target position.
   *             If you want all index positions to be equally spaced around the
   *             circle, set motion.index.dist to a factor of limit.cycle.dist.
   *             For linear devices, or rotary devices where limit.cycle.dist is
   *             zero, the command will be accepted if the targeted position is
   *             within the valid travel of the device, i.e. in the range [
   *             limit.min, limit.max ].
   */
  void move_index(unsigned int index);

  /**
   * \author     lokraszewski
   *
   * \date       03-Oct-2018
   * \brief      sin starts a sinusoidal motion.
   *
   * \param[in]  amplitude  The amplitude
   * \param[in]  period     The period
   * \param[in]  count      The count
   *
   * \details    Amplitude specifies half of the peak-to-peak amplitude of the
   *             motion in units of microsteps. A positive number implies that
   *             the sinusoidal *motion starts at the minimum position and will
   *             move in a positive direction from the starting position. A
   *             negative number implies that the *sinusoidal motion starts at
   *             the maximum position and will move in a negative direction from
   *             the starting position. The starting position of the device and
   *             the other limit of the sinusoidal motion (current position +
   *             amplitude * 2) must both be in the range [ limit.min, limit.max
   *             ] . Period specifies the period of the motion in ms, with
   *             resolution down to 0.1 ms. A minimum value of 1 ms is
   *             recommended to achieve a reasonable resolution. Period must be
   *             in the range [ 0.2, 429496729.5 ]. Count, an optional
   *             parameter, specifies the number of repeated cycles. The valid
   *             range is 1 - 4294967294. If count is not provided, the motion
   *             will continue until another motion or stop command pre-empts
   *             it. To stop the sinusoidal motion after the current cycle
   *             completes, refer to the move sin stop command. On stepper motor
   *             products with direct reading or linear encoders (i.e.
   *             encoder.mode is 2), sinusoidal motion commands can only be
   *             executed when cloop.mode is set to 2 or 0. sinusoidal motion
   *             illustration The speed and acceleration of a sinusoidal motion
   *             are determined by the amplitude and period specified in the
   *             command, as shown in the following equation. It is up to the
   *             user to ensure the maximum acceleration is low enough to
   *             prevent the stage from slipping. Note: A sinusoidal motion has
   *             limited ability to recover from a stalling condition. sin stop
   *             ends a sinusoidal motion when its current cycle completes.
   */
  void                   move_sin(int amplitude, int period, int count = 0);
  uint                   get_device_id(void);
  int                    get_position(void);
  std::shared_ptr<Reply> command(const Command cmd) const;

  template <typename T>
  std::shared_ptr<Reply> command(const Command cmd, const T param) const
  {
    return m_ctrl->command<T>(m_address, cmd, param);
  }

  template <typename T>
  T get_setting(const std::string setting)
  {
    return (command<std::string>(Command::Get, setting))->get<T>();
  }

  virtual void move_to_location(const double real_location) {}
  virtual void setup(void) {}

private:
protected:
  static std::shared_ptr<spdlog::logger> m_log;
  Controller* const                      m_ctrl;
  const Address                          m_address;
  const DeviceID                         m_id;
};
} // namespace zaber
