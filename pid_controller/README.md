# PID_controller

通常のPID(位置型PID)を簡単に実装できるライブラリです

## 用語

##### update関数を呼び出す周波数とupdate関数を実行したい周波数の割合

例えば関数を呼び出すのは1000Hzだけど実際に計算したいのは100Hzなどの場合は

1000 ÷ 100 = 10

ということで10になります。

update関数を呼び出す周波数とupdate関数を実行したい周波数が同じであれば割合は1になります。


## コンストラクタ

どちらかを選んで呼び出してください

##### PID_controller::PID_controller(const PID_Element &index,const float frequency)

PID_ElementというPIDのパラメータを保持する構造体を、frenquencyにはupdate関数を呼び出す周波数とupdate関数を実行したい周波数の割合を入れてください
```c++
//例
PID_controller pid_controller(index,1);
```

##### PID_controller::PID_controller(float proportional,float integral,float differential,const float frequency)

proportionalにはpのゲイン、integralにはiのゲイン、differentialにはdのゲイン、frenquencyにはupdate関数を呼び出す周波数とupdate関数を実行したい周波数の割合を入れてください
```c++
//例
PID_controller pid_controller(1, 0.4, 0.02, 1);
```

## 関数

##### void PID_controller::setTarget(float target)

目標値を設定します
```c++
//例
pid_controller.setTarget(1000);
```

##### void PID_controller::updateOperation(float basis)

現在の制御したい値を受け取り、内部で出力する値の更新を行います
```c++
//例
pid_controller.updateOperation(position_x);
```

##### void PID_controller::updateOperation(float target, float basis)

目標値の設定と内部で出力する値の更新を同時に行います
```c++
//例
pid_controller.updateOperation(target_position_x, position_x);
```

##### void PID_controller::resetIntegral()

i成分を0にします
```c++
//例
pid_controller.resetIntegral()
```

##### float PID_controller::getOperation()

出力値を返します


```c++
//例
velocity_x = pid_controller.getOperation();
```




# PID_controller_velocity

## コンストラクタ

どちらかを選んで呼び出してください

##### PID_controller_velocity::PID_controller_velocity(const PID_Element &index,const float frequency)

PID_ElementというPIDのパラメータを保持する構造体を、frenquencyにはupdate関数を呼び出す周波数とupdate関数を実行したい周波数の割合を入れてください
```c++
//例
PID_controller pid_controller(index,1);
```

##### PID_controller_velocity::PID_controller_velocity(float proportional,float integral,float differential,const float frequency)

proportionalにはpのゲイン、integralにはiのゲイン、differentialにはdのゲイン、frenquencyにはupdate関数を呼び出す周波数とupdate関数を実行したい周波数の割合を入れてください
```c++
//例
PID_controller pid_controller(1, 0.4, 0.02, 1);
```

## 関数

###### void PID_controller_velocity::setTarget(float target)

目標値を設定します
```c++
//例
pid_controller_velocity.setTarget(1000);
```

##### void PID_controller_velocity::updateOperation(float basis)

現在の制御したい値を受け取り、内部で出力する値の更新を行います
```c++
//例
pid_controller_velocity.updateOperation(position_x);
```

##### void PID_controller_velocity::updateOperation(float target, float basis)

目標値の設定と内部で出力する値の更新を同時に行います
```c++
//例
pid_controller_velocity.updateOperation(target_position_x, position_x);
```

##### float PID_controller_velocity::getOperation()

出力値を返します
```c++
//例
velocity_x = pid_controller_velocity.getOperation();
```

###### void PID_controller_velocity::resetOperation()

出力値を0にします
```c++
//例
pid_controller_velocity.resetOperation();
```
