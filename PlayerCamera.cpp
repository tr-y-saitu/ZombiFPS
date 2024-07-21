#include "PlayerCamera.h"
#include "Input.h"
#include "Player.h"
#include "Stage.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerCamera::PlayerCamera()
    : angleHorizon          (DX_PI_F)
    , angleVertical         (0.0f)
    , targetPosition        (VGet(0,0,0))
    , cameraPosition        (VGet(0,0,0))
{
    // 描画範囲の設定
    SetCameraNearFar(0.1f, 600.0f);

    // カメラを設定
    SetCameraPositionAndTarget_UpVecY(cameraPosition, targetPosition);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerCamera::~PlayerCamera()
{
    // 処理なし
}

/// <summary>
/// 初期化
/// </summary>
void PlayerCamera::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void PlayerCamera::Update(const Input& input, const Player& player, const Stage& stage)
{
    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();

    // カメラの角度を更新
    UpdateCameraAngle(input);

    // カメラの注視点をプレイヤーよりも上に設定
    targetPosition = VAdd(player.GetPosition(), CameraPlayerTargetPosition);

    // カメラの座標を補正する
    FixCameraPosition(stage);

    // カメラの更新
    SetCameraPositionAndTarget_UpVecY(cameraPosition, targetPosition);
}

/// <summary>
/// カメラの角度を更新する
/// </summary>
/// <param name="input">入力処理</param>
void PlayerCamera::UpdateCameraAngle(const Input& input)
{
    // パッドの３ボタンか、シフトキーが押されている場合のみ角度変更操作を行う
    if (CheckHitKey(KEY_INPUT_LSHIFT) || (input.GetCurrentFrameInput() & PAD_INPUT_C))
    {
        // 「←」ボタンが押されていたら水平角度をマイナスする
        if (input.GetCurrentFrameInput() & PAD_INPUT_LEFT)
        {
            angleHorizon -= AngleSpeed;
        
            // －１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
            if (angleHorizon < -DX_PI_F)
            {
                angleHorizon += DX_TWO_PI_F;
            }
        }
        
        // 「→」ボタンが押されていたら水平角度をプラスする
        if (input.GetCurrentFrameInput() & PAD_INPUT_RIGHT)
        {
            angleHorizon += AngleSpeed;
    
            // １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
            if (angleHorizon > DX_PI_F)
            {
                angleHorizon -= DX_TWO_PI_F;
            }
        }
        
        // 「↑」ボタンが押されていたら垂直角度をマイナスする
        if (input.GetCurrentFrameInput() & PAD_INPUT_UP)
        {
            angleVertical -= AngleSpeed;
    
            // ある一定角度以下にはならないようにする
            if (angleVertical < -DX_PI_F / AngleVerticalOffset)
            {
                angleVertical = -DX_PI_F / AngleVerticalOffset;
            }
        }
        
        // 「↓」ボタンが押されていたら垂直角度をプラスする
        if (input.GetCurrentFrameInput() & PAD_INPUT_DOWN)
        {
            angleVertical += AngleSpeed;
    
            // ある一定角度以上にはならないようにする
            if (angleVertical > DX_PI_F / 2.0f - 0.6f)
            {
                angleVertical = DX_PI_F / 2.0f - 0.6f;
            }
        }
    }
}

/// <summary>
/// カメラ座標の修正
/// </summary>
/// <param name="stage">ステージ</param>
void PlayerCamera::FixCameraPosition(const Stage& stage)
{
    MATRIX RotZ, RotY;
    float CameraPlayerLength;
    MV1_COLL_RESULT_POLY_DIM HitResult;
    int HitNum;

    // 水平方向の回転はＹ軸回転
    RotY = MGetRotY(angleHorizon);

    // 垂直方向の回転はＺ軸回転 )
    RotZ = MGetRotZ(angleVertical);

    // カメラからプレイヤーまでの初期距離をセット
    CameraPlayerLength = ToPlayerLength;

    // カメラの座標を算出
    // Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
    // 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
    // 注視点の座標を足したものがカメラの座標
    cameraPosition = VAdd(VTransform(VTransform(VGet(-CameraPlayerLength, 0.0f, 0.0f), RotZ), RotY), targetPosition);

    // 注視点からカメラの座標までの間にステージのポリゴンがあるか調べる
    HitResult = MV1CollCheck_Capsule(stage.GetModelHandle(), -1, targetPosition, cameraPosition, CollisionSize);
    HitNum = HitResult.HitNum;
    MV1CollResultPolyDimTerminate(HitResult);
    if (HitNum != 0)
    {
        float NotHitLength;
        float HitLength;
        float TestLength;
        VECTOR TestPosition;

        // あったら無い位置までプレイヤーに近づく

        // ポリゴンに当たらない距離をセット
        NotHitLength = 0.0f;

        // ポリゴンに当たる距離をセット
        HitLength = CameraPlayerLength;
        do
        {
            // 当たるかどうかテストする距離をセット( 当たらない距離と当たる距離の中間 )
            TestLength = NotHitLength + (HitLength - NotHitLength) / 2.0f;

            // テスト用のカメラ座標を算出
            TestPosition = VAdd(VTransform(VTransform(VGet(-TestLength, 0.0f, 0.0f), RotZ), RotY), targetPosition);

            // 新しい座標で壁に当たるかテスト
            HitResult = MV1CollCheck_Capsule(stage.GetModelHandle(), -1, targetPosition, TestPosition, CollisionSize);
            HitNum = HitResult.HitNum;
            MV1CollResultPolyDimTerminate(HitResult);
            if (HitNum != 0)
            {
                // 当たったら当たる距離を TestLength に変更する
                HitLength = TestLength;
            }
            else
            {
                // 当たらなかったら当たらない距離を TestLength に変更する
                NotHitLength = TestLength;
            }

            // HitLength と NoHitLength が十分に近づいていなかったらループ
        } while (HitLength - NotHitLength > 0.1f);

        // カメラの座標をセット
        cameraPosition = TestPosition;
    }
}