# OmniWheelController

オムニホイール駆動のための、x,y,回転方向の速度を各ホイールの速度に変換するためのライブラリ

## 目次
- [OmniWheelController](#omniwheelcontroller)
  - [目次](#目次)
  - [クラステンプレート](#クラステンプレート)
  - [コンストラクタ](#コンストラクタ)
    - [OmniWheelController::OmniWheelControllerstd::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS>)](#omniwheelcontrolleromniwheelcontrollerstdarraymechanicparameter-number_of_omni_wheels)
  - [関数](#関数)
    - [OmniWheelController::update(CoordinateSystem_3D<float>, float)](#omniwheelcontrollerupdatecoordinatesystem_3dfloat-float)
    - [OmniWheelController::update(float, float, float, float)](#omniwheelcontrollerupdatefloat-float-float-float)
    - [OmniWheelController::get_wheel_velocity()](#omniwheelcontrollerget_wheel_velocity)
    - [OmniWheelController::get_wheel_velocity(uint8_t)](#omniwheelcontrollerget_wheel_velocityuint8_t)

## クラステンプレート
```c++
template <std::size_t NUMBER_OF_OMNI_WHEELS, typename OUTPUT_TYPE>
```
```yaml
NUMBER_OF_OMNI_WHEELS: オムニホイールの数
OUTPUT_TYPE: 各オムニホイールの速度の型
```

## コンストラクタ

##### OmniWheelController::OmniWheelControllerstd::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS>)
> ```c++
> OmniWheelController
> (
>   std::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS> mechanic_parameter
> ) 
> ```
> オムニホイールの取り付け位置を設定します。
> ```c++
> // 例
> aca::OmniWheelController<4, int16_t> omni_wheel_controller(
>   std::array<MechanicParameter, 4>{
>   	aca::MechanicParameter{ 3.0/4.0*M_PI, robot_radius},
>   	aca::MechanicParameter{-3.0/4.0*M_PI, robot_radius},
>   	aca::MechanicParameter{-1.0/4.0*M_PI, robot_radius},
>   	aca::MechanicParameter{ 1.0/4.0*M_PI, robot_radius}
>   }
> );
> ```

## 関数

##### OmniWheelController::update(CoordinateSystem_3D<float>, float)
> ```c++
> void update(
>   float field_velocity_x,
>   float field_velocity_y,
>   float angular_velocity,
>   float angle
> )
> ```
> 各ホイールの速度を更新します。
> ```c++
> // 例
> aca::field_velocity
> omniWheelController.update(field_velocity, angle);
> ```

##### OmniWheelController::update(float, float, float, float)
> ```c++
> void update(
>   float field_velocity_x,
>   float field_velocity_y,
>   float angular_velocity,
>   float angle
> )
> ```
> 各ホイールの速度を更新します。
> 内部で上記の update を実行しています。
> ```c++
> // 例
> omniWheelController.update(field_velocity_x, field_velocity_y, angular_velocity, angle);
> ```

##### OmniWheelController::get_wheel_velocity()
> ```c++
> std::array<OUTPUT_TYPE, NUMBER_OF_OMNI_WHEELS> get_wheel_velocity()
> ```
> 各ホイールの速度を保持したarray配列を返します。
> ```c++
> // 例
> omniWheelController.get_wheel_velocity();
> ```

##### OmniWheelController::get_wheel_velocity(uint8_t)
> ```c++
> OUTPUT_TYPE get_wheel_velocity(uint8_t wheel_number)
> ```
> 指定したホイールの速度を返します。
> ```c++
> // 例
> omniWheelController.get_wheel_velocity(0);
> ```