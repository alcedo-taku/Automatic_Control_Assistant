# MecanumWheelController

オムニホイール駆動のための、x,y,回転方向の速度を各ホイールの速度に変換するためのライブラリ

## 目次
- [MecanumWheelController](#MecanumWheelController)
    - [目次](#目次)
    - [クラステンプレート](#クラステンプレート)
    - [コンストラクタ](#コンストラクタ)
        - [MecanumWheelController::MecanumWheelControllerstd::array<MechanicParameter, NUMBER_OF_OMNI_WHEELS>)](#MecanumWheelControllerMecanumWheelControllerstdarraymechanicparameter-number_of_omni_wheels)
    - [関数](#関数)
        - [MecanumWheelController::update(CoordinateSystem_3D<float>, float)](#MecanumWheelControllerupdatecoordinatesystem_3dfloat-float)
        - [MecanumWheelController::update(float, float, float, float)](#MecanumWheelControllerupdatefloat-float-float-float)
        - [MecanumWheelController::get_wheel_velocity()](#MecanumWheelControllerget_wheel_velocity)
        - [MecanumWheelController::get_wheel_velocity(uint8_t)](#MecanumWheelControllerget_wheel_velocityuint8_t)

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
> ```c++
> // 例
> aca::MecanumWheelController<int16_t> omni_wheel_controller(a, b);
> ```

## 関数

##### MecanumWheelController::update(CoordinateSystem_3D<float>, float)
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
> aca::field_velocity = {field_velocity_x, field_velocity_y, angular_velocity};
> MecanumWheelController.update(field_velocity, angle);
> ```

##### MecanumWheelController::update(float, float, float, float)
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
> MecanumWheelController.update(field_velocity_x, field_velocity_y, angular_velocity, angle);
> ```

##### MecanumWheelController::get_wheel_velocity()
> ```c++
> std::array<OUTPUT_TYPE, NUMBER_OF_OMNI_WHEELS> get_wheel_velocity()
> ```
> 各ホイールの速度を保持したarray配列を返します。
> ```c++
> // 例
> MecanumWheelController.get_wheel_velocity();
> ```

##### MecanumWheelController::get_wheel_velocity(uint8_t)
> ```c++
> OUTPUT_TYPE get_wheel_velocity(uint8_t wheel_number)
> ```
> 指定したホイールの速度を返します。
> ```c++
> // 例
> MecanumWheelController.get_wheel_velocity(0);
> ```