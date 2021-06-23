#include "PID_controller.hpp"

PID_controller::PID_controller(
	const PID_Element &index,
	const float frequency
):
        index(index),
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
	return operation.proportional*index.proportional
		 + operation.integral*index.integral
		 + operation.differential*index.differential;
}
