
# pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.4.2
# define DEBUG

// シーンの名前
enum class State
{
    Title,

    Game,

    CharaSelect,

    BattleScene,

    GameOver,

    GameClear,
};

// ゲームデータ
struct GameData
{
    int SelectNum;  // キャラクターの種類
    uint32 highscore;
    uint32 dataLv;
    uint32 releasedChara;   // 解放されたキャラ
    uint32 selectedLv;  // 選択されたLv
};

// シーン管理クラス
using MyApp = SceneManager<State, GameData>;

// 画面サイズ
inline constexpr int WINDOW_WIDTH = 800;
inline constexpr int WINDOW_HEIGHT = 600;


// セーブデータファイル
extern String saveDataPath;

void LoadSaveData(GameData& gameData);

void WriteSaveData(const GameData& gameData);
