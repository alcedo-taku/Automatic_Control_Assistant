#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

namespace aca {

struct PID_Element{
    float proportional;
    float integral;
    float differential;
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

public:
	PID_controller(const PID_Element &pid_parameter, const float frequency);
	PID_controller(const PID_Element &pid_parameter);
	PID_controller(const float frequency);
	void init(const PID_Element &pid_parameter, const float frequency);
	void init(const PID_Element &pid_parameter);
	void init(const float frequency);
	void updateOperation(const float difference);
	void resetIntegral();
	float getOperation();
	float getOperationDifference();
};

} // namespace aca

#endif //PID_CONTROLLER_HPP
