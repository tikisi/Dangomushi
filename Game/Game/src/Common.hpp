
# pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

// シーンの名前
enum class State
{
    Title,

    Game,

    Battle,
};

// ゲームデータ
struct GameData
{
    // ハイスコア
    int32 highScore = 0;
};

// シーン管理クラス
using MyApp = SceneManager<State, GameData>;

// 画面サイズ
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
