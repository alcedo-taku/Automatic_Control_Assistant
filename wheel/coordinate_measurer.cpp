#include "coordinate_measurer.hpp"
#include <cmath>

CoordinateMeasurer::CoordinateMeasurer(uint16_t encoderCPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius){
	parameter.encoderCPR = encoderCPR * 4;
	parameter.radiusOfMeasureWheel = radiusOfMeasureWheel;
	parameter.attachmentRadius = attachmentRadius;
}

void CoordinateMeasurer::setData(std::array<int32_t,3> *pEncoderCount){
	befCount = count;
	count = *pEncoderCount;
	return;
}

CoordinatePoint *CoordinateMeasurer::get_coordinate(){
	return &coordinate;
}

void CoordinateMeasurer::update(){
	calcRad();
	calcPoint();
}

void CoordinateMeasurer::overwriteCoord(CoordinatePoint coordinate){
    this->coordinate = coordinate;
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
	offset_coordinate = *pCoordinate;
}

void CoordinateMeasurerLine::calcRad(){
    if(count[0] - count[2])	{
        coordinate.rad = offset_coordinate.rad;
    } else {
        coordinate.rad = (count[0] - count[2]) * M_PI * parameter.attachmentRadius / (parameter.encoderCPR * parameter.attachmentRadius) + offset_coordinate.rad;
    }
}

void CoordinateMeasurerLine::calcPoint(){
	float sin_value;
	float cos_value;
	float delta_y , delta_x;

	cos_value = cos(coordinate.rad);
	sin_value = sin(coordinate.rad);

	delta_y = (count[0] + count[2] - befCount[0] - befCount[2]) / 2.0;
	delta_x = count[1] - befCount[1];

    coordinate.x += convertCountToDistance(delta_x) * cos_value - convertCountToDistance(delta_y) * sin_value;
    coordinate.y += convertCountToDistance(delta_y) * cos_value + convertCountToDistance(delta_x) * sin_value;
}


/********************
 * CoordinateMeasurerTriangle
 ********************/

CoordinateMeasurerTriangle::CoordinateMeasurerTriangle(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius) : CoordinateMeasurer(encoderPPR, radiusOfMeasureWheel, attachmentRadius){

}

void CoordinateMeasurerTriangle::offset(CoordinatePoint *pCoordinate){
    coordinate = coordinate + *pCoordinate - offset_coordinate;
	offset_coordinate = *pCoordinate;
}

void CoordinateMeasurerTriangle::calcRad(){
	coordinate.rad += (count[0] + count[1] + count[2] - count[0] - count[1] - count[2]) * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (parameter.attachmentRadius * parameter.encoderCPR * 3.0);
}

void CoordinateMeasurerTriangle::calcPoint(){
	float sin_value;
	float cos_value;
	float delta_y , delta_x;

	cos_value = cos(coordinate.rad);
	sin_value = sin(coordinate.rad);

	delta_y = (count[2] - befCount[2] - (count[1] - befCount[1])) * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (sqrt(3.0) * parameter.encoderCPR);
	delta_x = (count[1] + befCount[1] + count[2] - befCount[2] - 2 * (count[0] - befCount[0])) * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (3.0 * parameter.encoderCPR);

    coordinate.x += convertCountToDistance(delta_x) * cos_value - convertCountToDistance(delta_y) * sin_value;
    coordinate.y += convertCountToDistance(delta_y) * cos_value + convertCountToDistance(delta_x) * sin_value;
}
