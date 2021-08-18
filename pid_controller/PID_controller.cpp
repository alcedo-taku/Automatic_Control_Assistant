#include "PID_controller.hpp"

namespace aca {

PID_controller::PID_controller(
	const PID_Element &pid_parameter,
	const float frequency
):
        pid_parameter(pid_parameter),
        frequency(frequency)
{
	operation.integral = 0;
}

PID_controller::PID_controller(
	float proportional,
	float integral,
	float differential,
	const float frequency
):
	PID_controller(PID_Element{proportional, integral, differential}, frequency)
{
}

void PID_controller::updateOperation(float difference){
	operation.proportional = difference;
	operation.integral += (last_difference + difference) / 2 / frequency;
	operation.differential = (difference - last_difference)*frequency;
	last_difference = difference;
}

void PID_controller::resetIntegral(){
	operation.integral = 0;
}

float PID_controller::getOperation(){
	return operation.proportional*pid_parameter.proportional
		 + operation.integral*pid_parameter.integral
		 + operation.differential*pid_parameter.differential;
}

} // namespace aca