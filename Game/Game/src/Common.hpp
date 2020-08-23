
# pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

// シーンの名前
enum class State
{
    Title,

    Game,

	CharaSelect,

    Battle,
    
    GameOver,
};

// ゲームデータ
struct GameData
{
    int SelectNum;  // キャラクターの種類
    double highscore = 0;
    int dataLv = 1;
};

// シーン管理クラス
using MyApp = SceneManager<State, GameData>;

// 画面サイズ
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
