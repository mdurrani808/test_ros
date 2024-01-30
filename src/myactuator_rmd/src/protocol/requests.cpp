#include "myactuator_rmd/protocol/requests.hpp"

#include <chrono>
#include <cstdint>
#include <cstring>
#include <string>

#include "myactuator_rmd/actuator_state/baud_rate.hpp"
#include "myactuator_rmd/actuator_state/acceleration_type.hpp"
#include "myactuator_rmd/protocol/single_motor_message.hpp"
#include "myactuator_rmd/exceptions.hpp"


namespace myactuator_rmd {

  bool CanIdRequest::isWrite() const noexcept {
    return (getAs<std::uint8_t>(2) == 0) ? true : false;
  }

  GetCanIdRequest::GetCanIdRequest()
  : CanIdRequest{}  {
    setAt(static_cast<std::uint8_t>(1), 2);
    return;
  }

  SetCanIdRequest::SetCanIdRequest(std::uint16_t const can_id)
  : CanIdRequest{}  {
    setAt(static_cast<std::uint8_t>(0), 2);
    setAt(static_cast<std::uint8_t>(can_id), 6);
    return;
  }

  std::uint16_t SetCanIdRequest::getCanId() const noexcept {
    return static_cast<std::uint16_t>(getAs<std::uint8_t>(7));
  }

  SetAccelerationRequest::SetAccelerationRequest(std::uint32_t const acceleration, AccelerationType const mode)
  : SingleMotorRequest{} {
    if ((acceleration < 100) || (acceleration > 60000)) {
      throw ValueRangeException("Acceleration value '" + std::to_string(acceleration) + "' out of range [100, 60000]");
    }
    auto const acceleration_type {static_cast<std::uint8_t>(mode)};
    setAt(acceleration_type, 1);
    setAt(acceleration, 4);
    return;
  }

  std::uint32_t SetAccelerationRequest::getAcceleration() const noexcept {
    return getAs<std::uint32_t>(4);
  }

  AccelerationType SetAccelerationRequest::getMode() const noexcept {
    return static_cast<AccelerationType>(getAs<std::uint8_t>(1));
  }

  SetBaudRateRequest::SetBaudRateRequest(BaudRate const baud_rate)
  : SingleMotorRequest{} {
    setAt(static_cast<std::uint8_t>(baud_rate), 7);
    return;
  }

  BaudRate SetBaudRateRequest::getBaudRate() const noexcept {
    return static_cast<BaudRate>(getAs<std::uint8_t>(7));
  }

  SetEncoderZeroRequest::SetEncoderZeroRequest(std::int32_t const encoder_offset)
  : SingleMotorRequest{} {
    setAt(encoder_offset, 4);
    return;
  }

  std::int32_t SetEncoderZeroRequest::getEncoderZero() const noexcept {
    return getAs<std::int32_t>(4);
  }

  SetPositionAbsoluteRequest::SetPositionAbsoluteRequest(float const position, float const max_speed)
  : SingleMotorRequest{} {
    if ((position < -360.0f) || (position > 360.0f)) {
      throw ValueRangeException("Position value '" + std::to_string(position) + "' out of range [0.0, 360.0]");
    }
    if ((max_speed < -1320.0f) || (max_speed > 1320.0f)) {
      throw ValueRangeException("Maximum speed value '" + std::to_string(max_speed) + "' out of range [0.0, 1320.0]");
    }
    auto const v {static_cast<std::uint16_t>(max_speed)};
    auto const pos {static_cast<std::int32_t>(position*100.0f)};
    setAt(v, 2);
    setAt(pos, 4);
    return;
  }

  float SetPositionAbsoluteRequest::getMaxSpeed() const noexcept {
    return static_cast<float>(getAs<std::uint16_t>(2));
  }

  float SetPositionAbsoluteRequest::getPosition() const noexcept {
    return static_cast<float>(getAs<std::int32_t>(4)/100.0f);
  }

  SetTorqueRequest::SetTorqueRequest(float const current)
  : SingleMotorRequest{} {
    if ((current < -20.0f) || (current > 20.0f)) {
      throw ValueRangeException("Current value '" + std::to_string(current) + "' out of range [-20.0, 20.0]");
    }
    auto const c {static_cast<std::int16_t>(current/0.01f)};
    setAt(c, 4);
    return;
  }

  float SetTorqueRequest::getTorqueCurrent() const noexcept {
    return static_cast<float>(getAs<std::int16_t>(4))*0.01f;
  }

  SetTimeoutRequest::SetTimeoutRequest(std::chrono::milliseconds const& timeout) {
    setAt(static_cast<std::uint32_t>(timeout.count()), 4);
    return;
  }

  std::chrono::milliseconds SetTimeoutRequest::getTimeout() const noexcept {
    std::chrono::milliseconds const timeout {getAs<std::uint32_t>(4)};
    return timeout;
  }

  SetVelocityRequest::SetVelocityRequest(float const speed)
  : SingleMotorRequest{} {
    if ((speed < -1320.0f) || (speed > 1320.0f)) {
      throw ValueRangeException("Speed value '" + std::to_string(speed) + "' out of range [-1320.0, 1320.0]");
    }
    auto const s {static_cast<std::int32_t>(speed*100.0f)};
    setAt(s, 4);
    return;
  }

  float SetVelocityRequest::getSpeed() const noexcept {
    return static_cast<float>(getAs<std::int32_t>(4))/100.0f;
  }

}
