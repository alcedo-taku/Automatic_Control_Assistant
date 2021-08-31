# PID_controller_velocity

速度型PIDを簡単に実装できるライブラリ

## 目次

- [PID_controller_velocity](#pid_controller_velocity)
  - [目次](#目次)  
  - [コンストラクタ](#コンストラクタ-1)  
    - [PID_controller_velocity::PID_controller_velocity(const PID_Element &,const float)](#pid_controller_velocitypid_controller_velocityconst-pid_element-const-float)  
    - [PID_controller_velocity::PID_controller_velocity(float ,float ,float ,const float)](#pid_controller_velocitypid_controller_velocityfloat-float-float-const-float)  
  - [関数](#関数-1)  
    - [PID_controller_velocity::updateOperation(float)](#pid_controller_velocityupdateoperationfloat)  
    - [PID_controller_velocity::getOperation()](#pid_controller_velocitygetoperation)  
    - [PID_controller_velocity::resetOperation()](#pid_controller_velocityresetoperation)

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
