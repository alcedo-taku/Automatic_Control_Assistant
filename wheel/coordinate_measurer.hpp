#ifndef COORDINATE_MEASURER_HPP_
#define COORDINATE_MEASURER_HPP_

#include <cstdint>
#include "CoordinatePoint.hpp"

struct EncoderCount {
	int32_t encoder0;
	int32_t encoder1;
	int32_t encoder2;
};

struct RobotParameter {
	uint16_t encoderCPR; // encoder count per revolution
	uint16_t radiusOfMeasureWheel;
	uint16_t attachmentRadius;
};

class CoordinateMeasurer{
public:
	CoordinateMeasurer(uint16_t encoderCPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
	void setData(EncoderCount *pEncoderCount);
	CoordinatePoint *getCoord();
	void update();
	virtual void offset(CoordinatePoint *pCoord) = 0;
	void overwriteCoord(CoordinatePoint coordinate);

private:
	virtual void calcRad() = 0;
	virtual void calcPoint() = 0;

protected:
	float convertCountToDistance(float deltaCount);

	CoordinatePoint coord;
    CoordinatePoint offsetCoord;
	EncoderCount count;
	EncoderCount befCount;
	RobotParameter parameter;
};

class CoordinateMeasurerLine : public CoordinateMeasurer{
public:
	CoordinateMeasurerLine(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
	void offset(CoordinatePoint *pCoord) override;
private:
	void calcRad() override;
	void calcPoint() override;
};

class CoordinateMeasurerTriangle : public CoordinateMeasurer{
public:
	CoordinateMeasurerTriangle(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
	void offset(CoordinatePoint *pCoord) override;
private:
	void calcRad() override;
	void calcPoint() override;
};

#endif // COORDINATE_MEASURER_HPP_
