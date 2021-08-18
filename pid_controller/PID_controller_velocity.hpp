#ifndef PID_CONTROLLER_VELOCITY_HPP
#define PID_CONTROLLER_VELOCITY_HPP

#include "PID_controller_util.hpp"

namespace aca {

class PID_controller_velocity
{
private:
    const PID_Element pid_parameter;
    const float frequency;
    PID_Element operation;
    float operation_value = 0;
    float last_difference = 0;
    float last_proportional = 0;
    float last_operation_velocity = 0;
public:
    PID_controller_velocity(const PID_Element &pid_parameter, const float frequency);
    PID_controller_velocity(float proportional, float integral, float differential, const float frequency);
    void updateOperation(float difference);
    float getOperation();
    void resetOperation();
};

} // namespace aca

#endif //PID_CONTROLLER_VELOCITY_HPP
