
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
    uint32 SelectNum;  // 選択したキャラクター
    int death = 0;

    uint32 highscore;
    uint32 dataLv;
    uint32 releasedChara;   // 解放されたキャラ
    uint32 selectedLv;  // 選択されたLv
    GameData() {
        SelectNum = 1;
        death = 0;
        dataLv = 1;
        highscore = 0;
        releasedChara = 0;
    }
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

// ステージ選択Window用
namespace StageSelect {
    inline constexpr Point windowSize = Point(640, 480);
    inline constexpr Point btnSize = Point(150, 25);
    inline constexpr Point charaBoxSize = Point(60 ,60);
    void DrawWindow(const GameData& gameData, const uint32 selecter);
}
