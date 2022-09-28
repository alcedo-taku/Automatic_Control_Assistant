#ifndef COORDINATE_MEASURER_HPP_
#define COORDINATE_MEASURER_HPP_

#include <cstdint>
#include <array>
#include <cmath>
#include "coordinate.hpp"

namespace aca{


/**
 * @struct RobotParameter
 * @brief ロボットのパラメータを入れる構造体
 */
template <std::size_t  NUMBER_OF_ENCODER>
struct RobotParameter {
	std::array<uint16_t,NUMBER_OF_ENCODER> encoder_CPR; // encoder count per revolution
	std::array<uint16_t,NUMBER_OF_ENCODER> radius_of_measure_wheel;
	std::array<uint16_t,NUMBER_OF_ENCODER> radius_of_attachment;
	std::array<float,NUMBER_OF_ENCODER> encoder_attachment_angle_TCP; //encoder tea ceremony procedures
	std::array<float,NUMBER_OF_ENCODER> encoder_attachment_angle_true;
};



/**
 * @class CoordinateMeasurer
 * @brief 自己位置推定用のクラス
 * @details 基底クラス
 */

template <std::size_t  NUMBER_OF_ENCODER>
class CoordinateMeasurer{
public:
	/**
	 * @brief コンストラクタ
	 * @param encoder_PPR エンコーダの pulse per revolution
	 * @param radius_of_measure_Wheel　計測輪の半径
	 * @param radius_of_attachment 計測輪の取付半径
	 * @param encoder_attachment_angle_TCP 各計測輪自身の建前の角度
	 * @param encoder_attachment_angle_true 各計測輪自身の実際の角度
	 */
	CoordinateMeasurer(std::array<uint16_t,NUMBER_OF_ENCODER> encoder_PPR, std::array<uint16_t,NUMBER_OF_ENCODER> radius_of_measure_Wheel, std::array<uint16_t,NUMBER_OF_ENCODER> radius_of_attachment, std::array<float,NUMBER_OF_ENCODER> encoder_attachment_angle_TCP, std::array<float, NUMBER_OF_ENCODER> encoder_attachment_angle_true) {
		parameter.encoder_CPR = encoder_PPR * 4;
		parameter.radius_of_measure_wheel = radius_of_measure_Wheel;
		parameter.radius_of_attachment = radius_of_attachment;
		parameter.encoder_attachment_angle_TCP= encoder_attachment_angle_TCP;
		parameter.encoder_attachment_angle_true = encoder_attachment_angle_true;
	}
	CoordinateMeasurer(uint16_t encoder_PPR, uint16_t radius_of_measure_Wheel, uint16_t radius_of_attachment, std::array<float, NUMBER_OF_ENCODER> encoder_attachment_angle){
		for(int i=0;i<4;i++){
			parameter.encoder_CPR[i] = encoder_PPR * 4;
			parameter.radius_of_measure_wheel[i] = radius_of_measure_Wheel;
			parameter.radius_of_attachment[i] = radius_of_attachment;
		}
		parameter.encoder_attachment_angle_true = encoder_attachment_angle;
	}

