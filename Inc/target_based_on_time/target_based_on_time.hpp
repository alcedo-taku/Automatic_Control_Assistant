#ifndef AUTOMATIC_CONTROL_ASSISTANT_TARGET_BASED_ON_TIME
#define AUTOMATIC_CONTROL_ASSISTANT_TARGET_BASED_ON_TIME

#include "math.h"
#include "main.h"

class TargetBasedOnTime{
public:
	TargetBasedOnTime();
	void set(float targetPositionDistance, float maxAcceleration, float maxVelocity);
	void setTarget(float targetPosition);
	void start();
	void update(uint16_t time);
	void update();
	float getPosition();
	float getVelocity();
	float getTimeRequired();
private:
	float targetPositionDistance;
	float maxAcceleration;
	float maxVelocity;
	float maxVelocityThisTime;
	float borderDistance;
	uint16_t startingTime;

	float position;
	float velocity;
	float getPositionBasic(uint16_t time);
	float getVelocityBasic(uint16_t time);

	float periodOfAcceleration;
	float periodOfConstantVelocity;
	float periodOfDeceleration;
};

#endif //AUTOMATIC_CONTROL_ASSISTANT_TARGET_BASED_ON_TIME
