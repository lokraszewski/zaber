#include "zaber/zaber.h"

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
  case Command::None: os << ""; break;
  case Command::MoveAbsolute: os << "move abs"; break;
  case Command::MoveRelative: os << "move rel"; break;
  case Command::MoveVelocity: os << "move vel"; break;
  case Command::MoveMin: os << "move min"; break;
  case Command::MoveMax: os << "move max"; break;
  case Command::Home: os << "home"; break;
  case Command::Get: os << "get"; break;
  case Command::Renumber: os << "renumber"; break;
  }

  return os;
}

std::shared_ptr<spdlog::logger> Device::m_log          = spdlog::stdout_color_mt("device");
std::shared_ptr<spdlog::logger> Controller::m_log      = spdlog::stdout_color_mt("zaber");
size_t                          Device::m_device_count = 0;

} // namespace zaber