	/**
	 * @brief 座標を更新する関数
	 * @details 内部で、calcAngle,convert_to_robot,convert_to_field を実行している
	 * @param encoder_count そのときの各エンコーダのカウントを格納した配列
	 */
	void update(const std::array<int32_t,NUMBER_OF_ENCODER> &encoder_count){
		std::array<float,NUMBER_OF_ENCODER> distance;
		for(uint8_t i = 0; i < NUMBER_OF_ENCODER; i++){
			distance[i] = 2.0 * M_PI * parameter.radius_of_measure_wheel[i] * (float)encoder_count[i] / (float)parameter.encoder_CPR[i];
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
	const Coordinate<float> &get_coordinate(){
		return coordinate;
	}

	/**
	 * @brief 座標を上書きする関数
	 * @param coordinate 上書きしたい座標を格納した構造体
	 */
	void overwrite_coordinate(Coordinate<float> coordinate){
		offset_angle = this->coordinate.angle - coordinate.angle;
	    this->coordinate = coordinate;
	}

private:
	virtual float calc_angle(std::array<float,NUMBER_OF_ENCODER> distance) = 0;
	virtual Coordinate<float> convert_to_robot(std::array<float,NUMBER_OF_ENCODER> distance) = 0;

	/**
	 * @brief ロボット座標の微小移動距離を フィールド座標に変換する
	 * @details ロボット座標の微小移動距離 → フィールド座標の微小移動距離 → フィールド座標
	 * @param micro_distance ロボット座標の微小移動距離
	 * @return フィールド座標
	 */
	Coordinate<float> convert_to_field(Coordinate<float> micro_distance){
		Coordinate<float> micro_field_distance;
		float cos_value = std::cos(coordinate.angle);
		float sin_value = std::sin(coordinate.angle);
		micro_field_distance.x = micro_distance.x * cos_value - micro_distance.y * sin_value;
		micro_field_distance.y = micro_distance.x * sin_value + micro_distance.y * cos_value;
		return micro_field_distance;
	}

protected:
	Coordinate<float> coordinate; 					//!< フィールド座標(field_coordinate)
	float offset_angle;								//!< 座標を上書きされたときの角度のオフセット量
	RobotParameter<NUMBER_OF_ENCODER> parameter;	//!< ロボットのパラメータを格納する構造体のインスタンス
};



/**
 * @class CoordinateMeasurerLine
 * @brief H字型配置計測輪のため、CoordinateMeasurer を継承したライブラリ
 */
template <std::size_t  NUMBER_OF_ENCODER>
class CoordinateMeasurerLine : public CoordinateMeasurer<NUMBER_OF_ENCODER>{
public:
	/**
	 * @brief コンストラクタ
	 * @param encoder_PPR エンコーダの pulse per revolution
	 * @param radius_of_measure_Wheel　計測輪の半径
	 * @param radius_of_attachment 計測輪の取付半径
	 * @param encoder_attachment_angle_TCP 各計測輪自身の建前の角度
	 * @param encoder_attachment_angle_true 各計測輪自身の実際の角度
	 */
	CoordinateMeasurerLine(
		uint16_t encoder_PPR, uint16_t radius_of_measure_Wheel, uint16_t radius_of_attachment, std::array<float,NUMBER_OF_ENCODER> encoder_attachment_angle_true
	):
		CoordinateMeasurer<NUMBER_OF_ENCODER>(encoder_PPR, radius_of_measure_Wheel, radius_of_attachment, encoder_attachment_angle_true)
	{
	}

private:
	/**
	 * @brief 角度を計算する関数
	 * @param distance
	 * @return ロボットの回転した角度
	 */
	float calc_angle(std::array<float,NUMBER_OF_ENCODER> distance) override {
		return ( ( distance[0]*std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[0]*M_PI/180) ) - ( distance[2]*std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[2]*M_PI/180) ) ) / (2.0*CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.radius_of_attachment[0]);
	}

	/**
	 * @brief 各計測輪の進んだ距離を ロボット座標の微小移動距離に変換する
	 * @details 各計測輪の進んだ距離 → 各計測輪の微小進んだ距離 → ロボット座標の微小移動距離
	 * @param distance 各計測輪の進んだ距離
	 * @return ロボット座標の微小移動距離
	 */
	Coordinate<float> convert_to_robot(std::array<float,NUMBER_OF_ENCODER> distance) override {
		Coordinate<float> micro_robot_distance;
		static std::array<float,NUMBER_OF_ENCODER> prev_distance = distance;
		micro_robot_distance.x = (distance[1]-prev_distance[1])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[1]*M_PI/180) + ( (distance[0]-prev_distance[0])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[0]*M_PI/180) + (distance[2]-prev_distance[2])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[2]*M_PI/180) ) / 2.0;
		micro_robot_distance.y = (distance[1]-prev_distance[1])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[1]*M_PI/180) + ( (distance[0]-prev_distance[0])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[0]*M_PI/180) + (distance[2]-prev_distance[2])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[2]*M_PI/180) ) / 2.0;;
		prev_distance = distance;
		return micro_robot_distance;
	}

};



/**
 * @class CoordinateMeasurerTriangle
 * @brief 三角形配置計測輪のため、CoordinateMeasurer を継承したライブラリ
 */
