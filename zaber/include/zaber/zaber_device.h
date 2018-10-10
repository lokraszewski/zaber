#pragma once
/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 10-10-2018
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
  Device() = delete; // Delete default constructor, we require a contnroller object.
  virtual ~Device();

  std::unique_ptr<Device> make_device(Controller* const ctrl, const Address address = 1, const DeviceID id = DeviceID::UNKNOWN);
  bool                    is_busy(void) const;
  void                    wait_until_idle(void) const;
  bool                    is_connected(void);
  void                    stop(void) const;
  void                    emergency_stop(void) const;
  void                    home(void) const;
  void                    reset(void) const;
  void                    restore_defaults(void) const;
  void                    move_absolute(const int value);
  void                    move_relative(int value);
  void                    move_velocity(int value);
  void                    move_min(void);
  void                    move_max(void);
  void                    store_position(const uint8_t number, const size_t pos) const;
  void                    store_position(const uint8_t number) const;
  void                    move_stored(const uint8_t number) const;
  void                    move_index(unsigned int index);
  DeviceID                get_device_id(void) const;
  int                     get_position(void) const;
  int                     get_max(void) const;
  int                     get_min(void) const;
  int                     get_home_position(void) const;

  template <typename T>
  T get_setting(const std::string setting) const
  {
    return (command<std::string>(Command::Get, setting))->get<T>();
  }

  std::shared_ptr<Reply> command(const Command cmd) const;

  template <typename T>
  std::shared_ptr<Reply> command(const Command cmd, const T param) const
  {
    return m_ctrl->command<T>(m_address, cmd, param);
  }

  template <typename T, typename... Args>
  std::shared_ptr<Reply> command(const Command cmd, const T param, Args... args) const
  {
    return m_ctrl->command<>(m_address, cmd, param, args...);
  }

  /**
   * \date       10-Oct-2018
   * \brief      Moves to real location, for linear device this would be in SI
   *             meters, for rotary device it would be SI degrees.
   *
   * \param[in]  real_location  The real location
   *
   */
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
