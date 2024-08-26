#include "Player.h"
#include "Shutter.h"
#include "Stage.h"
#include "ModelDataManager.h"
#include "Enemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage()
    : shadowMapHandle       (-1)
{
    // データマネージャーのアドレスを所持
    modelDataManager = ModelDataManager::GetInstance();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
    // 終了処理
    Finalize();
}

/// <summary>
/// 初期化
/// </summary>
void Stage::Initialize()
{
    // モデル読み込み
    modelHandle = modelDataManager->GetDuplicatesModelHandle(ModelDataManager::ModelDataType::StageModelData);

    // モデルのスケールを調整
    // スケールを小さくしすぎると当たり判定できなくなる
    MV1SetScale(modelHandle, VGet(0.1,0.1,0.1));

    // スケールを調整
    MV1SetScale(modelHandle, StageModelScale);

    // モデル全体のコリジョン情報のセットアップ
    MV1SetupCollInfo(modelHandle, SelectCollisionEntire);
    
    isCreatedHitDim = false;


    // シャドウマップ // 

    // シャドウマップの作成
    shadowMapHandle = MakeShadowMap(2048, 2048);

    // シャドウマップに描画する範囲を設定
    SetShadowMapDrawArea(shadowMapHandle, VGet(-400, -1, -400), VGet(400, 10, 400));

    // ライトの方向を設定
    SetLightDirection(VGet(0.5f, 0.5f, 0.5f));

    // シャドウマップが想定するライトの方向もセット
    SetShadowMapLightDirection(shadowMapHandle, VGet(0.5f, -0.5f, 0.5f));

    // ステージモデル用のシャドウマップへの描画の準備
    ShadowMap_DrawSetup(shadowMapHandle);

    // ステージモデルに影を描画
    MV1DrawModel(modelHandle);

    // シャドウマップの描画終了
    ShadowMap_DrawEnd();
}

/// <summary>
/// タイトルシーンでの初期化
/// </summary>
void Stage::InitializeTitleScene()
{
    // モデル読み込み
    modelHandle = modelDataManager->GetDuplicatesModelHandle(ModelDataManager::ModelDataType::StageModelData);

    // モデルのスケールを調整
    // スケールを小さくしすぎると当たり判定できなくなる
    MV1SetScale(modelHandle, VGet(0.1, 0.1, 0.1));

    // スケールを調整
    MV1SetScale(modelHandle, StageModelScale);
}

/// <summary>
/// 終了時処理
/// </summary>
void Stage::Finalize()
{
    // ステージモデルの後始末
    MV1DeleteModel(modelHandle);
    if (isCreatedHitDim)
    {
        MV1CollResultPolyDimTerminate(hitDim);
        isCreatedHitDim = false;
    }
}

/// <summary>
/// 描画
/// </summary>
void Stage::Draw()
{
    // シャドウマップを使用する
    SetUseShadowMap(0, shadowMapHandle);

    // モデルの描画
    MV1DrawModel(modelHandle);

    // 描画のために使用するシャドウマップの設定を解除
    SetUseShadowMap(0, -1);
}

/// <summary>
/// ステージとの当たり判定
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="checkPosition">当たり判定をしたい座標</param>
/// <param name="moveVector"></param>
VECTOR Stage::IsHitCollision(Player& player, const VECTOR& checkPosition, const VECTOR& moveVector)
{
    // 検出したプレイヤーの周囲のポリゴン情報を開放する
    if (isCreatedHitDim)
    {
        MV1CollResultPolyDimTerminate(hitDim);
        isCreatedHitDim = false;
    }

    VECTOR fixedPosition = checkPosition;

    // プレイヤーの周囲にあるステージポリゴンを取得する
    // ( 検出する範囲は移動距離も考慮する )
    hitDim = MV1CollCheck_Sphere(modelHandle, -1, checkPosition, DefaultSize + VSize(moveVector));

    // 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
    AnalyzeWallAndFloor(checkPosition);

    // 壁ポリゴンとの当たり判定処理
    // 壁ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    fixedPosition = CheckHitWithWall(player, fixedPosition);

    // 床ポリゴンとの当たり判定
    // 床ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    fixedPosition = CheckHitWithFloor(player, fixedPosition);

    return fixedPosition;
}

