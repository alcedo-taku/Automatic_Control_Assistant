#include "coordinate_measurer.hpp"
#include <cmath>

namespace aca{

/*
 * CoordinateMeasurer
 */

/**
 * @brief コンストラクタ
 * @param encoder_PPR エンコーダの pulse per revolution
 * @param radius_of_measure_Wheel　計測輪の半径
 * @param attachment_radius 計測輪の取付半径
 */
CoordinateMeasurer::CoordinateMeasurer(uint16_t encoder_PPR, uint16_t radius_of_measure_Wheel, uint16_t attachment_radius){
	parameter.encoder_CPR = encoder_PPR * 4;
	parameter.radius_of_measure_wheel = radius_of_measure_Wheel;
	parameter.attachment_radius = attachment_radius;
}

/**
 * @brief 座標を更新する関数
 * @details 内部で、calcAngle,convert_to_robot,convert_to_field を実行している
 * @param encoder_count そのときの各エンコーダのカウントを格納した配列
 */
void CoordinateMeasurer::update(const std::array<int32_t,3> &encoder_count){
	std::array<float,3> distance;
	for(uint8_t i = 0; i < 3; i++){
		distance[i] = 2.0 * M_PI * parameter.radius_of_measure_wheel * (float)encoder_count[i] / (float)parameter.encoder_CPR;
	}
	coordinate.angle = calc_angle(distance) - offset_angle;
	Coordinate<float> micro_field_distance = convert_to_field( convert_to_robot(distance) );
	static Coordinate<float> prev_micro_field_distance = {0,0,0};
	coordinate.x += (micro_field_distance.x + prev_micro_field_distance.x) / 2.0;
	coordinate.y += (micro_field_distance.y + prev_micro_field_distance.y) / 2.0;
	prev_micro_field_distance = micro_field_distance;
}

/**
 * @brief 座標を取得する関数
 * @return 座標を格納した構造体
 */
const Coordinate<float> &CoordinateMeasurer::get_coordinate(){
	return coordinate;
}

/**
 * @brief 座標を上書きする関数
 * @param coordinate 上書きしたい座標を格納した構造体
 */
void CoordinateMeasurer::overwrite_coordinate(Coordinate<float> coordinate){
	offset_angle = this->coordinate.angle - coordinate.angle;
    this->coordinate = coordinate;
}

/**
 * @brief ロボット座標の微小移動距離を フィールド座標に変換する
 * @details ロボット座標の微小移動距離 → フィールド座標の微小移動距離 → フィールド座標
 * @param micro_distance ロボット座標の微小移動距離
 * @return フィールド座標
 */
Coordinate<float> CoordinateMeasurer::convert_to_field(Coordinate<float> micro_distance){
	Coordinate<float> micro_field_distance;
	float cos_value = std::cos(coordinate.angle);
	float sin_value = std::sin(coordinate.angle);
	micro_field_distance.x = micro_distance.x * cos_value - micro_distance.y * sin_value;
	micro_field_distance.y = micro_distance.x * sin_value + micro_distance.y * cos_value;
	return micro_field_distance;
}


/*
 * CoordinateMeasurerLine
 */

/**
 * @brief コンストラクタ
 * @param encoder_PPR エンコーダの pulse per revolution
 * @param radius_of_measure_Wheel　計測輪の半径
 * @param attachment_radius 計測輪の取付半径
 */
CoordinateMeasurerLine::CoordinateMeasurerLine(
	uint16_t encoder_PPR, uint16_t radius_of_measure_Wheel, uint16_t attachment_radius
):
	CoordinateMeasurer(encoder_PPR, radius_of_measure_Wheel, attachment_radius)
{
}

/**
 * @brief 角度を計算する関数
 * @param distance
 * @return
 */
float CoordinateMeasurerLine::calc_angle(std::array<float,3> distance){
	return (distance[0] - distance[2]) / (2.0*parameter.attachment_radius);
}

/**
 * @brief 各計測輪の進んだ距離を ロボット座標の微小移動距離に変換する
 * @details 各計測輪の進んだ距離 → 各計測輪の微小進んだ距離 → ロボット座標の微小移動距離
 * @param distance 各計測輪の進んだ距離
 * @return ロボット座標の微小移動距離
 */
Coordinate<float> CoordinateMeasurerLine::convert_to_robot(std::array<float,3> distance){
	Coordinate<float> micro_robot_distance;
	static std::array<float,3> prev_distance = distance;
	micro_robot_distance.x = distance[1]-prev_distance[1];
	micro_robot_distance.y = ( (distance[0]-prev_distance[0]) + (distance[2]-prev_distance[2]) ) / 2.0;
	prev_distance = distance;
	return micro_robot_distance;
}


/*
 * CoordinateMeasurerTriangle
 */

/**
 * @brief コンストラクタ
 * @param encoder_PPR エンコーダの pulse per revolution
 * @param radius_of_measure_Wheel　計測輪の半径
 * @param attachment_radius 計測輪の取付半径
 */
CoordinateMeasurerTriangle::CoordinateMeasurerTriangle(
	uint16_t encoder_PPR, uint16_t radius_of_measure_Wheel, uint16_t attachment_radius
):
	CoordinateMeasurer(encoder_PPR, radius_of_measure_Wheel, attachment_radius)
{
}

/**
 * @brief 各計測輪の進んだ距離を ロボット座標の微小移動距離に変換する
 * @details 各計測輪の進んだ距離 → 各計測輪の微小進んだ距離 → ロボット座標の微小移動距離
 * @param distance 各計測輪の進んだ距離
 * @return ロボット座標の微小移動距離
 */
Coordinate<float> CoordinateMeasurerTriangle::convert_to_robot(std::array<float,3> distance){
	Coordinate<float> micro_robot_distance;
	static std::array<float,3> prev_distance = distance;
	micro_robot_distance.x = ( -2*(distance[0]-prev_distance[0]) + (distance[1]-prev_distance[1]) + (distance[2]-prev_distance[2]) ) / 3.0;
	micro_robot_distance.y = ( -(distance[1]-prev_distance[1]) + (distance[2]-prev_distance[2]) ) / std::sqrt(3.0);
	prev_distance = distance;
	return micro_robot_distance;
}

/**
 * @brief 角度を計算する関数
 * @param distance
 * @return
 */
float CoordinateMeasurerTriangle::calc_angle(std::array<float,3> distance){
	return (distance[0] + distance[1] + distance[2]) / (3.0 * parameter.attachment_radius);
}



}; // namespace aca
