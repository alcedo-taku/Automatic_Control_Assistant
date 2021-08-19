# PID_Controller

## 目次

- [PID_Controller](#pid_controller)  
  - [目次](#目次)  
- [PID_Controller](#pid_controller-1)  
  - [コンストラクタ](#コンストラクタ)  
    - [PID_controller::PID_controller(const PID_Element &, const float)](#pid_controllerpid_controllerconst-pid_element--const-float)  
    - [PID_controller::PID_controller(float, float, float, const float)](#pid_controllerpid_controllerfloat-float-float-const-float)  
  - [関数](#関数)  
    - [void PID_controller::updateOperation(float difference)](#void-pid_controllerupdateoperationfloat-difference)  
    - [PID_controller::resetIntegral()](#pid_controllerresetintegral)  
    - [PID_controller::getOperation()](#pid_controllergetoperation)  
- [PID_controller_velocity](#pid_controller_velocity)  
  - [コンストラクタ](#コンストラクタ-1)  
    - [PID_controller_velocity::PID_controller_velocity(const PID_Element &,const float)](#pid_controller_velocitypid_controller_velocityconst-pid_element-const-float)  
    - [PID_controller_velocity::PID_controller_velocity(float ,float ,float ,const float)](#pid_controller_velocitypid_controller_velocityfloat-float-float-const-float)  
  - [関数](#関数-1)  
    - [PID_controller_velocity::updateOperation(float)](#pid_controller_velocityupdateoperationfloat)  
    - [PID_controller_velocity::getOperation()](#pid_controller_velocitygetoperation)  
    - [PID_controller_velocity::resetOperation()](#pid_controller_velocityresetoperation)  


# PID_Controller

通常のPID(位置型PID)を簡単に実装できるライブラリ

## コンストラクタ

##### PID_controller::PID_controller(const PID_Element &, const float)
> ```c++
> PID_controller(
>   const PID_Element &pid_parameter, // PIDのパラメータを保持する構造体
>   const float frequency //制御周波数
> )
> ```
> 上記の値を設定します。
> ```c++
> // 例
> PID_Element pid_parameter = {10, 0.4, 0.02};
> PID_controller pid_controller(pid_parameter,1);
> ```

##### PID_controller::PID_controller(float, float, float, const float)
> ```c++
> PID_controller(
>   float proportional, // 比例ゲイン
>   float integral, // 積分ゲイン
>   float differential, // 微分ゲイン
>   const float frequency // 制御周波数
> )
> ```
> 各ゲインの値と制御周波数を設定します。
> ```c++
> // 例
> PID_controller pid_controller(10, 0.4, 0.02, 1);
> ```

## 関数

##### PID_controller::updateOperation(float difference)
> ```c++
> void updateOperation(
>   float difference
> )
> ```
> 誤差値を設定し、内部で出力値を更新します。
> ```c++
> // 例
> pid_controller.updateOperation(target_position - current_position);
> ```

##### PID_controller::resetIntegral()
> ```c++
> void resetIntegral()
> ```
> 積分成分を0にします。
> ```c++
> // 例
> pid_controller.resetIntegral()
> ```

##### PID_controller::getOperation()
> ```c++
> float getOperation()
> ```
> 出力値を返します。
> ```c++
> // 例
> velocity_x = pid_controller.getOperation();
> ```


# PID_controller_velocity

速度型PIDを簡単に実装できるライブラリ

## コンストラクタ

##### PID_controller_velocity::PID_controller_velocity(const PID_Element &,const float)
> ```c++
> PID_controller_velocity(
>   const PID_Element &pid_parameter, // PIDのパラメータを保持する構造体
>   const float frequency //制御周波数
> )
> ```
> 上記の値を設定します。
> ```c++
> // 例
> PID_Element pid_parameter = {10, 0.4, 0.02};
> PID_controller pid_controller(pid_parameter,1);
> ```

##### PID_controller_velocity::PID_controller_velocity(float ,float ,float ,const float)
> ```c++
> PID_controller_velocity(
>   float proportional, // 比例ゲイン
>   float integral, // 積分ゲイン
>   float differential, // 微分ゲイン
>   const float frequency // 制御周波数
> )
> ```
> 各ゲインの値と制御周波数を設定します。
> ```c++
> // 例
> PID_controller pid_controller(10, 0.4, 0.02, 1);
> ```

## 関数

##### PID_controller_velocity::updateOperation(float)
> ```c++
> void updateOperation(
>   float difference
> )
> ```
> 誤差値を設定し、内部で出力値の更新します。
> ```c++
> // 例
> pid_controller_velocity.updateOperation(target_position - current_position);
> ```

##### PID_controller_velocity::getOperation()
> ```c++
> float getOperation()
> ```
> 出力値を返します。
> ```c++
> // 例
> velocity_x = pid_controller_velocity.getOperation();
> ```

###### PID_controller_velocity::resetOperation()
> ```c++
> void resetOperation()
> ```
> 出力値を0にします。
> ```c++
> // 例
> pid_controller_velocity.resetOperation();
> ```
