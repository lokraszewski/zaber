#pragma once

#include <iostream>
#include <map>
#include <string>

/*
 * @Author: Lukasz
 * @Date:   03-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 03-10-2018
 */

namespace zaber
{

/*

Warning Flags
A warning flag is provided in each device-to-user reply message, indicating whether any device fault or warning is active. If more than one
condition is active, it shows the one with highest precedence.

The warning flags are defined as follows, with the highest priority first:

 */

enum class Warning
{
  None,
  DriverDisabled, // FD - The driver has disabled itself due to overheating. This warning persists until the driver returns to normal
                  // operating conditions.
  EncoderError,   // FQ - The encoder-measured position may be unreliable. The encoder has encountered a read error due to poor sensor
                  // alignment, vibration, dirt or other environmental conditions. A home operation is recommended to recalibrate encoder
                  // reference position. If a controller is set with a peripheral ID of a peripheral with a direct encoder, this flag may
  // appear when the peripheral is not connected. Send system reset after connecting the peripheral to clear the warning. This
  // warning persists until acknowledged and cleared by the user with the warnings command. Please contact Zaber's technical
  // support if this error persists.
  StalledAndStopped, // FS - Stalling was detected and the axis has stopped itself. This warning persists until acknowledged and cleared by
                     // the user with the warnings command.
  ExcessiveTwist,    // FT - The lockstep group has exceeded allowable twist and has stopped. This warning persists until acknowledged and
                     // cleared by the user with the warnings command.
  StreamBoundsError, // FB - A previous streamed motion could not be executed because it
                     // failed a precondition (e.g. motion exceeds device bounds, calls
                     // nested too deeply). The error reason can be obtained using the
                     // stream info command. This warning persists until acknowledged and
                     // cleared by the user with the warnings command; also, until the
                     // warning is cleared, no further streamed motions can be sent to
                     // the failed stream.
  InterpolatedPathDeviation, // FP - Streamed or sinusoidal motion was terminated because an axis slipped and thus the device deviated from
                             // the requested path. This warning persists until acknowledged and cleared by the user with the warnings
                             // command.
  LimitError, // FE - The target limit sensor cannot be reached or is faulty. This warning persists until acknowledged and cleared by the
              // user with the warnings command.
              //
  Devicenothomed, // WH - The device has a position reference, but has not been homed. As a result, calibration has been disabled. Home the
                  // device to re-enable calibration. This warning persists until the device has been homed.
  UnexpectedLimitTrigger, // WL - A movement operation did not complete due to a triggered limit sensor. This flag is set if a movement
                          // operation is interrupted by a limit sensor and the No Reference Position (WR) warning flag is not present. This
                          // may be an indication that the axis has slipped or one of limit.min and limit.max is incorrect. This warning
                          // persists until acknowledged and cleared by the user with the warnings command.
  Invalidcalibrationtype, // WP - The saved calibration data type for the specified peripheral.serial value is unsupported by the current
                          // peripheralid. This warning persists until a valid combination of calibration data, peripheralid, and
                          // peripheral.serial is provided.
  VoltageOutofRange, // WV - The supply voltage is outside the recommended operating range of the device. Damage could result to the device
                     // if not remedied. This warning persists until the condition is remedied.
  ControllerTemperatureHigh, // WT - The internal temperature of the controller has exceeded the recommended limit for the device. This
                             // warning persists until the over temperature condition is remedied.
  DisplacedwhenStationary,   // WM - While not in motion, the axis has been forced out of its position. This warning persists until the axis
                             // is moved.
  NoReferencePosition, // WR - Axis has not had a reference position established. This warning persists until the axis position is updated
                       // via homing or any command/action that sets position.
  ManualControl,       // NC - Axis is busy due to manual control via the knob. This warning persists until a movement command is issued.
  CommandInterrupted,  // NI - A movement operation (command or manual control) was requested while the axis was executing another movement
                       // command. This indicates that a movement command did not complete.This warning persists until a movement command is
                       // issued when the axis is either idle or executing a manual control movement.
  StreamDiscontinuity, // ND - The device has slowed down while following a streamed motion path because it has run out of queued motions.
                       // This warning persists until the stream has enough motions queued that it no longer needs to decelerate for that
                       // reason, or until the stream is disabled.
  SettingUpdatePending, // NU - A setting is pending to be updated or a reset is pending. This warning is cleared automatically, once the
                        // settings have been updated or the device has reset.
  JoystickCalibrating,  // NJ - Joystick calibration is in progress. Moving the joystick will have no effect. This warning persists until
                        // joystick calibration is complete.

  Unknown,
};

std::ostream& operator<<(std::ostream& os, const Warning& warn);

inline Warning get_warning(const std::string str)
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

enum class ReplyFlag
{
  OK,    //*! The command was valid and accepted by the device.
  RJ,    //*! The command was rejected. The data field of the message will contain one of the following reasons:
  AGAIN, //*! The command cannot be processed right now. The user or application should send the command again. Occurs only during streamed
         // motion.
  BADAXIS,      //*! The command was sent with an axis number greater than the number of axes available.
  BADCOMMAND,   //*! The command or setting is incorrect or invalid.
  BADDATA,      //*! The data provided in the command is incorrect or out of range.
  BADMESSAGEID, //*! A message ID was provided, but was not either -- or a number from 0 to 99.
  DEVICEONLY,   //*! An axis number was specified when trying to execute a device only command.
  FULL,     //*! The device has run out of permanent storage and cannot accept the command. Occurs when storing to a stream buffer or when
            // saving commands to joystick keys.
  LOCKSTEP, //*! An axis cannot be moved using normal motion commands because it is part of a lockstep group. You must use lockstep commands
            // for motion or disable the lockstep group first.
  NOACCESS, //*! The command or setting is not available at the current access level.
  PARKED,   //*! The device cannot move because it is currently parked.
  STATUSBUSY, //*! The device cannot be parked, nor can certain settings be changed, because it is currently busy.
};

std::ostream& operator<<(std::ostream& os, const ReplyFlag& rf);

inline ReplyFlag get_reply_flag(const std::string str)
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

enum class Status
{
  IDLE,
  BUSY,
};

std::ostream& operator<<(std::ostream& os, const Status& sts);

inline Status get_status(const std::string str)
{
  const std::map<std::string, Status> m = {{"IDLE", Status::IDLE}, {"BUSY", Status::BUSY}};
  return m.at(str);
}

} // namespace zaber