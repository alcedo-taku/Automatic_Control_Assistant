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
	const float proportional,
	const float integral,
	const float differential,
	const float frequency
):
	PID_controller(PID_Element{proportional, integral, differential}, frequency)
{
}

PID_controller::PID_controller(
	const PID_Element &pid_parameter
):
    PID_controller(pid_parameter, 0)
{
}

PID_controller::PID_controller(
    const float proportional,
    const float integral,
    const float differential
):
    PID_controller(PID_Element{proportional, integral, differential}, 0)
{
}

PID_controller::PID_controller(
	const float frequency
):
    PID_controller(PID_Element{0, 0, 0}, frequency)
{
}

void PID_controller::init(const PID_Element &pid_parameter, const float frequency){
    this->pid_parameter = pid_parameter;
    this->frequency = frequency;
    operation.integral = 0;
}

void PID_controller::init(const float proportional, const float integral, const float differential, const float frequency){
    init(PID_Element{proportional, integral, differential}, frequency);
}

void PID_controller::init(const PID_Element &pid_parameter){
    init(pid_parameter, frequency);
}

void PID_controller::init(const float proportional, const float integral, const float differential){
    init(PID_Element{proportional, integral, differential}, frequency);
}

void PID_controller::init(const float frequency){
    init(pid_parameter, frequency);
}


void PID_controller::updateOperation(const float difference){
	last_operation_value = operation_value;
	operation.proportional = difference;
	operation.integral += (last_difference + difference) / 2 / frequency;
	operation.differential = (difference - last_difference)*frequency;
	operation_value = operation.proportional * pid_parameter.proportional
					 + operation.integral * pid_parameter.integral
					 + operation.differential * pid_parameter.differential;
	last_difference = difference;
}

void PID_controller::resetIntegral(){
	last_operation_value -= operation.integral * pid_parameter.integral;
	operation.integral = 0;
}

float PID_controller::getOperation(){
	return operation_value;
}

float PID_controller::getOperationDifference(){
	return operation_value - last_operation_value;
}

} // namespace aca
