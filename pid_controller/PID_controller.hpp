#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include <stdint.h>
#include <cmath>

namespace aca {

/**
 * PIDのパラメータを保持する構造体
 */
struct PID_Element{
    float proportional;
    float integral;
    float differential;
};

/**
 * 安定条件を表す構造体
 */
struct StableConditions{
	/**
	 * 許容誤差
	 * @details 大きくし過ぎると応答性が悪くなるので、小さい値から調整していくことを推奨する
	 */
	float allowable_error;

	/**
	 * 安定時間 [ms]
	 * @details この時間分、許容誤差内に収まっていたら、安定したみなす
	 * @details 初期値(0)の場合は判定しない(常にfalse)
	 */
	uint16_t stable_time;
};

class PID_controller
{
private:
	//! PIDの各パラメータ
	PID_Element pid_parameter;

	//! 制御周波数 [Hz]
	float frequency;

	//! PIDの各生値（パラメータをかける前）
	PID_Element operation;

	//! 操作量
	float operation_value;

	//! 前回の操作量
	float last_operation_value = 0;

	//! 前回の差
	float last_difference = 0;

	//! 安定条件
	StableConditions stable_conditions;

	//! 安定時間をカウントするカウンタ変数 [ms]
	uint16_t stable_time_counter;

	//! 安定しているかどうかを表わす変数
	bool is_stable = false;

public:

	/**
	 * コンストラクタ
	 * @param pid_parameter PIDの各パラメータ
	 * @param frequency 制御周波数
	 * @param stable_conditions 操作量を0にする安定条件
	 */
	PID_controller(const PID_Element &pid_parameter, const float frequency, const StableConditions &stable_conditions);

	/**
	 * コンストラクタ
	 * @param pid_parameter PIDの各パラメータ
	 * @param frequency 制御周波数
	 */
	PID_controller(const PID_Element &pid_parameter, const float frequency);

	/**
	 * コンストラクタ
	 * @param pid_parameter PIDの各パラメータ
	 */
	PID_controller(const PID_Element &pid_parameter);

	/**
	 * コンストラクタ
	 * @param frequency 制御周波数
	 */
	PID_controller(const float frequency);

	/**
	 * 初期化関数
	 * @param pid_parameter PIDの各パラメータ
	 * @param frequency 制御周波数
	 */
	void init(const PID_Element &pid_parameter, const float frequency);

	/**
	 * 初期化関数
	 * @param pid_parameter PIDの各パラメータ
	 */
	void init(const PID_Element &pid_parameter);

	/**
	 * 初期化関数
	 * @param frequency 制御周波数
	 */
	void init(const float frequency);

	/**
	 * 安定条件を設定する関数
	 * @param stable_conditions 安定条件を表す構造体変数
	 */
	void set_stable_conditions(const StableConditions &stable_conditions);

	/**
	 * 操作量を更新する関数
	 * @param difference 偏差(誤差値)
	 */
	void update_operation(const float difference);

	/**
	 * 積分成分を0にリセットする関数
	 */
	void reset_integral();

	/**
	 * 操作量を取得する関数
	 * @details 位置型PID（普通のPID）で使用する
	 * @return 操作量
	 */
	float get_operation();

	/**
	 * 操作量の変化を取得する関数
	 * @details 速度型PIDで使用する
	 * @return 操作量
	 */
	float get_operation_difference();

	/**
	 * 現在安定かどうかを取得する関数
	 * @return 安定判定
	 */
	bool get_is_stable();
};

} // namespace aca

#endif //PID_CONTROLLER_HPP
