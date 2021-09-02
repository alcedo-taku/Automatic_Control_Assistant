#include "coordinate_measurer.hpp"
#include <cmath>

CoordinateMeasurer::CoordinateMeasurer(uint16_t encoderCPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius){
	parameter.encoderCPR = encoderCPR * 4;
	parameter.radiusOfMeasureWheel = radiusOfMeasureWheel;
	parameter.attachmentRadius = attachmentRadius;
}

void CoordinateMeasurer::setData(EncoderCount *pEncoderCount){
	befCount = count;
	count = *pEncoderCount;
	return;
}

CoordinatePoint *CoordinateMeasurer::getCoord(){
	return &coord;
}

void CoordinateMeasurer::update(){
	calcRad();
	calcPoint();
}

void CoordinateMeasurer::overwriteCoord(CoordinatePoint coordinate){
	coord = coordinate;
}

float CoordinateMeasurer::convertCountToDistance(float deltaCount){
	return deltaCount * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (float)parameter.encoderCPR;
}

/*****************
 * CoordinateMeasurerLine
 ******************/

CoordinateMeasurerLine::CoordinateMeasurerLine(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius) : CoordinateMeasurer(encoderPPR, radiusOfMeasureWheel, attachmentRadius){

}

void CoordinateMeasurerLine::offset(CoordinatePoint *pCoordinate){
	offsetCoord = *pCoordinate;
}

void CoordinateMeasurerLine::calcRad(){
	if(count.encoder0 - count.encoder2)	coord.rad = offsetCoord.rad;
	else coord.rad = (count.encoder0 - count.encoder2) * M_PI * parameter.attachmentRadius / (parameter.encoderCPR * parameter.attachmentRadius) + offsetCoord.rad;
}

void CoordinateMeasurerLine::calcPoint(){
	float sine;
	float cosine;
	float delta_y , delta_x;

	cosine = cos(coord.rad);
	sine = sin(coord.rad);

	delta_y = (count.encoder0 + count.encoder2 - befCount.encoder0 - befCount.encoder2) / 2.0;
	delta_x = count.encoder1 - befCount.encoder1;

	coord.x += convertCountToDistance(delta_x) * cosine - convertCountToDistance(delta_y) * sine;
	coord.y += convertCountToDistance(delta_y) * cosine + convertCountToDistance(delta_x) * sine;
}


/********************
 * CoordinateMeasurerTriangle
 ********************/

CoordinateMeasurerTriangle::CoordinateMeasurerTriangle(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius) : CoordinateMeasurer(encoderPPR, radiusOfMeasureWheel, attachmentRadius){

}

void CoordinateMeasurerTriangle::offset(CoordinatePoint *pCoordinate){
    coord = coord + *pCoordinate - offsetCoord;
	offsetCoord = *pCoordinate;
}

void CoordinateMeasurerTriangle::calcRad(){
	coord.rad += (count.encoder0 + count.encoder1 + count.encoder2 - count.encoder0 - count.encoder1 - count.encoder2) * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (parameter.attachmentRadius * parameter.encoderCPR * 3.0);
}

void CoordinateMeasurerTriangle::calcPoint(){
	float sine;
	float cosine;
	float delta_y , delta_x;

	cosine = cos(coord.rad);
	sine = sin(coord.rad);

	delta_y = (count.encoder2 - befCount.encoder2 - (count.encoder1 - befCount.encoder1)) * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (sqrt(3.0) * parameter.encoderCPR);
	delta_x = (count.encoder1 + befCount.encoder1 + count.encoder2 - befCount.encoder2 - 2 * (count.encoder0 - befCount.encoder0)) * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (3.0 * parameter.encoderCPR);

	coord.x += convertCountToDistance(delta_x) * cosine - convertCountToDistance(delta_y) * sine;
	coord.y += convertCountToDistance(delta_y) * cosine + convertCountToDistance(delta_x) * sine;
}
