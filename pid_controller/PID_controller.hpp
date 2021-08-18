#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP
#include "PID_controller_util.hpp"

namespace aca {

class PID_controller
{
private:
	const PID_Element index;
	const float frequency;
	PID_Element operation;
	float last_difference = 0;

public:
	PID_controller(const PID_Element &index, const float frequency);
	PID_controller(float proportional, float integral, float differential, const float frequency);
	void updateOperation(float current);
	void resetIntegral();
	float getOperation();
};

} // namespace aca

#endif //PID_CONTROLLER_HPP