template <std::size_t  NUMBER_OF_ENCODER>
class CoordinateMeasurerTriangle : public CoordinateMeasurer<NUMBER_OF_ENCODER>{
public:
	/**
	 * @brief コンストラクタ
	 * @param encoder_PPR エンコーダの pulse per revolution
	 * @param radius_of_measure_Wheel　計測輪の半径
	 * @param radius_of_attachment 計測輪の取付半径
	 * @param encoder_attachment_angle_TCP 各計測輪自身の建前の角度
	 * @param encoder_attachment_angle_true 各計測輪自身の実際の角度
	 */
	CoordinateMeasurerTriangle(
		uint16_t encoder_PPR, uint16_t radius_of_measure_Wheel, uint16_t radius_of_attachment, std::array<float,NUMBER_OF_ENCODER> encoder_attachment_angle_true
	):
		CoordinateMeasurer<NUMBER_OF_ENCODER>(encoder_PPR, radius_of_measure_Wheel, radius_of_attachment, encoder_attachment_angle_true)
	{
	}

private:
	/**
	 * @brief 角度を計算する関数
	 * @param distance
	 * @return　ロボットの回転した角度
	 */
	float calc_angle(std::array<float,NUMBER_OF_ENCODER> distance) override {
		return ( ( ( distance[0]*std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[0]*M_PI/180) ) / std::sin(180*M_PI/180) ) +  ( ( distance[1]*std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[1]*M_PI/180) ) / std::sin(300*M_PI/180) ) +  ( ( distance[2]*std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[2]*M_PI/180) ) / std::sin(60*M_PI/180) ) ) / (3.0 * CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.radius_of_attachment[0]);
	}

	/**
	 * @brief 各計測輪の進んだ距離を ロボット座標の微小移動距離に変換する
	 * @details 各計測輪の進んだ距離 → 各計測輪の微小進んだ距離 → ロボット座標の微小移動距離
	 * @param distance 各計測輪の進んだ距離
	 * @return ロボット座標の微小移動距離
	 */
	Coordinate<float> convert_to_robot(std::array<float,NUMBER_OF_ENCODER> distance) override {
		Coordinate<float> micro_robot_distance;
		static std::array<float,NUMBER_OF_ENCODER> prev_distance = distance;
		micro_robot_distance.x = ( (distance[0]-prev_distance[0])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[0]*M_PI/180) + (distance[1]-prev_distance[1])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[1]*M_PI/180) + (distance[2]-prev_distance[2])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[2]*M_PI/180) ) / 3.0;
		micro_robot_distance.y = ( (distance[0]-prev_distance[0])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[0]*M_PI/180)) + ( (distance[1]-prev_distance[1])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[1]*M_PI/180) + (distance[2]-prev_distance[2])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[2]*M_PI/180) ) / 2.0;
		prev_distance = distance;
		return micro_robot_distance;
	}

};



/**
 * @class CoordinateMeasurerSquare
 * @brief 四角形配置計測輪のため、CoordinateMeasurer を継承したライブラリ
 */
template <std::size_t NUMBER_OF_ENCODER>
class CoordinateMeasurerSquare : public CoordinateMeasurer<NUMBER_OF_ENCODER>{
public:
	/**
	 * @brief コンストラクタ
	 * @param encoder_PPR エンコーダの pulse per revolution
	 * @param radius_of_measure_Wheel　計測輪の半径
	 * @param radius_of_attachment 計測輪の取付半径
	 * @param encoder_attachment_angle_TCP 各計測輪自身の建前の角度
	 * @param encoder_attachment_angle_true 各計測輪自身の実際の角度
	 */
	CoordinateMeasurerSquare(
		uint16_t encoder_PPR, uint16_t radius_of_measure_wheel, uint16_t radius_of_attachment, std::array<float,NUMBER_OF_ENCODER> encoder_attachment_angle_true
	):
		CoordinateMeasurer<NUMBER_OF_ENCODER>(encoder_PPR, radius_of_measure_wheel, radius_of_attachment ,encoder_attachment_angle_true)
	{
	}

private:
	/**
	 * @brief 角度を計算する関数
	 * @param distance
	 * @return　ロボットの回転した角度
	 */
	float calc_angle(std::array<float,NUMBER_OF_ENCODER> distance) override {
		return (-distance[0]*std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[0]*M_PI/180) - distance[1]*std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[1]*M_PI/180)
			  + distance[2]*std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[2]*M_PI/180) + distance[3]*std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[3]*M_PI/180))/(4.0*CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.radius_of_attachment[0]);
	}

	/**
	 * @brief 各計測輪の進んだ距離を ロボット座標の微小移動距離に変換する
	 * @details 各計測輪の進んだ距離 → 各計測輪の微小進んだ距離 → ロボット座標の微小移動距離
	 * @param distance 各計測輪の進んだ距離
	 * @return ロボット座標の微小移動距離
	 */
	Coordinate<float> convert_to_robot(std::array<float,NUMBER_OF_ENCODER> distance) override {
		Coordinate<float> micro_robot_distance;
		static std::array<float,NUMBER_OF_ENCODER> prev_distance = distance;
		micro_robot_distance.x = ( (distance[0]-prev_distance[0])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[0]*M_PI/180) + (distance[2]-prev_distance[2])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[2]*M_PI/180) )/2.0
							   + ( (distance[1]-prev_distance[1])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[1]*M_PI/180) + (distance[3]-prev_distance[3])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[3]*M_PI/180) )/2.0;
		micro_robot_distance.y = ( (distance[1]-prev_distance[1])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[1]*M_PI/180) + (distance[3]-prev_distance[3])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[3]*M_PI/180) )/2.0
							   + ( (distance[0]-prev_distance[0])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[0]*M_PI/180) + (distance[2]-prev_distance[2])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[2]*M_PI/180) )/2.0;
		prev_distance = distance;
		return micro_robot_distance;
	}

};



