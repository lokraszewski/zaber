#pragma once

#include "zaber_types.h"

#include "fmt/format.h"
#include "fmt/ostream.h"
#include "serial/serial.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <cstdio>
#include <exception>
#include <iostream>
#include <memory> //Shared ptr.
#include <spdlog/spdlog.h>
#include <stdint.h>
#include <string>
#include <unistd.h>

#include <iostream>
#include <math.h> /* log10 */
#include <stdint.h>
#include <stdio.h> /* printf */
#include <stdlib.h>
#include <string>
#include <vector>

namespace zaber
{

/**
 \author     lokraszewski

 \date       03-Oct-2018
 \brief      Reply structure.

 \details    Format:
 \code
 * nn a fl bbbb ww x[:CC]ff
 *
 \endcode
 * - @ - Message Type Length: 1 byte. This field always contains @ for a reply
   message.
 - nn - Device Address Length: 2 bytes. This field contains the address of the
   device sending the reply, always formatted as two digits.
 - a - Axis Number Length: 1 byte. This field contains the reply scope, from 0
   to 9. 0 indicates that the following fields apply to the whole device and all
   axes on it, otherwise the fields apply to the specific axis indicated.
 - fl - Reply Flag Length: 2 bytes. The reply flag indicates if the message was
   accepted or rejected and can have the following values: OK - The command was
   valid and accepted by the device. RJ - The command was rejected. The data
   field of the message will contain one of the following reasons: AGAIN - The
   command cannot be processed right now. The user or application should send
   the command again. Occurs only during streamed motion. BADAXIS - The command
   was sent with an axis number greater than the number of axes available.
   BADCOMMAND - The command or setting is incorrect or invalid. BADDATA - The
   data provided in the command is incorrect or out of range. BADMESSAGEID - A
   message ID was provided, but was not either -- or a number from 0 to 99.
   DEVICEONLY - An axis number was specified when trying to execute a device
   only command. FULL - The device has run out of permanent storage and cannot
   accept the command. Occurs when storing to a stream buffer or when saving
   commands to joystick keys. LOCKSTEP - An axis cannot be moved using normal
   motion commands because it is part of a lockstep group. You must use lockstep
   commands for motion or disable the lockstep group first. NOACCESS - The
   command or setting is not available at the current access level. PARKED - The
   device cannot move because it is currently parked. STATUSBUSY - The device
   cannot be parked, nor can certain settings be changed, because it is
   currently busy.
 - bbbb - Device Status Length: 4 bytes. This field contains BUSY when the axis
   is moving and IDLE otherwise. All movement commands, including stop, put the
   axis into the BUSY state, while they are being executed. During streamed
   motion, wait commands are considered to be busy, not idle. If the reply
   message applies to the whole device, the status is BUSY if any axis is busy
   and IDLE if all axes are idle.
 - ww - Warning Flag Length: 2 bytes. Contains the highest priority warning
   currently active for the device or axis, or -- under normal conditions. A
   full description of the flags is available in the Warning Flags Section.
 - xxx.. - Response Data Length: 1+ bytes. The response for the command
   executed. The contents and format of this field vary depending on the
   command, but is typically 0 (zero). CC - Message Checksum Length: 3 bytes. A
   device will append a checksum to all replies if the comm.checksum setting is
   configured to 1. More information and code examples are provided in the
   Checksumming section below.
 - ff - Message Footer Length: 2 bytes. This field always contains a CR-LF
   combination for a reply message.
*/
struct Reply
{
public:
  int         address; /**! address*/
  int         scope;   /**! scope*/
  ReplyFlag   flag;    /**! flag*/
  Status      status;  /**! status*/
  Warning     warning; /**! warning*/
  std::string payload; /**! payload*/

  Reply(void) {}
  Reply(std::string reply)
  {
    std::istringstream       iss(reply);
    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    auto itr = tokens.begin();
    char sof;
    sscanf((*itr++).c_str(), "%c%d", &sof, &address);
    sscanf((*itr++).c_str(), "%d", &scope);
    flag    = get_reply_flag(*itr++);
    status  = get_status(*itr++);
    warning = get_warning(*itr++);
    payload = *itr++;
  }
  ~Reply() {}

  friend std::ostream& operator<<(std::ostream& os, const Reply& rp)
  {
    return os << fmt::format("[{}, {}, {}, {}, {}, {}]", rp.address, rp.scope, rp.flag, rp.status, rp.warning, rp.payload);
  }
};

class Device
{

public:
  typedef uint8_t                         Address; /** Address type. */
  typedef std::string                     Setting; /** Setting*/
  typedef std::shared_ptr<serial::Serial> Port;    /** Serial port type. */

  Device(Port port, const Address address = 1) : m_address(address), m_port(port)
  {
    m_log->trace("{} with address of {}", __FUNCTION__, m_address);
    if (m_port == nullptr)
    {
      m_log->error("Serial port cannot be null!");
      throw std::invalid_argument("Serial port cannot be null!");
    }
    m_device_count++;
  }

  Device() = delete; // Delete default constructor.

  virtual ~Device()
  {
    m_device_count--;
    m_log->trace("{} with address of {}", __FUNCTION__, m_address);
  }

