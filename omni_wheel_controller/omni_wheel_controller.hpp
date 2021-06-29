#ifndef CONVERSION_VELOCITY_FIELD_TO_WHEEL
#define CONVERSION_VELOCITY_FIELD_TO_WHEEL
#include<array>
#include<cmath>

class ConversionVelocityFieldToWheel{
private:
    float field_velocity_x;
    float field_velocity_y;
    float rad;
    float robot_radius;

    float robot_velocity_x;
    float robot_velocity_y;
    std::array<int16_t, 4> omni_velocity;

    static constexpr float cos45 = 1 / std::sqrt(2);

    void setField(float,float,float);
    void setRobot(float);
public:
    ConversionVelocityFieldToWheel(
            float robot_radius
    );
    void setVelocity(float,float,float,float);
    std::array<int16_t, 4> getOmni();
};

#endif //CONVERSION_VELOCITY_FIELD_TO_WHEEL
