#include "PID_controller_velocity.hpp"

PID_controller_velocity::PID_controller_velocity(
        const PID_Element &index,
        const float frequency
):
        index(index),
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

void PID_controller_velocity::setTarget(float target){
    this->target = target;
}

void PID_controller_velocity::updateOperation(float basis){
    float difference = target - basis;
    updateOperation_difference(difference);
}
void PID_controller_velocity::updateOperation_difference(float difference){
    operation.proportional = (difference - last_difference)*frequency;
    operation.integral = difference;
    operation.differential = (operation.proportional - last_proportional)*frequency;
    last_difference = difference;
    last_proportional = operation.proportional;

	float operation_velocity =
			operation.proportional*index.proportional
	           + operation.integral*index.integral
	           + operation.differential*index.differential;
	operation_value += (operation_velocity+last_operation_velocity)/frequency/2;

	last_operation_velocity = operation_velocity;


}

void PID_controller_velocity::updateOperation(float target, float basis){
    setTarget(target);
    updateOperation(basis);
}

float PID_controller_velocity::getOperation(){
    return operation_value;
}

void PID_controller_velocity::resetOperation(){
	operation_value = 0;
}


