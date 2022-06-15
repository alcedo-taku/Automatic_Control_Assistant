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
	uint16_t encoder_CPR; // encoder count per revolution
	uint16_t radius_of_measure_wheel;
	uint16_t attachment_radius;
};

/**
 * @class CoordinateMeasurer
 * @brief 自己位置推定用のクラス
 * @details 基底クラス
 */
class CoordinateMeasurer{
public:
	CoordinateMeasurer(uint16_t encoder_PPR, uint16_t radius_of_measure_Wheel, uint16_t attachment_radius);

	void update(const std::array<int32_t,3> &encoder_count);
	void update(const std::array<int32_t,4> &encoder_count);

	const Coordinate<float> &get_coordinate();
	void overwrite_coordinate(Coordinate<float> coordinate);
private:
	virtual float calc_angle(std::array<float,3> distance){return 0;}
	virtual Coordinate<float> convert_to_robot(std::array<float,3> distance){return {0,0,0};}

	virtual float calc_angle(std::array<float,4> distance){return 0;}
	virtual Coordinate<float> convert_to_robot(std::array<float,4> distance){return {0,0,0};}

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
	float calc_angle(std::array<float,3> distance) override;
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
	float calc_angle(std::array<float,3> distance) override;
	Coordinate<float> convert_to_robot(std::array<float,3> distance) override;
};



/**
 * @class CoordinateMeasurerSquare
 * @brief 四角形配置計測輪のため、CoordinateMeasurer を継承したライブラリ
 */
class CoordinateMeasurerSquare : public CoordinateMeasurer{
public:
	CoordinateMeasurerSquare(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);
private:
	float calc_angle(std::array<float,4> distance) override;
	Coordinate<float> convert_to_robot(std::array<float,4> distance) override;
};


}; // namespace aca

#endif // COORDINATE_MEASURER_HPP_
