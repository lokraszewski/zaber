/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 10-10-2018
 */

#include "zaber/zaber_types.h"
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

namespace zaber
{

std::ostream& operator<<(std::ostream& os, const Warning& warn)
{
  switch (warn)
  {
  case Warning::None: os << "None"; break;
  case Warning::DriverDisabled: os << "DriverDisabled"; break;
  case Warning::EncoderError: os << "EncoderError"; break;
  case Warning::StalledAndStopped: os << "StalledAndStopped"; break;
  case Warning::ExcessiveTwist: os << "ExcessiveTwist"; break;
  case Warning::StreamBoundsError: os << "StreamBoundsError"; break;
  case Warning::InterpolatedPathDeviation: os << "InterpolatedPathDeviation"; break;
  case Warning::LimitError: os << "LimitError"; break;
  case Warning::Devicenothomed: os << "Devicenothomed"; break;
  case Warning::UnexpectedLimitTrigger: os << "UnexpectedLimitTrigger"; break;
  case Warning::Invalidcalibrationtype: os << "Invalidcalibrationtype"; break;
  case Warning::VoltageOutofRange: os << "VoltageOutofRange"; break;
  case Warning::ControllerTemperatureHigh: os << "ControllerTemperatureHigh"; break;
  case Warning::DisplacedwhenStationary: os << "DisplacedwhenStationary"; break;
  case Warning::NoReferencePosition: os << "NoReferencePosition"; break;
  case Warning::ManualControl: os << "ManualControl"; break;
  case Warning::CommandInterrupted: os << "CommandInterrupted"; break;
  case Warning::StreamDiscontinuity: os << "StreamDiscontinuity"; break;
  case Warning::SettingUpdatePending: os << "SettingUpdatePending"; break;
  case Warning::JoystickCalibrating: os << "JoystickCalibrating"; break;
  case Warning::Unknown: os << "Unknown"; break;
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const ReplyFlag& rf)
{
  switch (rf)
  {
  case ReplyFlag::OK: os << "OK"; break;
  case ReplyFlag::RJ: os << "RJ"; break;
  case ReplyFlag::AGAIN: os << "AGAIN"; break;
  case ReplyFlag::BADAXIS: os << "BADAXIS"; break;
  case ReplyFlag::BADCOMMAND: os << "BADCOMMAND"; break;
  case ReplyFlag::BADDATA: os << "BADDATA"; break;
  case ReplyFlag::BADMESSAGEID: os << "BADMESSAGEID"; break;
  case ReplyFlag::DEVICEONLY: os << "DEVICEONLY"; break;
  case ReplyFlag::FULL: os << "FULL"; break;
  case ReplyFlag::LOCKSTEP: os << "LOCKSTEP"; break;
  case ReplyFlag::NOACCESS: os << "NOACCESS"; break;
  case ReplyFlag::PARKED: os << "PARKED"; break;
  case ReplyFlag::STATUSBUSY: os << "STATUSBUSY"; break;
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const Status& sts)
{
  switch (sts)
  {
  case Status::IDLE: os << "IDLE"; break;
  case Status::BUSY: os << "BUSY"; break;
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const Command& cmd)
{

  switch (cmd)
  {
  case Command::StorePosition: os << "tools storepos"; break;
  case Command::SystemRestore: os << "system restore"; break;
  case Command::SystemReset: os << "system reset"; break;
  case Command::EmergencyStop: os << "estop"; break;
  case Command::Stop: os << "stop"; break;
  case Command::None: os << ""; break;
  case Command::MoveAbsolute: os << "move abs"; break;
  case Command::MoveRelative: os << "move rel"; break;
  case Command::MoveVelocity: os << "move vel"; break;
  case Command::MoveStored: os << "move stored"; break;
  case Command::MoveIndex: os << "move index"; break;
  case Command::MoveMin: os << "move min"; break;
  case Command::MoveMax: os << "move max"; break;
  case Command::Home: os << "home"; break;
  case Command::Get: os << "get"; break;
  case Command::Renumber: os << "renumber"; break;
  }

  return os;
}

Warning get_warning(const std::string str)
{
  const std::map<std::string, Warning> m = {{"FD", Warning::DriverDisabled},
                                            {"FQ", Warning::EncoderError},
                                            {"FS", Warning::StalledAndStopped},
                                            {"FT", Warning::ExcessiveTwist},
                                            {"FB", Warning::StreamBoundsError},
                                            {"FP", Warning::InterpolatedPathDeviation},
                                            {"FE", Warning::LimitError},
                                            {"WH", Warning::Devicenothomed},
                                            {"WL", Warning::UnexpectedLimitTrigger},
                                            {"WP", Warning::Invalidcalibrationtype},
                                            {"WV", Warning::VoltageOutofRange},
                                            {"WT", Warning::ControllerTemperatureHigh},
                                            {"WM", Warning::DisplacedwhenStationary},
                                            {"WR", Warning::NoReferencePosition},
                                            {"NC", Warning::ManualControl},
                                            {"NI", Warning::CommandInterrupted},
                                            {"ND", Warning::StreamDiscontinuity},
                                            {"NU", Warning::SettingUpdatePending},
                                            {"NJ", Warning::JoystickCalibrating},
                                            {"--", Warning::None}};

  return m.at(str);
}

ReplyFlag get_reply_flag(const std::string str)
{
  const std::map<std::string, ReplyFlag> m = {{"OK", ReplyFlag::OK},
                                              {"RJ", ReplyFlag::RJ},
                                              {"AGAIN", ReplyFlag::AGAIN},
                                              {"BADAXIS", ReplyFlag::BADAXIS},
                                              {"BADCOMMAND", ReplyFlag::BADCOMMAND},
                                              {"BADDATA", ReplyFlag::BADDATA},
                                              {"BADMESSAGEID", ReplyFlag::BADMESSAGEID},
                                              {"DEVICEONLY", ReplyFlag::DEVICEONLY},
                                              {"FULL", ReplyFlag::FULL},
                                              {"LOCKSTEP", ReplyFlag::LOCKSTEP},
                                              {"NOACCESS", ReplyFlag::NOACCESS},
                                              {"PARKED", ReplyFlag::PARKED},
                                              {"STATUSBUSY", ReplyFlag::STATUSBUSY}};
  return m.at(str);
}

Status get_status(const std::string str)
{
  const std::map<std::string, Status> m = {{"IDLE", Status::IDLE}, {"BUSY", Status::BUSY}};
  return m.at(str);
}

Reply::Reply(std::string reply)
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

} // namespace zaber
