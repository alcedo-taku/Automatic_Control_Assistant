#ifndef AUTOMATIC_CONTROL_ASSISTANT_TARGET_BASED_ON_TIME
#define AUTOMATIC_CONTROL_ASSISTANT_TARGET_BASED_ON_TIME

#include "math.h"
#include <cstdint>

class TargetBasedOnTime{
public:
	TargetBasedOnTime();
	void set(float targetPosition, float initialPosition, float maxAcceleration, float maxVelocity);
	void set(float targetPositionDistance, float maxAcceleration, float maxVelocity);
	void setTarget(float targetPosition);
	void update(uint16_t time);
	float getPosition();
	float getVelocity();
	float getTimeRequired(); //目標値に達するまでの時間を返す
private:
	float targetPositionDistance;
	float targetPosition;
	float initialPosition;
	float maxAcceleration;
	float maxVelocity;
	float maxVelocityThisTime;
	float borderDistance; //加速しきれる最小距離

	float position;
	float velocity;
	float getPositionBasic(uint16_t time);
	float getVelocityBasic(uint16_t time);

	float periodOfAcceleration; //加速時間
	float periodOfConstantVelocity; //等速時間
	float periodOfDeceleration; //減速時間
};

#endif //AUTOMATIC_CONTROL_ASSISTANT_TARGET_BASED_ON_TIME
