# Automatic_Control_Assistant - 3.3.0
```c++
#include "Automatic_Control_Assistant.hpp"
```

```c++
namespace aca
```

## 目次
- [Wheel](wheel/README.md)
  - [WheelController](wheel/wheel_controller/README.md)
    - OmniWheelController
    - MecanumWheelController
  - [CoordinateMeasurer](wheel/coordinate_measurer/README.md)
    - CoordinateMeasurerLine
    - CoordinateMeasurerTriangle
- [TargetBasedOnTime](target_based_on_time/README.md)
- [PID_controller](pid_controller/README.md)

## 設計思想
- HALライブラリの環境に依存しない

## フォーマット
- README
  - 以下のテンプレートに沿って書く
    ```md
    # タイトル(クラス名)
    概要説明

    ## 設計思想(省略可)

    ## クラス(クラスが複数含まれる場合のみ) 

    ## 使用するのに必要な知識(省略可)

    ## 理解するのに必要な知識(省略可)

    ## サンプルプログラム
    (主要な関数のみで良い)
    ### コンストラクタ
    ### 初期化
    ### 更新と取得

    [<< 戻る](../README.md)
    ```

- コメント
  - 関数はソースファイルに、クラス,構造体,変数はヘッダファイルに Doxygen 形式でコメントを書く