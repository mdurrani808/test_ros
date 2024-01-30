/**
 * \file driver.hpp
 * \mainpage
 *    Contains the main driver
 * \author
 *    Tobit Flatscher (github.com/2b-t)
*/

#ifndef MYACTUATOR_RMD__DRIVER
#define MYACTUATOR_RMD__DRIVER
#pragma once

#include <chrono>
#include <cstdint>
#include <string>

#include "myactuator_rmd/actuator_state/acceleration_type.hpp"
#include "myactuator_rmd/actuator_state/baud_rate.hpp"
#include "myactuator_rmd/actuator_state/control_mode.hpp"
#include "myactuator_rmd/actuator_state/feedback.hpp"
#include "myactuator_rmd/actuator_state/gains.hpp"
#include "myactuator_rmd/actuator_state/motor_status_1.hpp"
#include "myactuator_rmd/actuator_state/motor_status_2.hpp"
#include "myactuator_rmd/actuator_state/motor_status_3.hpp"
#include "myactuator_rmd/protocol/address_offset.hpp"
#include "myactuator_rmd/protocol/node.hpp"


namespace myactuator_rmd {

  /**\class Driver
   * \brief
   *    Driver for commanding the MyActuator RMD actuator series
  */
  class Driver: protected Node<AddressOffset::request,AddressOffset::response> {
    public:
      /**\fn Driver
       * \brief
       *    Class constructor
       * 
       * \param[in] ifname
       *    The name of the network interface that should communicated over
       * \param[in] actuator_id
       *    The actuator id [1, 32]
      */
      Driver(std::string const& ifname, std::uint32_t const actuator_id);
      Driver() = delete;
      Driver(Driver const&) = delete;
      Driver& operator = (Driver const&) = default;
      Driver(Driver&&) = default;
      Driver& operator = (Driver&&) = default;

      /**\fn getAcceleration
       * \brief
       *    Reads the current acceleration
       * 
       * \return
       *    The current acceleration in dps with a resolution of 1 dps
      */
      [[nodiscard]]
      std::int32_t getAcceleration();

      /**\fn getCanId
       * \brief
       *    Get the CAN ID of the device
       * 
       * \return
       *    The CAN ID of the device starting at 0x240
      */
      std::uint16_t getCanId();

      /**\fn getControllerGains
       * \brief
       *    Reads the currently used controller gains
       * 
       * \return
       *    The currently used controller gains for current, speed and position as unsigned 8-bit integers
      */
      [[nodiscard]]
      Gains getControllerGains();

      /**\fn getControlMode
       * \brief
       *    Reads the currently used control mode
       * 
       * \return
       *    The currently used control mode
      */
      [[nodiscard]]
      ControlMode getControlMode();

      /**\fn getMotorModel
       * \brief
       *    Reads the motor model currently in use by the actuator
       * 
       * \return
       *    The motor model string currently in use by the actuator, e.g. 'X8S2V10'
      */
      [[nodiscard]]
      std::string getMotorModel();

      /**\fn getMotorPower
       * \brief
       *    Reads the current motor power consumption in Watt
       * 
       * \return
       *    The current motor power consumption in Watt with a resolution of 0.1
      */
      [[nodiscard]]
      float getMotorPower();

      /**\fn getMotorStatus1
       * \brief
       *    Reads the motor status 1
       * 
       * \return
       *    The motor status 1 containing temperature, voltage and error codes
      */
      [[nodiscard]]
      MotorStatus1 getMotorStatus1();

      /**\fn getMotorStatus2
       * \brief
       *    Reads the motor status 2
       * 
       * \return
       *    The motor status 2 containing current, speed and position
      */
      [[nodiscard]]
      MotorStatus2 getMotorStatus2();

      /**\fn getMotorStatus3
       * \brief
       *    Reads the motor status 3
       * 
       * \return
       *    The motor status 3 containing detailed current information
      */
      [[nodiscard]]
      MotorStatus3 getMotorStatus3();

      /**\fn getMultiTurnAngle
       * \brief
       *    Read the multi-turn angle
       * 
       * \return
       *    The current multi-turn angle with a resolution of 0.01 deg
      */
      [[nodiscard]]
      float getMultiTurnAngle();

      /**\fn getMultiTurnEncoderPosition
       * \brief
       *    Read the multi-turn encoder position subtracted by the encoder multi-turn zero offset
       * 
       * \return
       *    The multi-turn encoder position
      */
      [[nodiscard]]
      std::int32_t getMultiTurnEncoderPosition();

      /**\fn getMultiTurnEncoderOriginalPosition
       * \brief
       *    Read the raw multi-turn encoder position without taking into consideration the multi-turn zero offset
       * 
       * \return
       *    The multi-turn encoder position
      */
      [[nodiscard]]
      std::int32_t getMultiTurnEncoderOriginalPosition();

      /**\fn getMultiTurnEncoderZeroOffset
       * \brief
       *    Read the multi-turn encoder zero offset
       * 
       * \return
       *    The multi-turn encoder zero offset
      */
      [[nodiscard]]
      std::int32_t getMultiTurnEncoderZeroOffset();

      /**\fn getRuntime
       * \brief
       *    Reads the uptime of the actuator in milliseconds
       * 
       * \return
       *    The uptime of the actuator in milliseconds
      */
      [[nodiscard]]
      std::chrono::milliseconds getRuntime();

