#ifndef OMNI_WHEEL_CONTROLLER
#define OMNI_WHEEL_CONTROLLER
#include<array>
#include<cmath>

namespace aca {

struct MechanicParameter{
    float wheel_angle;
    float distance_from_center;
};

struct Coefficient{
    float sin_value;
    float cos_value;
    float distance_from_center;
};

template <typename T>
struct Coordinate{
    T x;
    T y;
    T angle;
};

template <std::size_t NUMBER_OF_OMNI_WHEELS, typename OUTPUT_TYPE>
class OmniWheelController{
private:
    std::array<Coefficient, NUMBER_OF_OMNI_WHEELS> coefficient;
    std::array<OUTPUT_TYPE, NUMBER_OF_OMNI_WHEELS> wheel_velocity;

    Coordinate<float> rotation_matrix(Coordinate<float> field_velocity, float angle){
        Coordinate<float> robot_velocity;
        robot_velocity.x =  field_velocity.x * std::cos(angle) + field_velocity.y * std::sin(angle);
        robot_velocity.y = -field_velocity.x * std::sin(angle) + field_velocity.y * std::cos(angle);
        robot_velocity.angle = field_velocity.angle;
        return robot_velocity;
    };
    void convert_each_wheel(Coordinate<float> robot_velocity){
        for (uint8_t i=0; i<NUMBER_OF_OMNI_WHEELS; i++) {
            wheel_velocity[i] = robot_velocity.x * coefficient[i].cos_value + robot_velocity.y * coefficient[i].sin_value + robot_velocity.angle * coefficient[i].distance_from_center;
        }
    };
public:
    OmniWheelController(std::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS> mechanic_parameter){
        for (uint8_t i=0; i<NUMBER_OF_OMNI_WHEELS; i++) {
            coefficient[i].sin_value = std::sin(mechanic_parameter[i].wheel_angle);
            coefficient[i].cos_value = std::cos(mechanic_parameter[i].wheel_angle);
            coefficient[i].distance_from_center = mechanic_parameter[i].distance_from_center;
        }
    };
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

} // namespace aca

#endif //OMNI_WHEEL_CONTROLLER
