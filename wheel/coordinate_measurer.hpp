#ifndef COORDINATE_MEASURER_HPP_
#define COORDINATE_MEASURER_HPP_

#include <cstdint>
#include <array>
#include "CoordinatePoint.hpp"

struct RobotParameter {
	uint16_t encoderCPR; // encoder count per revolution
	uint16_t radiusOfMeasureWheel;
	uint16_t attachmentRadius;
};

class CoordinateMeasurer{
public:
	CoordinateMeasurer(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
	void setData(std::array<int32_t,3> *pEncoderCount);
	CoordinatePoint *get_coordinate();
	void update();
	void overwriteCoord(CoordinatePoint coordinate);

private:
	virtual void calcRad() = 0;
	virtual void calcPoint() = 0;

protected:
	float convertCountToDistance(float deltaCount);

	CoordinatePoint coordinate;
    CoordinatePoint offset_coordinate;
	std::array<int32_t,3> count;
	std::array<int32_t,3> befCount;
	std::array<float,3> distance;
	std::array<float,3> prev_distance;
	RobotParameter parameter;
};

class CoordinateMeasurerLine : public CoordinateMeasurer{
public:
	CoordinateMeasurerLine(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
private:
	void calcRad() override;
	void calcPoint() override;
};

class CoordinateMeasurerTriangle : public CoordinateMeasurer{
public:
	CoordinateMeasurerTriangle(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
private:
	void calcRad() override;
	void calcPoint() override;
};

#endif // COORDINATE_MEASURER_HPP_
