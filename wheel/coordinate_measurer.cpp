#include "coordinate_measurer.hpp"
#include <cmath>

namespace aca{

CoordinateMeasurer::CoordinateMeasurer(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius){
	parameter.encoderCPR = encoderPPR * 4;
	parameter.radiusOfMeasureWheel = radiusOfMeasureWheel;
	parameter.attachmentRadius = attachmentRadius;
}

void CoordinateMeasurer::setData(const std::array<int32_t,3> &EncoderCount){
	befCount = count;
	count = EncoderCount;
	for(uint8_t i; i<3; i++){
		prev_distance[i] = distance[i];
		distance[i] = 2.0 * M_PI * parameter.radiusOfMeasureWheel * (float)EncoderCount[i] / (float)parameter.encoderCPR;
	}
}

const Coordinate<float> &CoordinateMeasurer::get_coordinate(){
	return coordinate;
}

void CoordinateMeasurer::update(){
	calcRad();
	calcPoint();
}

void CoordinateMeasurer::overwriteCoord(Coordinate<float> coordinate){
    this->coordinate = coordinate;
}

float CoordinateMeasurer::convertCountToDistance(float deltaCount){
	return deltaCount * parameter.radiusOfMeasureWheel * M_PI * 2.0 / (float)parameter.encoderCPR;
}

/*****************
 * CoordinateMeasurerLine
 ******************/

CoordinateMeasurerLine::CoordinateMeasurerLine(
	uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius
):
	CoordinateMeasurer(encoderPPR, radiusOfMeasureWheel, attachmentRadius)
{
}

void CoordinateMeasurerLine::calcRad(){
    if(count[0] - count[2])	{
        coordinate.angle = offset_coordinate.angle;
    } else {
//        coordinate.angle = (count[0] - count[2]) * M_PI * parameter.attachmentRadius / (parameter.encoderCPR * parameter.attachmentRadius) + offset_coordinate.angle;
        coordinate.angle = (distance[0] - distance[2]) / (2.0*parameter.attachmentRadius);
    }
}

void CoordinateMeasurerLine::calcPoint(){
	float cos_value = std::cos(coordinate.angle);
	float sin_value = std::sin(coordinate.angle);

	float delta_y = (count[0] + count[2] - befCount[0] - befCount[2]) / 2.0;
	float delta_x = count[1] - befCount[1];

    coordinate.x += convertCountToDistance(delta_x) * cos_value - convertCountToDistance(delta_y) * sin_value;
    coordinate.y += convertCountToDistance(delta_y) * cos_value + convertCountToDistance(delta_x) * sin_value;
}


/********************
 * CoordinateMeasurerTriangle
 ********************/

CoordinateMeasurerTriangle::CoordinateMeasurerTriangle(
	uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius
):
	CoordinateMeasurer(encoderPPR, radiusOfMeasureWheel, attachmentRadius)
{
}

void CoordinateMeasurerTriangle::calcRad(){
//	coordinate.angle += (count[0] + count[1] + count[2] - count[0] - count[1] - count[2]) * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (parameter.attachmentRadius * parameter.encoderCPR * 3.0);
	coordinate.angle = ( distance[0] + distance[1] + distance[2] ) / ( 3 * parameter.attachmentRadius );
}

void CoordinateMeasurerTriangle::calcPoint(){
	float sin_value = std::sin(coordinate.angle);
	float cos_value = std::cos(coordinate.angle);

	float delta_y = (count[2] - befCount[2] - (count[1] - befCount[1])) * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (sqrt(3.0) * parameter.encoderCPR);
	float delta_x = (count[1] + befCount[1] + count[2] - befCount[2] - 2 * (count[0] - befCount[0])) * parameter.radiusOfMeasureWheel *M_PI * 2.0 / (3.0 * parameter.encoderCPR);

    coordinate.x += convertCountToDistance(delta_x) * cos_value - convertCountToDistance(delta_y) * sin_value;
    coordinate.y += convertCountToDistance(delta_y) * cos_value + convertCountToDistance(delta_x) * sin_value;
}

}; // namespace aca
