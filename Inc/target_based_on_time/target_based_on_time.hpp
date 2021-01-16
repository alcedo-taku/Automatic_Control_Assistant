#ifndef AUTOMATIC_CONTROL_ASSISTANT_TARGET_BASED_ON_TIME
#define AUTOMATIC_CONTROL_ASSISTANT_TARGET_BASED_ON_TIME

#include "math.h"
#include "main.h"

class TargetBasedOnTime{
public:
	TargetBasedOnTime();
	void set(float targetPosition, float initialPosition, float maxAcceleration, float maxVelocity);
	void set(float targetPositionDistance, float maxAcceleration, float maxVelocity);
	void setTarget(float targetPosition);
	void update(uint16_t time);
	float getPosition();
	float getVelocity();
	float getTimeRequired();
private:
	float targetPositionDistance;
	float targetPosition;
	float initialPosition;
	float maxAcceleration;
	float maxVelocity;
	float maxVelocityThisTime;
	float borderDistance;

	float position;
	float velocity;
	float getPositionBasic(uint16_t time);
	float getVelocityBasic(uint16_t time);

	float periodOfAcceleration;
	float periodOfConstantVelocity;
	float periodOfDeceleration;
};

#endif //AUTOMATIC_CONTROL_ASSISTANT_TARGET_BASED_ON_TIME