/// <summary>
/// エネミーとステージの当たり判定
/// </summary>
/// <param name="player">エネミー</param>
/// <param name="checkPosition">当たり判定をしたい対象</param>
/// <param name="moveVector">移動方向</param>
VECTOR Stage::IsHitCollisionEnemy(Enemy& enemy, const VECTOR& checkPosition, const VECTOR& moveVector)
{
    // 検出したプレイヤーの周囲のポリゴン情報を開放する
    if (isCreatedHitDim)
    {
        MV1CollResultPolyDimTerminate(hitDim);
        isCreatedHitDim = false;
    }

    VECTOR fixedPosition = checkPosition;

    // プレイヤーの周囲にあるステージポリゴンを取得する
    // ( 検出する範囲は移動距離も考慮する )
    hitDim = MV1CollCheck_Sphere(modelHandle, -1, checkPosition, DefaultSize + VSize(moveVector));

    // 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
    AnalyzeWallAndFloor(checkPosition);

    // 壁ポリゴンとの当たり判定処理
    // 壁ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    fixedPosition = CheckHitWithWallEnemy(enemy, fixedPosition);

    // 床ポリゴンとの当たり判定
    // 床ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    //fixedPosition = CheckHitWithFloorEnemy(enemy, fixedPosition);

    return fixedPosition;
}

/// 判定処理する壁と床のポリゴン数を検出する
/// </summary>
/// <param name="CheckPosition">判定する座標</param>
void Stage::AnalyzeWallAndFloor(const VECTOR& CheckPosition)
{
    // 壁ポリゴンと床ポリゴンの数を初期化する
    wallNum = 0;
    floorNum = 0;

    // 検出されたポリゴンの数だけ繰り返し
    for (int i = 0; i < hitDim.HitNum; i++)
    {
        // ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
        // 法線とは表面に垂直なベクトルのこと
        if (hitDim.Dim[i].Normal.y < NormalVecterMaximumValue 
            && hitDim.Dim[i].Normal.y > NormalVecterMinimumValue)
        {
            // 壁ポリゴンと判断された場合でも、プレイヤーのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
            if (hitDim.Dim[i].Position[0].y > CheckPosition.y + CheckPositionOffset ||
                hitDim.Dim[i].Position[1].y > CheckPosition.y + CheckPositionOffset ||
                hitDim.Dim[i].Position[2].y > CheckPosition.y + CheckPositionOffset)
            {
                // ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
                if (wallNum < MaxHitColl)
                {
                    // ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
                    wall[wallNum] = &hitDim.Dim[i];

                    // 壁ポリゴンの数を加算する
                    wallNum++;
                }
            }
        }
        else
        {
            // ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
            if (floorNum < MaxHitColl)
            {
                // ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
                floor[floorNum] = &hitDim.Dim[i];

                // 床ポリゴンの数を加算する
                floorNum++;
            }
        }
    }
}

/// 壁ポリゴンとの当たり判定をチェックし、そこからずらす量を返す
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="CheckPosition">当たり判定する座標</param>
/// <returns>補正する移動ベクトル</returns>
VECTOR Stage::CheckHitWithWall(Player& player, const VECTOR& CheckPosition)
{
    VECTOR fixedPosition = CheckPosition;

    // 壁の数が無かったら早期リターン
    if (wallNum == 0)
    {
        return fixedPosition;
    }

    // 壁からの押し出し処理を試みる最大数だけ繰り返し
    for (int k = 0; k < HitTryNum; k++)
    {
        // 当たる可能性のある壁ポリゴンを全て見る
        bool isHitWall = false;
        for (int i = 0; i < wallNum; i++)
        {
            // i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
            auto floorPolygon = wall[i];

            // プレイヤーと当たっているなら
            if (HitCheck_Capsule_Triangle(fixedPosition, VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), HitWidth, floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]) == TRUE)
            {
                // 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
                // 移動後の位置を更新（移動後の場所を補正）
                fixedPosition = VAdd(fixedPosition, VScale(floorPolygon->Normal, HitSlideLength));

                // 移動した壁ポリゴンと接触しているかどうかを判定
                for (int j = 0; j < wallNum; j++)
                {
                    // 当たっていたらループを抜ける
                    floorPolygon = wall[j];
                    if (HitCheck_Capsule_Triangle(fixedPosition, VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), HitWidth, floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]) == TRUE)
                    {
                        isHitWall = true;
                        break;
                    }
                }

                // 全てのポリゴンと当たっていなかったらここでループ終了
                if (isHitWall == false)
                {
                    break;
                }
            }
        }

        // 全部のポリゴンで押し出しを試みる前に
        // 全ての壁ポリゴンと接触しなくなったらループから抜ける
        if (isHitWall == false)
        {
            break;
        }
    }

    return fixedPosition;
}

