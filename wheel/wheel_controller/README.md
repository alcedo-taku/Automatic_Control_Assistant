# WheelController

駆動のための、x,y,回転方向の速度を各ホイールの速度に変換するためのライブラリ

## 目次
- [WheelController](#wheelcontroller)
  - [目次](#目次)
  - [クラステンプレート](#クラステンプレート)
  - [関数](#関数)
    - [WheelController::update(CoordinateSystem_3D<float>, float)](#wheelcontrollerupdatecoordinatesystem_3dfloat-float)
    - [WheelController::update(float, float, float, float)](#wheelcontrollerupdatefloat-float-float-float)
    - [WheelController::get_wheel_velocity()](#wheelcontrollerget_wheel_velocity)
    - [WheelController::get_wheel_velocity(uint8_t)](#wheelcontrollerget_wheel_velocityuint8_t)
- [OmniWheelController](#omniwheelcontroller)
  - [クラステンプレート](#クラステンプレート-1)
  - [コンストラクタ](#コンストラクタ)
    - [OmniWheelController::OmniWheel(std::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS>)](#omniwheelcontrolleromniwheelstdarraymechanicparameter-number_of_omni_wheels)
- [MecanumWheelController](#mecanumwheelcontroller)
  - [クラステンプレート](#クラステンプレート-2)
  - [コンストラクタ](#コンストラクタ-1)
    - [MecanumWheelController::MecanumWheelController(float, float)](#mecanumwheelcontrollermecanumwheelcontrollerfloat-float)

## クラステンプレート
```c++
template <std::size_t NUMBER_OF_WHEELS, typename OUTPUT_TYPE>
```
```yaml
NUMBER_OF_OMNI_WHEELS: ホイールの数
OUTPUT_TYPE: 各ホイールの速度の型
```

## 関数

##### WheelController::update(CoordinateSystem_3D<float>, float)
> ```c++
> void update(
>   CoordinateSystem_3D<float> field_velocity,
>   float angle
> )
> ```
> 各ホイールの速度を更新します。
> ```c++
> // 例
> aca::field_velocity = {field_velocity_x, field_velocity_y, angular_velocity};
> omniWheelController.update(field_velocity, angle);
> ```

##### WheelController::update(float, float, float, float)
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

##### WheelController::get_wheel_velocity()
> ```c++
> std::array<OUTPUT_TYPE, NUMBER_OF_OMNI_WHEELS> get_wheel_velocity()
> ```
> 各ホイールの速度を保持したarray配列を返します。
> ```c++
> // 例
> omniWheelController.get_wheel_velocity();
> ```

##### WheelController::get_wheel_velocity(uint8_t)
> ```c++
> OUTPUT_TYPE get_wheel_velocity(uint8_t wheel_number)
> ```
> 指定したホイールの速度を返します。
> ```c++
> // 例
> omniWheelController.get_wheel_velocity(0);
> ```


# OmniWheelController

オムニホイール駆動のため、WheelController を継承したライブラリ

## クラステンプレート
```c++
template <std::size_t NUMBER_OF_OMNI_WHEELS, typename OUTPUT_TYPE>
```
```yaml
NUMBER_OF_OMNI_WHEELS: オムニホイールの数
OUTPUT_TYPE: 各オムニホイールの速度の型
```

## コンストラクタ

##### OmniWheelController::OmniWheel(std::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS>)
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


# MecanumWheelController

メカナムホイール駆動のための、WheelController を継承したライブラリ

## クラステンプレート
```c++
template <typename OUTPUT_TYPE>
```
```yaml
OUTPUT_TYPE: 各メカナムホイールの速度の型
```

## コンストラクタ

##### MecanumWheelController::MecanumWheelController(float, float)
> ```c++
> MecanumWheelController
> (
>   float a,
>   float b
> ) 
> ```
> メカナムホイールの取り付け位置を設定します。  
> a: 左右のホイールの距離の半分  
> b: 前後のホイールの距離の半分  
> ```c++
> // 例
> aca::MecanumWheelController<int16_t> omni_wheel_controller(a, b);
> ```
