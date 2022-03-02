# Automatic_Control_Assistant - 3.2.0
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
    # タイトル
    概要説明

    ## 設計思想

    ## クラス

    ## 使用するのに必要な知識

    ## 理解するのに必要な知識

    ## サンプルプログラム
    ### コンストラクタ
    ### 更新と取得

    [<< 戻る](../README.md)
    ```

- コメント
  - 関数はソースファイルに、クラス,構造体,変数はヘッダファイルに Doxygen 形式でコメントを書く