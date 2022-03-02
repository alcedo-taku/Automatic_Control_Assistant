#ifndef COORDINATE_MEASURER_HPP_
#define COORDINATE_MEASURER_HPP_

#include <cstdint>
#include <array>
#include "coordinate.hpp"

namespace aca{

/**
 * @struct RobotParameter
 * @brief ロボットのパラメータを入れる構造体
 */
struct RobotParameter {
	uint16_t encoderCPR; // encoder count per revolution
	uint16_t radiusOfMeasureWheel;
	uint16_t attachmentRadius;
};

/**
 * @class CoordinateMeasurer
 * @brief 自己位置推定用のクラス
 * @details 基底クラス
 */
class CoordinateMeasurer{
public:
	CoordinateMeasurer(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
	void update(const std::array<int32_t,3> &EncoderCount);
	const Coordinate<float> &get_coordinate();
	void overwriteCoordinate(Coordinate<float> coordinate);
private:
	virtual float calcAngle(std::array<float,3> distance) = 0;
	virtual Coordinate<float> convert_to_robot(std::array<float,3> distance) = 0;
	Coordinate<float> convert_to_field(Coordinate<float> micro_distance);
protected:
	Coordinate<float> coordinate; 	//!< フィールド座標(field_coordinate)
	float offset_angle;				//!< 座標を上書きされたときの角度のオフセット量
	RobotParameter parameter;		//!< ロボットのパラメータを格納する構造体のインスタンス
};



/**
 * @class CoordinateMeasurerLine
 * @brief H字型配置計測輪のため、CoordinateMeasurer を継承したライブラリ
 */
class CoordinateMeasurerLine : public CoordinateMeasurer{
public:
	CoordinateMeasurerLine(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
private:
	float calcAngle(std::array<float,3> distance) override;
	Coordinate<float> convert_to_robot(std::array<float,3> distance) override;
};



/**
 * @class CoordinateMeasurerTriangle
 * @brief 三角形配置計測輪のため、CoordinateMeasurer を継承したライブラリ
 */
class CoordinateMeasurerTriangle : public CoordinateMeasurer{
public:
	CoordinateMeasurerTriangle(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
private:
	float calcAngle(std::array<float,3> distance) override;
	Coordinate<float> convert_to_robot(std::array<float,3> distance) override;
};

}; // namespace aca

#endif // COORDINATE_MEASURER_HPP_