/**
 * @class CoordinateMeasurerFreedom
 * @brief 自由配置計測輪のため、CoordinateMeasurer を継承したライブラリ
 */
template <std::size_t NUMBER_OF_ENCODER>
class CoordinateMeasurerFreedom : public CoordinateMeasurer<NUMBER_OF_ENCODER>{
public:
	/**
	 * @brief コンストラクタ
	 * @param encoder_PPR エンコーダの pulse per revolution
	 * @param radius_of_measure_Wheel　計測輪の半径
	 * @param radius_of_attachment 計測輪の取付半径
	 * @param encoder_attachment_angle_TCP 各計測輪自身の建前の角度
	 * @param encoder_attachment_angle_true 各計測輪自身の実際の角度
	 */
	CoordinateMeasurerFreedom(
			 std::array<uint16_t,NUMBER_OF_ENCODER> encoder_PPR,  std::array<uint16_t,NUMBER_OF_ENCODER> radius_of_measure_wheel,  std::array<uint16_t,NUMBER_OF_ENCODER> radius_of_attachment, std::array<float,NUMBER_OF_ENCODER> encoder_attachment_angle_TCP, std::array<float,NUMBER_OF_ENCODER> encoder_attachment_angle_true
	):
		CoordinateMeasurer<NUMBER_OF_ENCODER>(encoder_PPR, radius_of_measure_wheel, radius_of_attachment , encoder_attachment_angle_TCP, encoder_attachment_angle_true)
	{
	}

private:
	/**
	 * @brief 角度を計算する関数
	 * @param distance
	 * @return　ロボットの回転した角度
	 */
	float calc_angle(std::array<float,NUMBER_OF_ENCODER> distance) override {
		float calc_angle = 0;
		for(int i = 0; i < (int)NUMBER_OF_ENCODER; i++){
			calc_angle += ( ( distance[i]*std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[i]*M_PI/180) ) / std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_TCP[i]*M_PI/180) )/(NUMBER_OF_ENCODER*CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.radius_of_attachment[i]);
		}
		return calc_angle;
	}

	/**
	 * @brief 各計測輪の進んだ距離を ロボット座標の微小移動距離に変換する
	 * @details 各計測輪がx軸またはy軸に直角と定義されている個数　→ 各計測輪の微小進んだ距離 →　各計測輪の進んだ距離 → ロボット座標の微小移動距離
	 * @param distance 各計測輪の進んだ距離
	 * @return ロボット座標の微小移動距離
	 */
	Coordinate<float> convert_to_robot(std::array<float,NUMBER_OF_ENCODER> distance) override {
		Coordinate<float> micro_robot_distance;
		static std::array<float,NUMBER_OF_ENCODER> prev_distance = distance;
		uint8_t xs_count = 0;
		uint8_t ys_count = 0;
		float micro_robot_distance_xm = 0;
		float micro_robot_distance_ym = 0;
		float micro_robot_distance_xs = 0;
		float micro_robot_distance_ys = 0;
		for(int i = 0; i < (int)NUMBER_OF_ENCODER; i++){
			if(std::abs(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_TCP[i]) == 90 || std::abs(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_TCP[i]) == 270){
				xs_count++;
			}
			if(std::abs(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_TCP[i]) == 360 || std::abs(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_TCP[i]) == 180){
				ys_count++;
			}
		}
		for(int i = 0; i < (int)NUMBER_OF_ENCODER; i++){
			if(std::abs(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_TCP[i]) == 90 || std::abs(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_TCP[i]) == 270){
				micro_robot_distance_xs += (distance[i]-prev_distance[i])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[i]*M_PI/180) / xs_count;
			}else{
				micro_robot_distance_xm += (distance[i]-prev_distance[i])/std::cos(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[i]*M_PI/180) / (NUMBER_OF_ENCODER - xs_count);
			}
			if(std::abs(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_TCP[i]) == 360 || std::abs(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_TCP[i]) == 180){
				micro_robot_distance_ys += (distance[i]-prev_distance[i])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[i]*M_PI/180) / ys_count;
			}else{
				micro_robot_distance_ym += (distance[i]-prev_distance[i])/std::sin(CoordinateMeasurer<NUMBER_OF_ENCODER>::parameter.encoder_attachment_angle_true[i]*M_PI/180) / (NUMBER_OF_ENCODER - ys_count);
			}
		}

		micro_robot_distance.x = micro_robot_distance_xm + micro_robot_distance_xs;
		micro_robot_distance.y = micro_robot_distance_ym + micro_robot_distance_ys;
		prev_distance = distance;
		return micro_robot_distance;
	}

};



}; // namespace aca

#endif // COORDINATE_MEASURER_HPP_
