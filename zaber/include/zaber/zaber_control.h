#pragma once

#include "zaber_includes.h"
#include "zaber_types.h"
#include <map>
namespace zaber
{

class Device;
class Controller
{
public:
  typedef uint8_t                         Address; /** Address type. */
  typedef std::string                     Setting; /** Setting*/
  typedef std::shared_ptr<serial::Serial> Port;    /** Serial port type. */

  Controller(const Port port);
  Controller() = delete;
  ~Controller();

  std::shared_ptr<Reply> command(const uint address, const Command command)
  {
    const auto packet = fmt::format("/{} {}\n", address, command);
    m_log->trace("{}", packet);
    m_port->write(packet);

    auto r = recieve_reply();
    if (r == nullptr)
    {
      const auto err = "No response from device!";
      m_log->error("{}", err);
      throw std::runtime_error(err);
    }

    return r;
  }

  template <typename T>
  std::shared_ptr<Reply> command(const uint address, const Command command, const T param)
  {
    const auto packet = fmt::format("/{} {} {}\n", address, command, param);
    m_log->trace("{}", packet);
    m_port->write(packet);
    auto r = recieve_reply();
    if (r == nullptr)
    {
      const auto err = "No response from device!";
      m_log->error("{}", err);
      throw std::runtime_error(err);
    }

    return r;
  }

  /**
   * \date       04-Oct-2018
   * \brief      Broadcasts a command.
   *
   * \param[in]  command  The command
   *
   * \return     { description_of_the_return_value }
   *
   * \details    { detailed_item_description }
   */
  std::vector<std::shared_ptr<Reply>> broadcast(const Command command)
  {
    const auto packet = fmt::format("/{}\n", command);
    m_log->trace("{}", packet);
    m_port->write(packet);
    return recieve_multiple_reply();
  }

  template <typename T>
  std::vector<std::shared_ptr<Reply>> broadcast(const Command command, const T param)
  {
    const auto packet = fmt::format("/{} {}\n", command, param);
    m_log->trace("{}", packet);
    m_port->write(packet);
    return recieve_multiple_reply();
  }

  std::vector<std::shared_ptr<Reply>> recieve_multiple_reply(uint max_replies = 100)
  {
    std::vector<std::shared_ptr<Reply>> reply;
    reply.reserve(max_replies);

    while (max_replies--)
    {
      auto r = recieve_reply();
      if (r == nullptr)
      {
        if (reply.size() == 0)
        {
          const auto err = "No response from device!";
          m_log->error("{}", err);
          throw std::runtime_error(err);
        }
        else
        {
          break;
        }
      }
      m_log->trace("{}", *r);
      reply.push_back(r);
    }
    return reply;
  }

  std::shared_ptr<Reply> recieve_reply()
  {

    auto response = m_port->readline(MAX_REPLY_LENGTH, "\n");
    if (response.size() == 0)
    {
      return nullptr;
    }

    if (response[0] != '@')
    {
      const auto err = fmt::format("Not a valid reply: [{}]", response);
      m_log->error("{}", err);
      return nullptr;
    }

    return std::make_shared<Reply>(response);
  }

  // void get_device_address(DeviceID id) {}
  // void get_device(size_t address) {}

  /**
   * \date       04-Oct-2018
   * \brief      Populates the device list.
   *
   * \details    Needs to be run in order to find devices in the chain.
   */
  uint discover(void)
  {
    /* Drop all previously known devies since renumber could corrupt the
     * mapping. */
    m_dev_map.clear();
    /* Renumerate first so the addresses are alwasy sequentional. If no response
     * is returned to renumber then we have no devies. */
    try
    {
      (void)broadcast(Command::Renumber);
    }
    catch (...)
    {
      return 0;
    }

    const auto replies = broadcast<>(Command::Get, "deviceid");
    for (auto r : replies)
    {
      m_dev_map[r->address] = r->get<uint>();
    }

    return device_count();
  }

  /**
   * \date       04-Oct-2018
   * \brief      Returns number of discovered devices on the chain.
   *
   * \return     Number of devices.
   *
   */
  size_t device_count(void) { return m_dev_map.size(); }

  std::unique_ptr<Device> make_device(const DeviceID id, const Address addr);
  std::unique_ptr<Device> make_device_from_address(const Address addr);
  std::unique_ptr<Device> make_device_from_id(const DeviceID id);

private:
  static constexpr auto                  MAX_REPLY_LENGTH   = 50;
  static constexpr auto                  MAX_COMMAND_LENGTH = 50;
  static std::shared_ptr<spdlog::logger> m_log;

  std::map<uint, uint> m_dev_map; /* map of address to device type. */

protected:
  const Port m_port;
};

} // namespace zaber
