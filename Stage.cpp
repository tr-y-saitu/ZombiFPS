#include "Player.h"
#include "Shutter.h"
#include "Stage.h"

/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage()
{
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
    // ステージモデルの読み込み
    modelHandle = MV1LoadModel("Data/Stage/BO2Map.mv1");
    MV1SetScale(modelHandle, VGet(4, 4, 4));
    
    // モデル全体のコリジョン情報のセットアップ
    MV1SetupCollInfo(modelHandle, -1);
    
    // テスト
    MV1SetPosition(modelHandle,VGet(0,0,0));

    isCreatedHitDim = false;
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
	MV1DrawModel(modelHandle);
}

/// <summary>
/// ステージとの当たり判定
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="checkPosition">当たり判定をしたい座標</param>
/// <param name="moveVector"></param>
void Stage::IsHitCollision(Player& player, const VECTOR& checkPosition, const VECTOR& moveVector)
{
    // 検出したプレイヤーの周囲のポリゴン情報を開放する
    if (isCreatedHitDim)
    {
        MV1CollResultPolyDimTerminate(hitDim);
        isCreatedHitDim = false;
    }

    VECTOR FixedPos = checkPosition;

    // プレイヤーの周囲にあるステージポリゴンを取得する
    // ( 検出する範囲は移動距離も考慮する )
    hitDim = MV1CollCheck_Sphere(modelHandle, -1, checkPosition, DefaultSize + VSize(moveVector));

    // 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
    AnalyzeWallAndFloor(checkPosition);

    // 壁ポリゴンとの当たり判定処理
    // 壁ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    FixedPos = CheckHitWithWall(player, FixedPos);

    // 床ポリゴンとの当たり判定
    // 床ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    FixedPos = CheckHitWithFloor(player, FixedPos);

    //return FixedPos;
}


void Stage::AnalyzeWallAndFloor(const VECTOR& CheckPosition)
{
    // 壁ポリゴンと床ポリゴンの数を初期化する
    wallNum = 0;
    floorNum = 0;

    // 検出されたポリゴンの数だけ繰り返し
    for (int i = 0; i < hitDim.HitNum; i++)
    {
        // ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
        if (hitDim.Dim[i].Normal.y < 0.000001f && hitDim.Dim[i].Normal.y > -0.000001f)
        {
            // 壁ポリゴンと判断された場合でも、プレイヤーのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
            if (hitDim.Dim[i].Position[0].y > CheckPosition.y + 1.0f ||
                hitDim.Dim[i].Position[1].y > CheckPosition.y + 1.0f ||
                hitDim.Dim[i].Position[2].y > CheckPosition.y + 1.0f)
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

VECTOR Stage::CheckHitWithWall(Player& player, const VECTOR& CheckPosition)
{
    VECTOR FixedPos = CheckPosition;

    // 壁の数が無かったら早期リターン
    if (wallNum == 0)
    {
        return FixedPos;
    }

    // 壁からの押し出し処理を試みる最大数だけ繰り返し
    for (int k = 0; k < HitTryNum; k++)
    {
        // 当たる可能性のある壁ポリゴンを全て見る
        bool isHitWall = false;
        for (int i = 0; i < wallNum; i++)
        {
            // i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
            auto Poly = wall[i];

            // プレイヤーと当たっているなら
            if (HitCheck_Capsule_Triangle(FixedPos, VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), HitWidth, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
            {
                // 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
                // 移動後の位置を更新（移動後の場所を補正）
                FixedPos = VAdd(FixedPos, VScale(Poly->Normal, HitSlideLength));

                // 移動した壁ポリゴンと接触しているかどうかを判定
                for (int j = 0; j < wallNum; j++)
                {
                    // 当たっていたらループを抜ける
                    Poly = wall[j];
                    if (HitCheck_Capsule_Triangle(FixedPos, VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), HitWidth, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
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

    return FixedPos;
}


VECTOR Stage::CheckHitWithFloor(Player& player, const VECTOR& CheckPosition)
{
    VECTOR FixedPos = CheckPosition;

    // 床の数が無かったら早期リターン
    if (floorNum == 0)
    {
        return FixedPos;
    }

    // 当たったかどうかのフラグを初期化
    bool IsHitFloor = false;

    // ジャンプ中且つ上昇中の場合は処理を分岐
    if (player.GetState() == Player::State::Jump
        && player.GetJumpPower() > 0.0f)
    {
        // 天井に頭をぶつける処理を行う
        // 一番低い天井にぶつける為の判定用変数を初期化
        float MinY = 0.0f;

        // 床ポリゴンの数だけ繰り返し
        for (int i = 0; i < floorNum; i++)
        {
            // i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
            auto Poly = floor[i];

            // 足先から頭の高さまでの間でポリゴンと接触しているかどうかを判定
            HITRESULT_LINE LineRes;					// 線分とポリゴンとの当たり判定の結果を代入する構造体
            LineRes = HitCheck_Line_Triangle(FixedPos, VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

            // 接触していなかったら何もしない
            if (LineRes.HitFlag == TRUE)
            {
                // 既にポリゴンに当たっていて、且つ今まで検出した天井ポリゴンより高い場合は何もしない
                if (!(IsHitFloor == true && MinY < LineRes.Position.y))
                {
                    // ポリゴンに当たったフラグを立てる
                    IsHitFloor = true;

                    // 接触したＹ座標を保存する
                    MinY = LineRes.Position.y;
                }
            }
        }

        // 接触したポリゴンがあれば
        if (IsHitFloor == true)
        {
            // 接触した場合はプレイヤーのＹ座標を接触座標を元に更新
            FixedPos.y = MinY - HitHeight;
            player.OnHitRoof();
        }
    }
    else
    {
        // 下降中かジャンプ中ではない場合の処理
        // 一番高い床ポリゴンにぶつける為の判定用変数を初期化
        float MaxY = 0.0f;

        // 床ポリゴンの数だけ繰り返し
        for (int i = 0; i < floorNum; i++)
        {
            // i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
            auto Poly = floor[i];

            // ジャンプ中かどうかで処理を分岐
            HITRESULT_LINE LineRes;					// 線分とポリゴンとの当たり判定の結果を代入する構造体
            if (player.GetState() == Player::State::Jump)
            {
                // ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
                LineRes = HitCheck_Line_Triangle(VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), VAdd(FixedPos, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
            }
            else
            {
                // 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
                LineRes = HitCheck_Line_Triangle(VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), VAdd(FixedPos, VGet(0.0f, -40.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
            }

            // 当たっていなかったら何もしない
            if (LineRes.HitFlag == TRUE)
            {
                // 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
                if (!(IsHitFloor == true && MaxY > LineRes.Position.y))
                {
                    // ポリゴンに当たったフラグを立てる
                    IsHitFloor = true;

                    // 接触したＹ座標を保存する
                    MaxY = LineRes.Position.y;
                }
            }
        }

        // 床ポリゴンに当たったかどうかで処理を分岐
        if (IsHitFloor == true)
        {
            // 当たった場合
            // 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
            FixedPos.y = MaxY;

            // 床に当たった時
            player.OnHitFloor();
        }
        else
        {
            // 床コリジョンに当たっていなくて且つジャンプ状態ではなかった場合は
            player.OnFall();
        }
    }

    return FixedPos;
}