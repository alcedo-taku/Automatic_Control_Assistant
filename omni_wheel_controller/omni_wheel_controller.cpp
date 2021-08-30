#include"omni_wheel_controller.hpp"

namespace aca {

template <std::size_t NUMBER_OF_OMNI_WHEELS>
OmniWheelController<NUMBER_OF_OMNI_WHEELS>::OmniWheelController(
    std::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS> mechanic_parameter)
{
	for (uint8_t i=0; i<NUMBER_OF_OMNI_WHEELS; i++) {
		coefficient[i].sin_value = std::sin(mechanic_parameter[i].wheel_angle);
		coefficient[i].cos_value = std::cos(mechanic_parameter[i].wheel_angle);
		coefficient[i].distance_from_center = mechanic_parameter[i].distance_from_center;
	}
}

template <std::size_t NUMBER_OF_OMNI_WHEELS>
CoordinateSystem_3D OmniWheelController<NUMBER_OF_OMNI_WHEELS>::rotation_matrix(CoordinateSystem_3D field_velocity, float angle){
    CoordinateSystem_3D robot_velocity;
    robot_velocity.x =  field_velocity.x * std::cos(angle) + field_velocity.y * std::sin(angle);
    robot_velocity.y = -field_velocity.x * std::sin(angle) + field_velocity.y * std::cos(angle);
    robot_velocity.angle = field_velocity.angle;
    return robot_velocity;
}


template <std::size_t NUMBER_OF_OMNI_WHEELS>
void OmniWheelController<NUMBER_OF_OMNI_WHEELS>::convert_each_wheel(CoordinateSystem_3D robot_velocity){
    for (uint8_t i=0; i<NUMBER_OF_OMNI_WHEELS; i++) {
        wheel_velocity[i] = robot_velocity.x * coefficient[i].cos_value + robot_velocity.y * coefficient[i].sin_value + robot_velocity.angle * coefficient[i].distance_from_center;
    }
}

template <std::size_t NUMBER_OF_OMNI_WHEELS>
void OmniWheelController<NUMBER_OF_OMNI_WHEELS>::update(CoordinateSystem_3D field_velocity, float angle){
    convert_each_wheel( rotation_matrix(field_velocity, angle) );
}

template <std::size_t NUMBER_OF_OMNI_WHEELS>
void OmniWheelController<NUMBER_OF_OMNI_WHEELS>::update(float field_velocity_x, float field_velocity_y, float field_velocity_angle, float angle){
    update( CoordinateSystem_3D{field_velocity_x, field_velocity_y, field_velocity_angle}, angle );
}

template <std::size_t NUMBER_OF_OMNI_WHEELS>
std::array<int16_t, NUMBER_OF_OMNI_WHEELS> OmniWheelController<NUMBER_OF_OMNI_WHEELS>::get_wheel_velocity(){
    return wheel_velocity;
}

template <std::size_t NUMBER_OF_OMNI_WHEELS>
int16_t OmniWheelController<NUMBER_OF_OMNI_WHEELS>::get_wheel_velocity(uint8_t wheel_number){
	return wheel_velocity[wheel_number];
}

} // namespace aca
