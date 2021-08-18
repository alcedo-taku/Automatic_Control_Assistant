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

PID_controller::PID_controller(const PID_Element &pid_parameter):
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

PID_controller::PID_controller(const float frequency):
    PID_controller(PID_Element{0, 0, 0}, 0)
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
    init(pid_parameter, 0)
}

void PID_controller::init(const float proportional, const float integral, const float differential){
    init(PID_Element{proportional, integral, differential}, 0
}

void PID_controller::init(const float frequency){
    init(PID_Element{0, 0, 0}, 0)
}


void PID_controller::updateOperation(const float difference){
	operation.proportional = difference;
	operation.integral += (last_difference + difference) / 2 / frequency;
	operation.differential = (difference - last_difference)*frequency;
	last_difference = difference;
}

void PID_controller::resetIntegral(){
	operation.integral = 0;
}

float PID_controller::getOperation(){
	return operation.proportional * pid_parameter.proportional
		 + operation.integral * pid_parameter.integral
		 + operation.differential * pid_parameter.differential;
}

} // namespace aca