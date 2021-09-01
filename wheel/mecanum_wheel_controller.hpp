#ifndef MECANUM_WHEEL_CONTROLLER_HPP
#define MECANUM_WHEEL_CONTROLLER_HPP

#include <array>
#include <cmath>
#include "coordinate.hpp"

namespace aca {

template <typename OUTPUT_TYPE>
class MecanumWheelController {
private:
    std::array<OUTPUT_TYPE, 4> wheel_velocity;
    float a,b;

    Coordinate<float> rotation_matrix(Coordinate<float> field_velocity, float angle){
        Coordinate<float> robot_velocity;
        robot_velocity.x =  field_velocity.x * std::cos(angle) + field_velocity.y * std::sin(angle);
        robot_velocity.y = -field_velocity.x * std::sin(angle) + field_velocity.y * std::cos(angle);
        robot_velocity.angle = field_velocity.angle;
        return robot_velocity;
    };
    void convert_each_wheel(Coordinate<float> robot_velocity){
        wheel_velocity[0] = -robot_velocity.x + robot_velocity.y +  (a+b)*robot_velocity.angle;
        wheel_velocity[1] =  robot_velocity.x + robot_velocity.y   -(a+b)*robot_velocity.angle;
        wheel_velocity[2] = -robot_velocity.x + robot_velocity.y   -(a+b)*robot_velocity.angle;
        wheel_velocity[3] =  robot_velocity.x + robot_velocity.y +  (a+b)*robot_velocity.angle;
    };
public:
    MecanumWheelController(
        float a,
        float b
    ):
        a(a),
        b(b)
    {
    };
    void update(Coordinate<float> field_velocity, float angle){
        convert_each_wheel( rotation_matrix(field_velocity, angle) );
    };
    void update(float field_velocity_x, float field_velocity_y, float angular_velocity, float angle){
        update( Coordinate<float>{field_velocity_x, field_velocity_y, angular_velocity}, angle );
    };
    std::array<OUTPUT_TYPE, 4> get_wheel_velocity(){
        return wheel_velocity;
    };
    OUTPUT_TYPE get_wheel_velocity(uint8_t wheel_number){
        return wheel_velocity[wheel_number];
    };
};

} // namespace aca

#endif //MECANUM_WHEEL_CONTROLLER_HPP