/// 床ポリゴンとの当たり判定をチェックし、そこからずらす量を返す
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="CheckPosition">当たり判定する座標</param>
/// <returns>補正する移動ベクトル</returns>
VECTOR Stage::CheckHitWithFloor(Player& player, const VECTOR& CheckPosition)
{
    VECTOR fixedPosition = CheckPosition;

    // 床の数が無かったら早期リターン
    if (floorNum == 0)
    {
        return fixedPosition;
    }

    // 当たったかどうかのフラグを初期化
    bool isHitFloor = false;

    // ジャンプ中且つ上昇中の場合は処理を分岐
    if (player.GetState() == Player::State::Jump
        && player.GetCurrentJumpPower() > 0.0f)
    {
        // 天井に頭をぶつける処理を行う
        // 一番低い天井にぶつける為の判定用変数を初期化
        float floorHeightMininum = 0.0f;

        // 床ポリゴンの数だけ繰り返し
        for (int i = 0; i < floorNum; i++)
        {
            // i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
            auto floorPolygon = floor[i];

            // 足先から頭の高さまでの間でポリゴンと接触しているかどうかを判定
            HITRESULT_LINE lineHitResult;             // 線分とポリゴンとの当たり判定の結果を代入する構造体
            lineHitResult = HitCheck_Line_Triangle(fixedPosition, VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]);

            // 接触していなかったら何もしない
            if (lineHitResult.HitFlag == TRUE)
            {
                // 既にポリゴンに当たっていて、且つ今まで検出した天井ポリゴンより高い場合は何もしない
                if (!(isHitFloor == true && floorHeightMininum < lineHitResult.Position.y))
                {
                    // ポリゴンに当たったフラグを立てる
                    isHitFloor = true;

                    // 接触したＹ座標を保存する
                    floorHeightMininum = lineHitResult.Position.y;
                }
            }
        }

        // 接触したポリゴンがあれば
        if (isHitFloor == true)
        {
            // 接触した場合はプレイヤーのＹ座標を接触座標を元に更新
            fixedPosition.y = floorHeightMininum - HitHeight;
            player.OnHitRoof();
        }
    }
    else
    {
        // 下降中かジャンプ中ではない場合の処理
        // 一番高い床ポリゴンにぶつける為の判定用変数を初期化
        float floorHeightMaximum = 0.0f;

        // 床ポリゴンの数だけ繰り返し
        for (int i = 0; i < floorNum; i++)
        {
            // i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
            auto floorPolygon = floor[i];

            // ジャンプ中かどうかで処理を分岐
            HITRESULT_LINE lineHitResult;           // 線分とポリゴンとの当たり判定の結果を代入する構造体
            if (player.GetState() == Player::State::Jump)
            {
                // ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
                lineHitResult = HitCheck_Line_Triangle(VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), VAdd(fixedPosition, VGet(0.0f, -1.0f, 0.0f)), floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]);
            }
            else
            {
                // 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
                lineHitResult = HitCheck_Line_Triangle(VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), VAdd(fixedPosition, VGet(0.0f, -40.0f, 0.0f)), floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]);
            }

            // 当たっていなかったら何もしない
            if (lineHitResult.HitFlag == TRUE)
            {
                // 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
                if (!(isHitFloor == true && floorHeightMaximum > lineHitResult.Position.y))
                {
                    // ポリゴンに当たったフラグを立てる
                    isHitFloor = true;

                    // 接触したＹ座標を保存する
                    floorHeightMaximum = lineHitResult.Position.y;
                }
            }
        }

        // 床ポリゴンに当たったかどうかで処理を分岐
         if (isHitFloor == true)
        {
            // 当たった場合
            // 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
            fixedPosition.y = floorHeightMaximum;

            // 床に当たった時
            player.OnHitFloor();
        }
    }

    return fixedPosition;
}


VECTOR Stage::CheckHitWithWallEnemy(Enemy& enemy, const VECTOR& CheckPosition)
{
    VECTOR fixedPosition = CheckPosition;

    // 壁の数が無かったら早期リターン
    if (wallNum == 0)
    {
        return fixedPosition;
    }

    // 壁からの押し出し処理を試みる最大数だけ繰り返し
    for (int k = 0; k < HitTryNum; k++)
    {
        // 当たる可能性のある壁ポリゴンを全て見る
        bool isHitWall = false;
        for (int i = 0; i < wallNum; i++)
        {
            // i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
            auto floorPolygon = wall[i];

            // プレイヤーと当たっているなら
            if (HitCheck_Capsule_Triangle(fixedPosition, VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), HitWidth, floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]) == TRUE)
            {
                // 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
                // 移動後の位置を更新（移動後の場所を補正）
                fixedPosition = VAdd(fixedPosition, VScale(floorPolygon->Normal, HitSlideLength));

                // 移動した壁ポリゴンと接触しているかどうかを判定
                for (int j = 0; j < wallNum; j++)
                {
                    // 当たっていたらループを抜ける
                    floorPolygon = wall[j];
                    if (HitCheck_Capsule_Triangle(fixedPosition, VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), HitWidth, floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]) == TRUE)
                    {
                        isHitWall = true;
                        break;
                    }
                }

                // 全てのポリゴンと当たっていなかったらここでループ終了
                if (isHitWall == false)
                {
                    break;
                }
            }
        }

        // 全部のポリゴンで押し出しを試みる前に
        // 全ての壁ポリゴンと接触しなくなったらループから抜ける
        if (isHitWall == false)
        {
            break;
        }
    }

    return fixedPosition;

}


