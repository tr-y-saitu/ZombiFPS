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
    // デバッグ情報の初期化
    ClearDebugDataList();

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
    // 入力更新
    UpdateKeyState();

    // コンソール画面をクリア
    if (isKeyRelease)
    {
        isKeyRelease = false;

        // 新しくデバッグ情報を描画
        PrintDebugData();
    }
}

/// <summary>
/// 新しくデバッグ情報を描画する
/// </summary>
void DebugLogger::PrintDebugData()
{
    // 画面をクリア
    // MEMO:ウィンドウズに直接コンソール画面をクリアにする指示を出す
    //      なんか行けるらしい
    system("cls");

    // デバッグ情報を上書き表示
    for (const auto& data : debugDataList)
    {
        // デバッグ情報の出力
        std::cout << " | Type: "    << data->dataType
                  << " | Name: "    << data->objectName
                  << " | Float: "   << data->floatData
                  << " | Vector: "  << "(" << data->vector.x << "," << data->vector.y << "," << data->vector.z << ") "
                  << std::endl;
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
    // 現在のキー状態を取得
    int keyState = CheckHitKey(KEY_INPUT_E);

    // キーが押されていない状態から押された状態に変わった場合
    if (!isKeyOn && keyState)
    {
        isKeyOn = true;
        isKeyRelease = false;
    }
    // キーが押されていた状態から離された場合
    else if (isKeyOn && !keyState)
    {
        isKeyOn = false;
        isKeyRelease = true;
    }
}
