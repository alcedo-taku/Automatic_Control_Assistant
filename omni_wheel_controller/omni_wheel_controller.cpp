#include"omni_wheel_controller.hpp"

namespace aca {

OmniWheelController::OmniWheelController(
    constexpr std::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS> mechanic_parameter
):
    mechanicParameter(mechanic_parameter.)
{
    std::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS> mechanic_parameter;
    mechanic_parameter[0].
}

CoordinateSystem_3D OmniWheelController::rotation_matrix(CoordinateSystem_3D field_velocity, float angle){
    CoordinateSystem_3D robot_velocity;
    robot_velocity.x =  field_velocity.x * std::cos(angle) + field_velocity.y * std::sin(angle);
    robot_velocity.y = -field_velocity.x * std::sin(angle) + field_velocity.y * std::cos(angle);
    robot_velocity.angle = field_velocity.angle;
    return robot_velocity;
}

void OmniWheelController::convert_each_wheel(CoordinateSystem_3D robot_velocity){
    for (const auto& e : wheel_velocity) {
        wheel_velocity = robot_velocity.x*cos(-3.0/4.0*M_PI) + robot_velocity.y*sin(-3.0/4.0*M_PI) + robot_velocity.angle*robotRadius;
    }
}

void OmniWheelController::update(CoordinateSystem_3D field_velocity, float angle){
    convert_each_wheel( rotation_matrix(field_velocity, angle) );
}

void OmniWheelController::update(float field_velocity_x, float field_velocity_y, float field_velocity_angle, float angle){
    update( CoordinateSystem_3D{field_velocity_x, field_velocity_y, field_velocity_angle}, angle );
}

std::array<int16_t, NUMBER_OF_OMNI_WHEELS> OmniWheelController::get_wheel_velocity(){
    return wheel_velocity;
}

} // namespace aca