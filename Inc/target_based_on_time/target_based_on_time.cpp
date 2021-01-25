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

		//加速しきれる最小距離の計算
		borderDistance = powf(maxVelocity, 2)*M_PI/(2*maxAcceleration);

		//最高速度の計算
		if (targetPositionDistance < borderDistance){
			maxVelocityThisTime = sqrtf(2*targetPositionDistance*maxAcceleration/M_PI);
		}else {
			maxVelocityThisTime = this->maxVelocity;
		}

		//加速時間、等速時間、減速時間の計算
		periodOfAcceleration = periodOfDeceleration = maxVelocityThisTime*M_PI/(2*maxAcceleration);
		periodOfConstantVelocity = 0;
		if (borderDistance < targetPositionDistance) {
			periodOfConstantVelocity = (targetPositionDistance-borderDistance)/maxVelocityThisTime;
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
		position = getPositionBasic(periodOfAcceleration) + maxVelocityThisTime*(time-periodOfAcceleration);
	}else if (periodOfAcceleration + periodOfConstantVelocity < time  &&  time <= periodOfAcceleration + periodOfConstantVelocity + periodOfDeceleration) { //period of deceleration
		velocity = getVelocityBasic(time-periodOfConstantVelocity);
		position = getPositionBasic(time-periodOfConstantVelocity) + maxVelocityThisTime*periodOfConstantVelocity;
	}else { //目標値に到達後
		velocity = 0;
		position = targetPosition;
	}

	//初期値と目標値の大小関係によって、速度と位置の正負を変える
    if (initialPosition > targetPosition){
        velocity = -velocity;
        position = -position;
    }
    //初期値を足す
    position += initialPosition;
}


float TargetBasedOnTime::getVelocityBasic(float time){
	return -maxVelocityThisTime /2 *cosf(2*maxAcceleration/maxVelocityThisTime*time) + maxVelocityThisTime/2;
}

float TargetBasedOnTime::getPositionBasic(float time){
	return -powf(maxVelocityThisTime, 2) /(4*maxAcceleration) *sinf(2*maxAcceleration /maxVelocityThisTime *time)+ maxVelocityThisTime/2*time;
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
