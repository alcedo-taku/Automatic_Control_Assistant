#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP
#include "PID_controller_util.hpp"

class PID_controller
{
private:
	const PID_Element index;
	const float frequency;
	PID_Element operation;
	float target;
	float last_difference = 0;

public:
	PID_controller(const PID_Element &index,const float frequency);
	PID_controller(float proportional, float integral, float differential,const float frequency);
	void setTarget(float target);
	void updateOperation(float basis);
	void updateOperation(float target, float basis);
	void resetIntegral();
	float getOperation();
	
};
#endif //PID_CONTROLLER_HPP