//VECTOR Stage::CheckHitWithFloorEnemy(Enemy& enemy, const VECTOR& CheckPosition)
//{
//    VECTOR fixedPosition = CheckPosition;
//
//    // 床の数が無かったら早期リターン
//    if (floorNum == 0)
//    {
//        return fixedPosition;
//    }
//
//    // 当たったかどうかのフラグを初期化
//    bool isHitFloor = false;
//
//    // ジャンプ中且つ上昇中の場合は処理を分岐
//    if (false)
//    {
//        // 天井に頭をぶつける処理を行う
//        // 一番低い天井にぶつける為の判定用変数を初期化
//        float floorHeightMininum = 0.0f;
//
//        // 床ポリゴンの数だけ繰り返し
//        for (int i = 0; i < floorNum; i++)
//        {
//            // i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
//            auto floorPolygon = floor[i];
//
//            // 足先から頭の高さまでの間でポリゴンと接触しているかどうかを判定
//            HITRESULT_LINE lineHitResult;             // 線分とポリゴンとの当たり判定の結果を代入する構造体
//            lineHitResult = HitCheck_Line_Triangle(fixedPosition, VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]);
//
//            // 接触していなかったら何もしない
//            if (lineHitResult.HitFlag == TRUE)
//            {
//                // 既にポリゴンに当たっていて、且つ今まで検出した天井ポリゴンより高い場合は何もしない
//                if (!(isHitFloor == true && floorHeightMininum < lineHitResult.Position.y))
//                {
//                    // ポリゴンに当たったフラグを立てる
//                    isHitFloor = true;
//
//                    // 接触したＹ座標を保存する
//                    floorHeightMininum = lineHitResult.Position.y;
//                }
//            }
//        }
//
//        // 接触したポリゴンがあれば
//        if (isHitFloor == true)
//        {
//            // 接触した場合はプレイヤーのＹ座標を接触座標を元に更新
//            fixedPosition.y = floorHeightMininum - HitHeight;
//            enemy.OnHitRoof();
//        }
//    }
//    else
//    {
//        // 下降中かジャンプ中ではない場合の処理
//        // 一番高い床ポリゴンにぶつける為の判定用変数を初期化
//        float floorHeightMaximum = 0.0f;
//
//        // 床ポリゴンの数だけ繰り返し
//        for (int i = 0; i < floorNum; i++)
//        {
//            // i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
//            auto floorPolygon = floor[i];
//
//            // ジャンプ中かどうかで処理を分岐
//            HITRESULT_LINE lineHitResult;           // 線分とポリゴンとの当たり判定の結果を代入する構造体
//            if (enemy.GetState() == Player::State::Jump)
//            {
//                // ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
//                lineHitResult = HitCheck_Line_Triangle(VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), VAdd(fixedPosition, VGet(0.0f, -1.0f, 0.0f)), floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]);
//            }
//            else
//            {
//                // 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
//                lineHitResult = HitCheck_Line_Triangle(VAdd(fixedPosition, VGet(0.0f, HitHeight, 0.0f)), VAdd(fixedPosition, VGet(0.0f, -40.0f, 0.0f)), floorPolygon->Position[0], floorPolygon->Position[1], floorPolygon->Position[2]);
//            }
//
//            // 当たっていなかったら何もしない
//            if (lineHitResult.HitFlag == TRUE)
//            {
//                // 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
//                if (!(isHitFloor == true && floorHeightMaximum > lineHitResult.Position.y))
//                {
//                    // ポリゴンに当たったフラグを立てる
//                    isHitFloor = true;
//
//                    // 接触したＹ座標を保存する
//                    floorHeightMaximum = lineHitResult.Position.y;
//                }
//            }
//        }
//
//        // 床ポリゴンに当たったかどうかで処理を分岐
//        if (isHitFloor == true)
//        {
//            // 当たった場合
//            // 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
//            fixedPosition.y = floorHeightMaximum;
//
//            // 床に当たった時
//            enemy.OnHitFloor();
//        }
//    }
//
//    return fixedPosition;
//
//}
