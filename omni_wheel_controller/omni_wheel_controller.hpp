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
    float sit_value;
    float cos_value;
    float distance_from_center;
};

struct CoordinateSystem_3D{
    float x;
    float y;
    float angle;
};

template <int NUMBER_OF_OMNI_WHEELS>
class OmniWheelController{
private:
    CoordinateSystem_3D field_velocity;
    std::array<Coefficient, NUMBER_OF_OMNI_WHEELS> coefficient;
    std::array<int16_t, NUMBER_OF_OMNI_WHEELS> wheel_velocity;

    CoordinateSystem_3D rotation_matrix(CoordinateSystem_3D field_velocity, float angle);
    void convert_each_wheel(CoordinateSystem_3D robot_velocity);
public:
    constexpr OmniWheelController(std::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS> mechanic_parameter);
    void update(CoordinateSystem_3D field_velocity, float angle);
    void update(float field_velocity_x, float field_velocity_y, float field_velocity_angle, float angle);
    std::array<int16_t, NUMBER_OF_OMNI_WHEELS> get_wheel_velocity();
    int16_t get_wheel_velocity(uint8_t wheel_number);
};

} // namespace aca

#endif //OMNI_WHEEL_CONTROLLER
