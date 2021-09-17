# 変更履歴

## v3.2.1
- ドキュメント
  - 目次を修正

## v3.2.0
- クラスを追加
  - `CoordinateMeasurer`
    - `CoordinateMeasurerLine`
    - `CoordinateMeasurerTriangle`
  - `WheelController`
    - (`OmniWheelController`)(既存のクラスを`WheelController`の派生クラスにした)
    - `MecanumWheelController`
- ドキュメント
  - 理解するのに必要な知識 を追加
  - 設計思想 を追加
- TargetBasedOnTime
  - 目標位置と現在位置の差が0の時、NaNを出力するバグを修正
  - 初期速度、最終速度が負の方向に最高速度より大きかったとき、訂正しないバグを修正
  - 初期位置が目標位置より大きいとき、初期速度と最終速度の正負が入れ替わるバグを修正

## v3.1.0
- OmniWheelController
  - 各ホイールの情報を個別に指定できるようにした

## v3.0.2
- PID_Controller
  - init関数で、指定していない値が自動的に0になるバグを修正

## v3.0.1
- PID_Controller
  - const変数を普通の変数に修正した

## v3.0.0
- namespace `aca` を追加
- クラスを追加
  - `OmniWheelController`
- PID_Controller
  - init関数を追加
  - `index` を `pid_parameter` に名前変更
  - README をわかりやすくした

## v2.3.0
- クラスを追加 
  - `PID_Controller`

## v2.2.0
- TargetBasedOnTime
  - 初期速度と最終速度を設定できる機能を追加
  - time のデータ型を uint32_t に変更

## v2.1.0
- TargetBasedOnTime
  - デバッグ用のプログラムをdebugフォルダに入れた

## v2.0.0
- Inc ディレクトリを削除

## v1.0.0
- クラスを追加
    - `TargetBasedOnTime`
