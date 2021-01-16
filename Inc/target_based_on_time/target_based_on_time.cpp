#include "target_based_on_time.hpp"

TargetBasedOnTime::TargetBasedOnTime(){

}



void TargetBasedOnTime::set(float targetPosition, float initialPosition, float maxAcceleration, float maxVelocity){
	if (targetPosition != this->targetPosition || maxAcceleration != this->maxAcceleration || maxVelocity != this->maxVelocity){
		this->maxAcceleration = maxAcceleration;
		this->maxVelocity = maxVelocity;

		this->targetPosition = targetPosition;
		this->initialPosition = initialPosition;
		targetPositionDistance = abs(targetPosition-initialPosition);

		border = powf(maxVelocity, 2)*M_PI/(2*maxAcceleration);

		if (targetPositionDistance < border){
			maxVelocityThisTime = sqrtf(2*targetPositionDistance*maxAcceleration/M_PI);
		}else {
			maxVelocityThisTime = this->maxVelocity;
		}

		periodOfAcceleration = periodOfDeceleration = maxVelocity*M_PI/(4*maxAcceleration);
		periodOfConstantVelocity = 0;

		if (border < targetPositionDistance) {
			periodOfConstantVelocity = targetPositionDistance/maxVelocityThisTime;
		}
	}
}

void TargetBasedOnTime::set(float targetPositionDistance, float maxAcceleration, float maxVelocity){
	set(targetPositionDistance, 0, maxAcceleration, maxVelocity);
}

void TargetBasedOnTime::setTarget(float targetPosition){
	set(targetPosition, maxAcceleration, maxVelocity);
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
		position = targetPosition;
	}
}


float TargetBasedOnTime::getVelocityBasic(uint16_t time){
	return -maxVelocityThisTime /2 *cosf(2*maxAcceleration/maxVelocityThisTime*time);
}

float TargetBasedOnTime::getPositionBasic(uint16_t time){
	return -powf(maxVelocityThisTime, 2) /(4*maxAcceleration) *sinf(2*maxAcceleration /maxVelocityThisTime *time);
}



float TargetBasedOnTime::getVelocity(){
	if (initialPosition <= targetPosition){
		return velocity;
	}else {
		return -velocity;
	}
}

float TargetBasedOnTime::getPosition(){
	if (initialPosition <= targetPosition) {
		return position + initialPosition;
	}else {
		return -position + initialPosition;
	}
	return position;
}

float TargetBasedOnTime::getTimeRequired(){
	return periodOfAcceleration + periodOfConstantVelocity + periodOfDeceleration;
}
