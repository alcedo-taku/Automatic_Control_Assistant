#ifndef WHEEL_WHEEL_CONTROLLER_HPP_
#define WHEEL_WHEEL_CONTROLLER_HPP_

#include <array>
#include <cmath>
#include "coordinate.hpp"

namespace aca {

template <std::size_t NUMBER_OF_OMNI_WHEELS, typename OUTPUT_TYPE>
class WheelController{
protected:
    std::array<OUTPUT_TYPE, NUMBER_OF_OMNI_WHEELS> wheel_velocity;
private:
    Coordinate<float> rotation_matrix(Coordinate<float> field_velocity, float angle){
        Coordinate<float> robot_velocity;
        robot_velocity.x =  field_velocity.x * std::cos(angle) + field_velocity.y * std::sin(angle);
        robot_velocity.y = -field_velocity.x * std::sin(angle) + field_velocity.y * std::cos(angle);
        robot_velocity.angle = field_velocity.angle;
        return robot_velocity;
    };
    virtual void convert_each_wheel(Coordinate<float> robot_velocity) = 0;
public:
    void update(Coordinate<float> field_velocity, float angle){
        convert_each_wheel( rotation_matrix(field_velocity, angle) );
    };
    void update(float field_velocity_x, float field_velocity_y, float angular_velocity, float angle){
        update( Coordinate<float>{field_velocity_x, field_velocity_y, angular_velocity}, angle );
    };
    std::array<OUTPUT_TYPE, NUMBER_OF_OMNI_WHEELS> get_wheel_velocity(){
        return wheel_velocity;
    };
    OUTPUT_TYPE get_wheel_velocity(uint8_t wheel_number){
        return wheel_velocity[wheel_number];
    };
};

/*****************
 * OmniWheelController
 ******************/

struct MechanicParameter{
    float wheel_angle;
    float distance_from_center;
};

struct Coefficient{
    float sin_value;
    float cos_value;
    float distance_from_center;
};

template <std::size_t NUMBER_OF_OMNI_WHEELS, typename OUTPUT_TYPE>
class OmniWheelController : public WheelController<NUMBER_OF_OMNI_WHEELS, OUTPUT_TYPE>{
private:
    std::array<Coefficient, NUMBER_OF_OMNI_WHEELS> coefficient;
//    std::array<OUTPUT_TYPE, NUMBER_OF_OMNI_WHEELS> wheel_velocity;

    void convert_each_wheel(Coordinate<float> robot_velocity) override {
        for (uint8_t i=0; i<NUMBER_OF_OMNI_WHEELS; i++) {
        	this->wheel_velocity[i] = robot_velocity.x * coefficient[i].cos_value + robot_velocity.y * coefficient[i].sin_value + robot_velocity.angle * coefficient[i].distance_from_center;
        }
    };
public:
    OmniWheelController(std::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS> mechanic_parameter){
        for (uint8_t i=0; i<NUMBER_OF_OMNI_WHEELS; i++) {
            coefficient[i].sin_value            = std::sin(mechanic_parameter[i].wheel_angle);
            coefficient[i].cos_value            = std::cos(mechanic_parameter[i].wheel_angle);
            coefficient[i].distance_from_center = mechanic_parameter[i].distance_from_center;
        }
    };
};

/*****************
 * MecanumWheelController
 ******************/

template <typename OUTPUT_TYPE>
class MecanumWheelController : public WheelController<4, OUTPUT_TYPE> {
private:
    float a,b;
    void convert_each_wheel(Coordinate<float> robot_velocity) override {
    	this->wheel_velocity[0] = -robot_velocity.x + robot_velocity.y +  (a+b)*robot_velocity.angle;
    	this->wheel_velocity[1] =  robot_velocity.x + robot_velocity.y   -(a+b)*robot_velocity.angle;
    	this->wheel_velocity[2] = -robot_velocity.x + robot_velocity.y   -(a+b)*robot_velocity.angle;
    	this->wheel_velocity[3] =  robot_velocity.x + robot_velocity.y +  (a+b)*robot_velocity.angle;
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
};

} // namespace aca

#endif // WHEEL_WHEEL_CONTROLLER_HPP_
