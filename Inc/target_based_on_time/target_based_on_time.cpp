#include "target_based_on_time.hpp"

TargetBasedOnTime::TargetBasedOnTime(){

}

void TargetBasedOnTime::set(float targetPositionDistance, float maxAcceleration, float maxVelocity){
	if (targetPositionDistance != this->targetPositionDistance || maxAcceleration != this->maxAcceleration || maxVelocity != this->maxVelocity){
		this->maxAcceleration = maxAcceleration;
		this->maxVelocity = maxVelocity;
		this->targetPositionDistance = targetPositionDistance;
		borderDistance = powf(maxVelocity, 2)*M_PI/(2*maxAcceleration);

		if (targetPositionDistance < borderDistance){
			maxVelocityThisTime = sqrtf(2*targetPositionDistance*maxAcceleration/M_PI);
		}else {
			maxVelocityThisTime = this->maxVelocity;
		}
		periodOfAcceleration = periodOfDeceleration = maxVelocity*M_PI/(4*maxAcceleration);
		periodOfConstantVelocity = 0;
		if (borderDistance < targetPositionDistance) {
			periodOfConstantVelocity = targetPositionDistance/maxVelocityThisTime;
		}
		startingTime = HAL_GetTick();
	}
}

void TargetBasedOnTime::setTarget(float targetPositionDistance){
	set(targetPositionDistance, maxAcceleration, maxVelocity);
}

void TargetBasedOnTime::start(){
	startingTime = HAL_GetTick();
}



void TargetBasedOnTime::update(uint16_t time){
	if (0 <= time  &&  time < periodOfAcceleration) { //period of acceleration
		velocity = getVelocityBasic(time);
		position = getPositionBasic(time);
	}else if (periodOfAcceleration <= time  &&  time <= periodOfAcceleration + periodOfConstantVelocity) { //period of constant velocity
		velocity = maxVelocityThisTime;
		position = getPositionBasic(periodOfAcceleration) + maxVelocity*(time-periodOfAcceleration);
	}else if (periodOfAcceleration + periodOfConstantVelocity < time  &&  time <= periodOfAcceleration + periodOfConstantVelocity + periodOfDeceleration) { //period of deceleration
		velocity = getVelocityBasic(time-periodOfConstantVelocity);
		position = getPositionBasic(time-periodOfConstantVelocity);
	}else {
		velocity = 0;
		position = targetPositionDistance;
	}
}

void TargetBasedOnTime::update(){
	update((uint16_t)HAL_GetTick()-startingTime);
}



float TargetBasedOnTime::getVelocityBasic(uint16_t time){
	return -maxVelocityThisTime /2 *cosf(2*maxAcceleration/maxVelocityThisTime*time);
}

float TargetBasedOnTime::getPositionBasic(uint16_t time){
	return -powf(maxVelocityThisTime, 2) /(4*maxAcceleration) *sinf(2*maxAcceleration /maxVelocityThisTime *time);
}



float TargetBasedOnTime::getVelocity(){
	return velocity;
}

float TargetBasedOnTime::getPosition(){
	return position;
}

float TargetBasedOnTime::getTimeRequired(){
	return periodOfAcceleration + periodOfConstantVelocity + periodOfDeceleration;
}
