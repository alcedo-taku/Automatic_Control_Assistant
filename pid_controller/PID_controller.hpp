#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP
#include "PID_controller_util.hpp"

namespace aca {

class PID_controller
{
private:
	PID_Element pid_parameter;
	float frequency;
	PID_Element operation;
	float last_difference = 0;

public:
	PID_controller(const PID_Element &pid_parameter, const float frequency);
	PID_controller(const float proportional, const float integral, const float differential, const float frequency);
	PID_controller(const PID_Element &pid_parameter);
	PID_controller(const float proportional, const float integral, const float differential);
	PID_controller(const float frequency);
	void init(const PID_Element &pid_parameter, const float frequency);
	void init(const float proportional, const float integral, const float differential, const float frequency);
	void init(const PID_Element &pid_parameter);
	void init(const float proportional, const float integral, const float differential);
	void init(const float frequency);
	void updateOperation(const float difference);
	void resetIntegral();
	float getOperation();
};

} // namespace aca

#endif //PID_CONTROLLER_HPP
