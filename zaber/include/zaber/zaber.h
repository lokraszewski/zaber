#pragma once

// OS Specific sleep
// #include "bit_macro.hpp" //Bit fields.
#include "fmt/format.h"
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

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <iostream>
#include <math.h>  /* log10 */
#include <stdio.h> /* printf */

namespace zaber
{

/*
 Talking to Zaber Devices
Zaber devices listen for Commands sent to them over a serial port and then immediately respond with a Reply. Commands always begin with a /
and end with a newline. Some commands take parameters, which are separated by spaces. Two example commands are:

/1 help↵
/1 move abs 10000↵
Where the move command has parameters of abs and 10000.

Replies begin with a @, have 4 or more parameters and end with a newline. For example, the most common reply is:

@01 0 OK IDLE -- 0
Which can be broken down into:

@                    A Reply
 01                  The ID of the device sending the reply
    0                The reply scope. 0 for the device or all axes, 1 onwards for an individual axis.
      OK             The command succeeded.
          IDLE       The device isn't moving, otherwise BUSY if it is moving.
               --    No faults or warnings in the device
                  0  The return value, typically 0.
A complete description of the reply fields is available in the Replies section.

Devices can also send two other types of messages; Alerts, starting with ! and Info, starting with #. Info messages are commonly seen in
response to a help command.

 */
class Device
{

public:
  typedef uint8_t     Address;
  typedef std::string Setting;

  Device(const Address address) : m_address(address)
  {
    m_device_count++;
    m_log->trace("{} with address of {}", __FUNCTION__, m_address);
  }
  virtual ~Device()
  {
    m_device_count--;
    m_log->trace("{} with address of {}", __FUNCTION__, m_address);
  }

  bool is_busy(void)
  {
    // Send empty command to the device address.
    // Wait and parse response.
  }

  bool is_connected(void) {}

  /**

  @author     lokraszewski
  @date       02-Oct-2018
  @brief      Instantly stops motorized movement.

  @details    Firmware Versions 6.06+

              The axis ignores the deceleration setting, immediately stops
              driving the motion, and holds the current position. Example Usage
              :
  @code
 /1 1 estop↵
 @01 1 OK BUSY-- 0
  @endcode

  @warning    The axis remains powered and will respond to future movement
              commands.

  @warning    Excessive use of this command may result in potential damage to
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

  /**
   * @author     lokraszewski
   * @date       02-Oct-2018
   * @brief      { function_description }
   *
   * @param[in]  param  The parameter
   *
   * @return     { description_of_the_return_value }
   *
   * @details
   *
   *
   *
   *
   *
   * { detailed_item_description }
   */
  std::string help(const std::string param = "") const
  {
    m_log->error("{} {}, NOT IMPLEMENTED", __FUNCTION__, param);
    return "";
  }

  /**
   @author     lokraszewski
   @date       02-Oct-2018
   @brief      Moves the axis to the home position.

   @details    The axis is moved towards the home position(closest to the motor
               generally) at the lesser of the limit.approach .maxspeed and
               maxspeed settings.Once the home position is reached, the current
               position is reset to the limit.home.preset.Additionally,
               limit.home.triggered is set to 1, and the No Reference
               Position(WR) warning flag is cleared.This command is equivalent
               to tools gotolimit home neg 2 0. Example Usage :
   @code
   / home↵
   \@01 0 OK BUSY WR 0
   @endcode
   @warning    Upon power up or setting changes, this command should be issued
               to obtain a reference position.Otherwise, motion commands may
               respond with a rejection reply or behave unexpectedly.
  */
  void home(void) const { m_log->error("{}, NOT IMPLEMENTED", __FUNCTION__); }

  static size_t device_count(void) { return m_device_count; }

private:
  static size_t                          m_device_count;
  static std::shared_ptr<spdlog::logger> m_log;

protected:
  Address m_address;
};

} // namespace zaber
