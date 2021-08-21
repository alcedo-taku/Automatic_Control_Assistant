# Omniwheelcontroller

オムニホイール駆動のための、x,y,回転方向の速度を各ホイールの速度に変換するためのライブラリ

## 目次
- [PID_Controller](#pid_controller-1)  
  - [コンストラクタ](#コンストラクタ)  
    - [PID_controller::PID_controller(const PID_Element &, const float)](#pid_controllerpid_controllerconst-pid_element--const-float)  
    - [PID_controller::PID_controller(float, float, float, const float)](#pid_controllerpid_controllerfloat-float-float-const-float)  
  - [関数](#関数)  
    - [void PID_controller::updateOperation(float difference)](#void-pid_controllerupdateoperationfloat-difference)  
    - [PID_controller::resetIntegral()](#pid_controllerresetintegral)  
    - [PID_controller::getOperation()](#pid_controllergetoperation)  


## コンストラクタ

##### OmniWheelController::OmniWheelController(float)
> ```c++
> OmniWheelController(
>   float robot_radius // ロボット半径
> ) 
> ```
> 上記の値を設定します。
> ```c++
> // 例
> OmniWheelController omniWheelController(robot_radius);
> ```

## 関数

##### OmniWheelController::setField(float ,float , float)
> ```c++
> void setField(
>   float field_velosity_x, // フィールド座標x方向の速度
>   float field_velosity_y, // フィールド座標y方向の速度
>   float rad // 現在のロボットの角度
> )
> ```
> フィールド座標速度と現在のロボットの角度を入れ、ロボット座標速度を計算します。
> ```c++
> // 例
> omniWheelController.setField(field_velosity_x, field_velosity_y, rad));
> ```

##### OmniWheelController::setRobot(float)
> ```c++
> void setRobot(
>   float angle_velocity
> )
> ```
> ロボットの自転速度を入れ、各ホイールの速度を計算します。
> ```c++
> // 例
> omniWheelController.setRobot(angle_velocity)
> ```

##### OmniWheelController::setVelocity(float, float, float, float)
> ```c++
> void setVelocity(
>   float field_velocity_x,
>   float field_velocity_y,
>   float angle_velocity,
>   float rad
> )
> ```
> 上記の値を入れ、内部で setField と setRobot を実行します。
> ```c++
> // 例
> omniWheelController.setVelocity(field_velocity_x, field_velocity_y, angle_velocity, rad);
> ```

##### OmniWheelController::getOmni()
> ```c++
> std::array<int16_t, 4> getOmni()
> ```
> 各ホイールの速度を保持したarray配列を返します。
> ```c++
> // 例
> omniWheelController.getOmni();
> ```