# CoordinateMeasurer

自己位置推定のためのライブラリ


## 計測輪の配置
![計測輪配置の図](measuring_wheel_position.png "計測輪配置")
数字：計測輪の番号  
矢印：正の方向  
※ 四角形配置は未実装


## サンプルプログラム
詳細は [coordinate_measurer.hpp](..\coordinate_measurer.hpp) に書いてあるので、参照すること。
三角形配置の場合を記すが、H型配置の場合も同様

### コンストラクタ
引数：PPR, 計測輪半径, 取付半径
```C++
aca::CoordinateMeasurerLine coordinate_measurer(1000, 30, 270);
```

### 座標の更新と取得
```C++
std::array<int32_t,3> encoder_count; // 現在のエンコーダのカウント
coordinate_measurer.update(encoder_count);

aca::Coordinate coordinate;
coordinate = coordinate_measurer.get_coordinate();
```

### 座標の上書き
x方向はそのままで、y方向にキャリブレーションした場合
```C++
coordinate_measurer.overwriteCoordinate(
    aca::Coordinate{coordinate.x, 0, 0}
);
```