#include"omni_wheel_controller.hpp"

OmniWheelController::OmniWheelController(
        float robot_radius
):
        robot_radius(robot_radius)
{

}

void OmniWheelController::setField(float field_velosity_x,float field_velosity_y, float rad){
    robot_velocity_x = field_velosity_x * std::cos(rad) + field_velosity_y * std::sin(rad);
    robot_velocity_y = -field_velosity_x * std::sin(rad) + field_velosity_y * std::cos(rad);
}

void OmniWheelController::setRobot(float angle_velocity){
    omni_velocity[0] = -cos45 * robot_velocity_x + cos45 * robot_velocity_y + (robot_radius * angle_velocity);
    omni_velocity[1] = -cos45 * robot_velocity_x - cos45 * robot_velocity_y + (robot_radius * angle_velocity);
    omni_velocity[2] = cos45 * robot_velocity_x - cos45 * robot_velocity_y + (robot_radius * angle_velocity);
    omni_velocity[3] = cos45 * robot_velocity_x + cos45 * robot_velocity_y + (robot_radius * angle_velocity);
}

void OmniWheelController::setVelocity(float field_velocity_x,float field_velocity_y,float angle_velocity,float rad){
    setField(field_velocity_x,field_velocity_y,rad);
    setRobot(angle_velocity);
}
std::array<int16_t, 4>OmniWheelController::getOmni(){
    return omni_velocity;
}
