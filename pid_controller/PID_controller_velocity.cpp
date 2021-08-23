#include "PID_controller_velocity.hpp"

namespace aca {

PID_controller_velocity::PID_controller_velocity(
    const PID_Element &pid_parameter,
    const float frequency
):
    pid_parameter(pid_parameter),
    frequency(frequency)
{
    operation.integral = 0;
}

PID_controller_velocity::PID_controller_velocity(
    const float proportional,
    const float integral,
    const float differential,
    const float frequency
):
    PID_controller_velocity(PID_Element{proportional, integral, differential}, frequency)
{
}

PID_controller_velocity::PID_controller_velocity(const PID_Element &pid_parameter):
    PID_controller_velocity(pid_parameter, 0)
{
}

PID_controller_velocity::PID_controller_velocity(
    const float proportional,
    const float integral,
    const float differential
):
    PID_controller_velocity(PID_Element{proportional, integral, differential}, 0)
{
}

PID_controller_velocity::PID_controller_velocity(const float frequency):
    PID_controller_velocity(PID_Element{0, 0, 0}, frequency)
{
}

void PID_controller_velocity::init(const PID_Element &pid_parameter, const float frequency){
    this->pid_parameter = pid_parameter;
    this->frequency = frequency;
    operation.integral = 0;
}

void PID_controller_velocity::init(const float proportional, const float integral, const float differential, const float frequency){
    init(PID_Element{proportional, integral, differential}, frequency);
}

void PID_controller_velocity::init(const PID_Element &pid_parameter){
    init(pid_parameter, frequency);
}

void PID_controller_velocity::init(const float proportional, const float integral, const float differential){
    init(PID_Element{proportional, integral, differential}, frequency);
}

void PID_controller_velocity::init(const float frequency){
    init(pid_parameter, frequency);
}

void PID_controller_velocity::updateOperation(float difference){
    operation.proportional = (difference - last_difference) * frequency;
    operation.integral = difference;
    operation.differential = (operation.proportional - last_proportional) * frequency;
    last_difference = difference;
    last_proportional = operation.proportional;

	float operation_velocity =
			operation.proportional * pid_parameter.proportional
	           + operation.integral * pid_parameter.integral
	           + operation.differential * pid_parameter.differential;
	operation_value += (operation_velocity + last_operation_velocity) / 2 / frequency;

	last_operation_velocity = operation_velocity;
}

float PID_controller_velocity::getOperation(){
    return operation_value;
}

void PID_controller_velocity::resetOperation(){
	operation_value = 0;
}

} // namespace aca
