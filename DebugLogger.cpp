#include "DebugLogger.h"

// 初期化
DebugLogger* DebugLogger::debugLogger = nullptr;
vector<DebugLogger::DebugPrintData*> DebugLogger::debugDataList;
bool DebugLogger::isKeyOn;
bool DebugLogger::isKeyRelease;
bool DebugLogger::isPreviousKeyOn;

/// <summary>
/// コンストラクタ
/// </summary>
DebugLogger::DebugLogger()
{
    // デバッグ用コンソール呼び出し
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);  // 標準出力をコンソールにリダイレクト
    freopen_s(&file, "CONIN$", "r", stdin);    // 標準入力をコンソールにリダイレクト

    // デバッグコンソールがアクティブウィンドウになるので
    // ゲーム本体のウィンドウをアクティブにする
    SetForegroundWindow(GetMainWindowHandle());

    isKeyOn = false;
    isKeyRelease = false;
    isPreviousKeyOn = false;
}

/// <summary>
/// デストラクタ
/// </summary>
DebugLogger::~DebugLogger()
{
    //コンソール解放
    FreeConsole();
}

/// <summary>
/// インスタンスの作成
/// </summary>
void DebugLogger::CreateInstance()
{
    // まだインスタンス化されていないなら作成
    if (debugLogger == nullptr)
    {
        debugLogger = new DebugLogger();
    }
}

/// <summary>
/// インスタンスのポインタを渡す
/// </summary>
/// <returns></returns>
DebugLogger* DebugLogger::GetInstance()
{
    return debugLogger;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void DebugLogger::DeleteInstance()
{
    delete(debugLogger);
}

/// <summary>
/// デバッグ表示リストに登録する
/// </summary>
/// <param name="data">登録するデータ</param>
void DebugLogger::RegisterDebugData(DebugPrintData* data)
{
    // データリストに追加
    debugDataList.push_back(data);
}

/// <summary>
/// 更新
/// </summary>
void DebugLogger::Update()
{
    UpdateKeyState();

    // コンソール画面をクリア
    if (isKeyRelease)
    {
        isKeyRelease = false;

        // デバッグ情報を上書き表示
        for (const auto& info : debugDataList)
        {
            // デバッグ情報の出力
            std::cout << "Object: " << info->objectName
                << " | Type: " << info->dataType
                << " | Vector: (" << info->vector.x << ", "
                << info->vector.y << ", " << info->vector.z
                << ") | Float: " << info->floatData << std::endl;
        }

        // デバッグ情報を初期化
        ClearDebugDataList();
    }

}

/// <summary>
/// デバッグ情報リストをクリアにする
/// </summary>
void DebugLogger::ClearDebugDataList()
{
    debugDataList.clear();
}

/// <summary>
/// 入力更新
/// </summary>
void DebugLogger::UpdateKeyState()
{
    // キー入力すでにされている場合
    if (isKeyOn)
    {
        if (!CheckHitKey(KEY_INPUT_E))
        {
            isKeyOn = false;          // キーが入力されていない
            isKeyRelease = true;      // キーが離れた
        }
    }
    else if (!isPreviousKeyOn && CheckHitKey(KEY_INPUT_E))
    {
        // キーは長押しされていない && 前フレームで入力なし && キーが押された
        isKeyRelease = false;   // キーは離れていない
        isKeyOn = true;         // キーが押された
    }

    // キー入力されたら
    if (CheckHitKey(KEY_INPUT_E))
    {
        isPreviousKeyOn = true;   // このフレームではキーが押された
    }
    else
    {
        isPreviousKeyOn = false;  // このフレームでキーは押されなかった
    }
}
