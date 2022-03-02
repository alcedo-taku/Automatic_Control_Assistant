#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include <stdint.h>
#include <cmath>

namespace aca {

struct PID_Element{
    float proportional;
    float integral;
    float differential;
};

struct StableConditions{
	float allowable_error;
	uint16_t stable_time; // 初期値(0)の場合は判定しない(常にfalse)
};

class PID_controller
{
private:
	PID_Element pid_parameter;
	float frequency;
	PID_Element operation = {0,0,0};
	float operation_value;
	float last_operation_value;
	float last_difference = 0;
	StableConditions stable_conditions;
	uint16_t stable_time_counter;
	bool is_stable = false;

public:
	PID_controller(const PID_Element &pid_parameter, const float frequency, const StableConditions &stable_conditions);
	PID_controller(const PID_Element &pid_parameter, const float frequency);
	PID_controller(const PID_Element &pid_parameter);
	PID_controller(const float frequency);
	void init(const PID_Element &pid_parameter, const float frequency);
	void init(const PID_Element &pid_parameter);
	void init(const float frequency);
	void set_stable_conditions(const float allowable_error, const uint16_t stable_time);
	void update_operation(const float difference);
	void reset_integral();
	float get_operation();
	float get_operation_difference();
	bool get_is_stable();
};

} // namespace aca

#endif //PID_CONTROLLER_HPP
