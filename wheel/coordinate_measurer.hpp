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
	/**
	 * @brief コンストラクタ
	 * @param encoderPPR エンコーダの pulse per revolution
	 * @param radiusOfMeasureWheel　計測輪の半径
	 * @param attachmentRadius 計測輪の取付半径
	 */
	CoordinateMeasurer(uint16_t encoderPPR, uint16_t radiusOfMeasureWheel, uint16_t attachmentRadius);

	/**
	 * @brief 座標を更新する関数
	 * @details 内部で、calcAngle,convert_to_robot,convert_to_field を実行している
	 * @param EncoderCount そのときの各エンコーダのカウントを格納した配列
	 */
	void update(const std::array<int32_t,3> &EncoderCount);

	/**
	 * @brief 座標を取得する関数
	 * @return 座標を格納した構造体
	 */
	const Coordinate<float> &get_coordinate();

	/**
	 * @brief 座標を上書きする関数
	 * @param coordinate 上書きしたい座標を格納した構造体
	 */
	void overwriteCoordinate(Coordinate<float> coordinate);

private:
	/**
	 * @brief 角度を計算する関数
	 * @param distance
	 * @return
	 */
	virtual float calcAngle(std::array<float,3> distance) = 0;

	/**
	 * @brief 各計測輪の進んだ距離を ロボット座標の微小移動距離に変換する
	 * @details 各計測輪の進んだ距離 → 各計測輪の微小進んだ距離 → ロボット座標の微小移動距離
	 * @param distance 各計測輪の進んだ距離
	 * @return ロボット座標の微小移動距離
	 */
	virtual Coordinate<float> convert_to_robot(std::array<float,3> distance) = 0;

	/**
	 * @brief ロボット座標の微小移動距離を フィールド座標に変換する
	 * @details ロボット座標の微小移動距離 → フィールド座標の微小移動距離 → フィールド座標
	 * @param micro_distance ロボット座標の微小移動距離
	 * @return フィールド座標
	 */
	Coordinate<float> convert_to_field(Coordinate<float> micro_distance);

protected:
	//! フィールド座標
	Coordinate<float> coordinate; // (field_coordinate)

	//! 座標を上書きされたときの角度のオフセット量
	float offset_angle;

	//! ロボットのパラメータを格納する構造体のインスタンス
	RobotParameter parameter;
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
