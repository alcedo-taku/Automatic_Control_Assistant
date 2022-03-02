#include "PID_controller.hpp"

namespace aca {

PID_controller::PID_controller(
	const PID_Element &pid_parameter,
	const float frequency,
	const StableConditions &stable_conditions
):
	pid_parameter(pid_parameter),
	frequency(frequency),
	stable_conditions(stable_conditions)
{
	operation.integral = 0;
}

PID_controller::PID_controller(
	const PID_Element &pid_parameter,
	const float frequency
):
	PID_controller(pid_parameter, frequency, StableConditions{0,0})
{
}

PID_controller::PID_controller(
	const PID_Element &pid_parameter
):
    PID_controller(pid_parameter, 0)
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
    reset_integral();
}

void PID_controller::init(const PID_Element &pid_parameter){
    init(pid_parameter, frequency);
}

void PID_controller::init(const float frequency){
    init(pid_parameter, frequency);
}


void PID_controller::set_stable_conditions(const StableConditions &stable_conditions){
	this->stable_conditions = stable_conditions;
}

void PID_controller::update_operation(const float difference){
	last_operation_value = operation_value;
	operation.proportional = difference;
	operation.integral += (last_difference + difference) / 2 / frequency;
	operation.differential = (difference - last_difference) * frequency;
	operation_value = operation.proportional * pid_parameter.proportional
					+ operation.integral     * pid_parameter.integral
					+ operation.differential * pid_parameter.differential;

	/* 許容誤差内に一定時間とどまった時、安定したとみなす */
	if( std::fabs(difference) < stable_conditions.allowable_error ){
		stable_time_counter += 1000.0f / frequency;
	}else{
		stable_time_counter = 0;
	}
	if( stable_conditions.stable_time <= stable_time_counter && stable_conditions.stable_time != 0 ){
		is_stable = true;
	}else{
		is_stable = false;
	}

	last_difference = difference;
}

void PID_controller::reset_integral(){
	last_operation_value -= operation.integral * pid_parameter.integral;
	operation.integral = 0;
}

float PID_controller::get_operation(){
	if( is_stable == true ){
		return 0;
	}else{
		return operation_value;
	}
}

float PID_controller::get_operation_difference(){
	return operation_value - last_operation_value;
}

bool PID_controller::get_is_stable(){
	return is_stable;
}

} // namespace aca
