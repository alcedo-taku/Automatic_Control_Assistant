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
    float proportional,
    float integral,
    float differential,
    const float frequency
):
    PID_controller_velocity(PID_Element{proportional, integral, differential}, frequency)
{
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