      /**\fn getSingleTurnAngle
       * \brief
       *    Read the single-turn angle
       * \warning
       *    This does not seem to give correct values with my X8-PRO V2 actuator!
       * 
       * \return
       *    The current single-turn angle with a resolution of 0.01 deg
      */
      [[nodiscard]]
      float getSingleTurnAngle();

      /**\fn getSingleTurnEncoderPosition
       * \brief
       *    Read the single-turn encoder position
       * 
       * \return
       *    The single-turn encoder position
      */
      [[nodiscard]]
      std::int16_t getSingleTurnEncoderPosition();

      /**\fn getVersionDate
       * \brief
       *    Reads the version date of the actuator firmware
       * 
       * \return
       *    The version date of the firmware on the actuator, e.g. '20220206'
      */
      [[nodiscard]]
      std::uint32_t getVersionDate();

      /**\fn lockBrake
       * \brief
       *    Close the holding brake. The motor won't be able to turn anymore.
      */
      void lockBrake();

      /**\fn releaseBrake
       * \brief
       *    Open the holding brake leaving the motor in a movable state
      */
      void releaseBrake();

      /**\fn reset
       * \brief
       *    Reset the actuator
      */
      void reset();

      /**\fn sendCurrentSetpoint
       * \brief
       *    Send a current set-point to the actuator
       *
       * \param[in] current
       *    The current set-point in Ampere [-20.00, 20.00]
       * \return
       *    Feedback control message containing actuator position, velocity, torque and temperature
      */
      Feedback sendCurrentSetpoint(float const current);

      /**\fn sendPositionAbsoluteSetpoint
       * \brief
       *    Send an absolute position set-point to the actuator additionally specifying a maximum velocity
       *
       * \param[in] position
       *    The position set-point in degree [-360.00, 360.00]
       * \param[in] max_speed
       *    The maximum speed for the motion in degree per second [-1320.0, 1320.0]
       * \return
       *    Feedback control message containing actuator position, velocity, torque and temperature
      */
      Feedback sendPositionAbsoluteSetpoint(float const position, float const max_speed = 500.0);

      /**\fn sendTorqueSetpoint
       * \brief
       *    Send a torque set-point to the actuator by setting the current
       *
       * \param[in] torque
       *    The desired torque in [Nm]
       * \param[in] torque_constant
       *    The motor's torque constant [Nm/A], depends on the model of the motor
       * \return
       *    Feedback control message containing actuator position, velocity, torque and temperature
      */
      Feedback sendTorqueSetpoint(float const torque, float const torque_constant = 2.09);

      /**\fn sendVelocitySetpoint
       * \brief
       *    Send a velocity set-point to the actuator
       *
       * \param[in] speed
       *    The speed set-point in degree per second [-1320.00, 1320.00]
       * \return
       *    Feedback control message containing actuator position, velocity, torque and temperature
      */
      Feedback sendVelocitySetpoint(float const speed);

      /**\fn setAcceleration
       * \brief
       *    Write the acceleration/deceleration for the different modes to RAM and ROM (persistent)
       * 
       * \param[in] acceleration
       *    The desired acceleration/deceleration in dps with a resolution of 1 dps/s [100, 60000]
       * \param[in] mode
       *    The mode of the desired acceleration/deceleration to be set
      */
      void setAcceleration(std::uint32_t const acceleration, AccelerationType const mode);

      /**\fn setBaudRate
       * \brief
       *    Set the communication Baud rate
       * 
       * \param[in] baud_rate
       *    Communication Baud rate that the actuator should operator with
      */
      void setBaudRate(BaudRate const baud_rate);

      /**\fn setCanId
       * \brief
       *    Set the CAN ID of the device
       * 
       * \param[in] can_id
       *    The CAN ID of the device in the range [1, 32]
      */
      void setCanId(std::uint16_t const can_id);

      /**\fn setCurrentPositionAsEncoderZero
       * \brief
       *    Set the zero offset (initial position) of the encoder to the current position
       * \warning
       *    Motor has be restarted in order for this to become effective
       * 
       * \return
       *    Current encoder position that was set to be zero
      */
      std::int32_t setCurrentPositionAsEncoderZero();

      /**\fn setEncoderZero
       * \brief
       *    Set the zero offset (initial position) of the encoder to a given value
       * \warning
       *    Motor has be restarted in order for this to become effective
       * 
       * \param[in] encoder_offset
       *    Encoder offset that should be set as zero
      */
      void setEncoderZero(std::int32_t const encoder_offset);

      /**\fn setControllerGains
       * \brief
       *    Write the currently used controller gains either to RAM (not persistent after reboot) or ROM (persistent)
       * 
       * \param[in] gains
       *    The PI-gains for current, speed and position to be set
       * \param[in] is_persistent
       *    Boolean argument signaling whether the controller gains should be persistent after reboot of the actuator or not
       * \return
       *    The currently used controller gains for current, speed and position as unsigned 8-bit integers
      */
      Gains setControllerGains(Gains const& gains, bool const is_persistent = false);

      /**\fn setTimeout
       * \brief
       *    Set the communication interruption protection time setting. The break will be triggered if the communication
       *    is interrupted for longer than the set time. The value 0 disables this feature.
       * 
       * \param[in] timeout
       *    The desired interruption protection time, 0 in case it should be disabled
      */
      void setTimeout(std::chrono::milliseconds const& timeout);

      /**\fn shutdownMotor
       * \brief
       *    Turn off the motor
      */
      void shutdownMotor();

      /**\fn stopMotor
       * \brief
       *    Stop the motor if running closed loop command
      */
      void stopMotor();
  };

}

#endif // MYACTUATOR_RMD__DRIVER