  bool is_busy(void) const
  {
    const auto reply = send_command(Command::None);
    return reply.status == Status::BUSY;
  }

  bool is_connected(void)
  {
    try
    {
      const auto reply = send_command(Command::None);
      return true;
    }
    catch (const std::exception& e)
    {
      m_log->error("{}:{}", __FUNCTION__, e.what());
      return false;
    }
  }

  /**
   * \author     lokraszewski
   * \date       03-Oct-2018
   * \brief      Decelerates an axis and brings it to a halt.
   *
   * \details    { detailed_item_description }
   */
  void stop(void) const { m_log->error("{}, NOT IMPLEMENTED", __FUNCTION__); }

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
  void emergency_stop(void) const { m_log->error("{}, NOT IMPLEMENTED", __FUNCTION__); }

  template <typename T>
  T get(Setting setting)
  {
    m_log->error("{}:{}, NOT IMPLEMENTED", __FUNCTION__, setting);
    return 0;
  }

  // void send_command(uint address, int axis, std::string command, std::string subcommand, T param)
  // {
  // }

  // template <typename T>
  // void send_command(const Command command, T param)
  // {
  //   const auto command = fmt::format("/{} {} {}\r", m_address, command);

  //   m_log->trace("Sending command: [{}]", command);
  //   m_port->write(command);
  // }
  template <typename T>
  Reply send_command(const Command command, const T param) const
  {
    const auto packet = fmt::format("/{} {} {}\n", m_address, command, param);
    m_log->trace("Command: [{},{}, {}]", m_address, command, param);
    m_port->write(packet);
    return get_reply();
  }

  Reply send_command(const Command command) const
  {
    const auto packet = fmt::format("/{} {}\n", m_address, command);
    m_log->trace("Command: [{},{}]", m_address, command);
    m_port->write(packet);
    return get_reply();
  }

  // std::vector<Reply> send_broadcast(const Command command) const {}

  /**
   * \date       03-Oct-2018
   * \brief      Gets the reply.
   *
   * \return     The reply.
   *
   * \details    { detailed_item_description }
   * \throw       std::runtime_error No response from device!
   */
  Reply get_reply(void) const
  {
    const auto MAX_REPLY_LENGTH = 50;
    auto       response         = m_port->readlines(MAX_REPLY_LENGTH, "\n");

    // If we dont get a response then log and throw since this function must
    // return reply.
    if (response.size() == 0)
    {
      const auto err = "No response from device!";
      m_log->trace("{}", err);
      throw std::runtime_error(err);
    }

    // Parse the response with reply constructor.
    Reply reply(response[0]);

    m_log->trace("Reply: {}", reply);

    return reply;
  }

  /**
   * \author     lokraszewski
   * \date       02-Oct-2018
   * \brief      { function_description }
   *
   * \param[in]  param  The parameter
   *
   * \return     { description_of_the_return_value }
   *
   * \details    { detailed_item_description }
   */
  std::string help(const std::string param = "") const { return ""; }

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
  void home(void) const { const auto reply = send_command(Command::Home); }
  /**
   * \author     lokraszewski
   * \date       03-Oct-2018
   * \brief      abs moves to the absolute position of value.
   *
   * \param[in]  value  Value must be in the range [ limit.min, limit.max ].
   *
   * \details    { detailed_item_description }
   */
  void move_absolute(int value) { const auto reply = send_command<>(Command::MoveAbsolute, value); }

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
  void move_relative(int value) { const auto reply = send_command<>(Command::MoveRelative, value); }

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
  void move_velocity(int value) { const auto reply = send_command<>(Command::MoveVelocity, value); }

  /**
   * \author     lokraszewski
   * \date       03-Oct-2018
   * \brief      min moves the axis to the minimum position, as specified by
   *             limit.min.
   *
   * \details    { detailed_item_description }
   */
  void move_min(void) { const auto reply = send_command(Command::MoveMin); }

  /**
   * \author     lokraszewski
   * \date       03-Oct-2018
   * \brief      max moves the axis to the maximum position, as specified by
   *             limit.max.
   *
   * \details    { detailed_item_description }
   */
  void move_max(void) { const auto reply = send_command(Command::MoveMax); }

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
  void move_stored(uint8_t number) { m_log->error("{}:{}, NOT IMPLEMENTED", number, __FUNCTION__); }

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
  void move_index(unsigned int index) { m_log->error("{}:{}, NOT IMPLEMENTED", __FUNCTION__, index); }

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
  void move_sin(int amplitude, int period, int count = 0)
  {
    m_log->error("{}:{} {} {}  NOT IMPLEMENTED", __FUNCTION__, amplitude, period, count);
  }

  uint get_device_id(void)
  {
    const auto        reply = send_command<>(Command::Get, "deviceid");
    std::stringstream ss(reply.payload);
    uint              id;
    ss >> id;
    return id;
  }

  int get_position(void)
  {
    const auto        reply = send_command<>(Command::Get, "pos");
    std::stringstream ss(reply.payload);
    int               pos;
    ss >> pos;
    return pos;
  }

  static size_t device_count(void) { return m_device_count; }

private:
  static size_t                          m_device_count;
  static std::shared_ptr<spdlog::logger> m_log;

protected:
  Address m_address;
  Port    m_port;
};

} // namespace zaber
