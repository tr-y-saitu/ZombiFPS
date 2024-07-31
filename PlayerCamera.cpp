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
    , cameraPitch           (0.0f)
    , targetPosition        (VGet(0,0,0))
    , cameraPosition        (VGet(0,0,0))
    , cameraRightVector     (VGet(0,0,0))
{
    // 描画範囲の設定
    SetCameraNearFar(CameraNearClip, CameraFarClip);

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
/// <param name="input">入力情報</param>
/// <param name="setPostion">設定する座標</param>
/// <param name="stage">ステージ</param>
void PlayerCamera::Update(const Input& input, VECTOR setPosition, const Stage& stage)
{
    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();


#ifdef USE_MOUSE
    // マウスを使ってカメラの角度を更新
    UpdateCameraAngleMouse(input);
#else
    // パッド、キーボード入力でカメラの角度を更新
    UpdateCameraAngle(input);
#endif

    // カメラの注視点をプレイヤーよりも上に設定
    targetPosition = VAdd(setPosition, CameraPlayerTargetPosition);

    // カメラの座標を補正する
    FixCameraPosition(stage,setPosition);

    // カメラの前方向ベクトルの更新
    UpdateCameraForwardVector();

    // カメラの右方向ベクトルを更新
    UpdateCameraRightVector();

    // 腰だめの位置にカメラを移動させる
    UpdateHipUpPosition(setPosition);

    // カメラのピッチ角度計算
    UpdateCameraPitch();

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
/// マウスでのカメラ角度更新
/// </summary>
/// <param name="input">入力更新情報</param>
void PlayerCamera::UpdateCameraAngleMouse(const Input& input)
{
    // マウスカーソル位置の取得
    Input::MousePosition mousePosition = input.GetMousePosition();

    // 画面の中心からどのくらい離れているか
    int deltaX = mousePosition.x - ScreenWidthHalf;
    int deltaY = mousePosition.y - ScreenHeightHalf;

    // マウス感度を設定
    float mouseSensitivity = input.MouseSensitivity;

    // 水平角度を更新
    if (fabs(deltaX) * mouseSensitivity >= MouseInputDeadZoneMin)
    {
        angleHorizon += deltaX * mouseSensitivity;
    }

    // １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
    if (angleHorizon > DX_PI_F)
    {
        angleHorizon -= DX_TWO_PI_F;
    }
    else if (angleHorizon < -DX_PI_F)
    {
        angleHorizon += DX_TWO_PI_F;
    }

    // 垂直角度を更新
    if (fabs(deltaY) * mouseSensitivity >= MouseInputDeadZoneMin)
    {
        angleVertical -= deltaY * mouseSensitivity;
    }

    // ある一定角度以上/以下にはならないようにする
    float maxVerticalAngle = DX_PI_F / 2.0f - 0.6;
    float minVerticalAngle = -DX_PI_F / AngleVerticalOffset;

    if (angleVertical > maxVerticalAngle)
    {
        angleVertical = maxVerticalAngle;
    }
    else if (angleVertical < minVerticalAngle)
    {
        angleVertical = minVerticalAngle;
    }
}

/// <summary>
/// カメラ座標の修正
/// </summary>
/// <param name="stage">ステージ</param>
void PlayerCamera::FixCameraPosition(const Stage& stage, VECTOR setPosition)
{
    MATRIX rotateZ, rotateY;
    float cameraPlayerLength;
    MV1_COLL_RESULT_POLY_DIM hitResult;
    int hitNum;

    // 水平方向の回転はＹ軸回転
    rotateY = MGetRotY(angleHorizon);

    // 垂直方向の回転はＺ軸回転 )
    rotateZ = MGetRotZ(angleVertical);

    // カメラからプレイヤーまでの初期距離をセット
    cameraPlayerLength = ToPlayerLength;

    // カメラの座標を算出
    // Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
    // 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
    // 注視点の座標を足したものがカメラの座標
    VECTOR cameraOffest = VGet(-cameraPlayerLength, 0.0f, 0.0f);
    cameraPosition = VAdd(VTransform(VTransform(cameraOffest, rotateZ), rotateY), targetPosition);

    // 注視点からカメラの座標までの間にステージのポリゴンがあるか調べる
    hitResult = MV1CollCheck_Capsule(stage.GetModelHandle(), -1, targetPosition, cameraPosition, CollisionSize);
    hitNum = hitResult.HitNum;
    MV1CollResultPolyDimTerminate(hitResult);
    if (hitNum != 0)
    {
        float noHItLength;
        float hitLength;
        float testLength;
        VECTOR testPosition;

        // あったら無い位置までプレイヤーに近づく

        // ポリゴンに当たらない距離をセット
        noHItLength = 0.0f;

        // ポリゴンに当たる距離をセット
        hitLength = cameraPlayerLength;
        do
        {
            // 当たるかどうかテストする距離をセット( 当たらない距離と当たる距離の中間 )
            testLength = noHItLength + (hitLength - noHItLength) / 2.0f;

            // テスト用のカメラ座標を算出
            testPosition = VAdd(VTransform(VTransform(VGet(-testLength, 0.0f, 0.0f), rotateZ), rotateY), targetPosition);

            // 新しい座標で壁に当たるかテスト
            hitResult = MV1CollCheck_Capsule(stage.GetModelHandle(), -1, targetPosition, testPosition, CollisionSize);
            hitNum = hitResult.HitNum;
            MV1CollResultPolyDimTerminate(hitResult);
            if (hitNum != 0)
            {
                // 当たったら当たる距離を testLength に変更する
                hitLength = testLength;
            }
            else
            {
                // 当たらなかったら当たらない距離を testLength に変更する
                noHItLength = testLength;
            }

            // hitLength と NoHitLength が十分に近づいていなかったらループ
        } while (hitLength - noHItLength > 0.1f);

        // カメラの座標をセット
        cameraPosition = testPosition;
    }
}

/// <summary>
/// カメラの前方向ベクトルを更新する
/// </summary>
void PlayerCamera::UpdateCameraForwardVector()
{
    // カメラから視点方向へのベクトル
    cameraForwardVector = VSub(targetPosition, cameraPosition);

    // 正規化
    cameraForwardVector = VNorm(cameraForwardVector);
}

/// <summary>
/// カメラの右方向ベクトルを更新する
/// </summary>
void PlayerCamera::UpdateCameraRightVector()
{
    // 前方向ベクトルと上方向ベクトルの外積で右方向ベクトルを求める
    VECTOR cameraUpVector = VGet(0, 1, 0);
    cameraRightVector = VNorm(VCross(cameraUpVector, cameraForwardVector));
}

/// <summary>
/// カメラを腰だめの位置に調整する
/// </summary>
/// <param name="setPosition">基準となる座標</param>
void PlayerCamera::UpdateHipUpPosition(VECTOR setPosition)
{
    // カメラのオフセット量を計算
    // プレイヤーよりも少し左後ろに移動
    VECTOR cameraOffset = VAdd(VScale(cameraRightVector, LeftOffset), VScale(cameraForwardVector, BackOffset));

    // カメラ自体の座標更新
    cameraPosition = VAdd(setPosition, cameraOffset);

    // カメラの右方向ベクトルを取得
    VECTOR rightVector = cameraRightVector;

    // 腰だめの位置にカメラを調整する
    // (プレイヤーよりも少し左を見つめる)
    VECTOR leftOffset = VScale(rightVector, ViewTargetShiftLeftOffset);

    // カメラの視点を更新
    targetPosition = VAdd(targetPosition, leftOffset);

}

/// <summary>
/// カメラのピッチ角度を更新する
/// </summary>
/// HACK:
/// ピッチ：上下角度
/// プレイヤーモデルとプレイヤーカメラの角度は同期しているので、
/// 上下角度のみこの関数で更新
void PlayerCamera::UpdateCameraPitch()
{  
    // カメラの前方向ベクトル取得（カメラがどこを向いているのか）
    VECTOR forwardVector = cameraForwardVector;

    //---- カメラが上下にどのくらい傾いているかを計算 ----//
    
    // 前方向ベクトルの長さを計算
    // MEMO：
    //  この軸から回転させる
    //  X軸とZ軸とで作った平面からどの程度カメラの前方向ベクトルが伸びているかが計算される
    float horizonLength = sqrt(forwardVector.x * forwardVector.x + forwardVector.z * forwardVector.z);
    
    // X軸とZ軸から作った平面の長さからどのくらい傾いているか計算
    // MEMO:
    //  horizonLengthを２次元平面上の軸とし、
    //  そこからforwardVector.yまでどのくらいの角度があるかを計算する
    cameraPitch = atan2f(forwardVector.y, horizonLength);
}
