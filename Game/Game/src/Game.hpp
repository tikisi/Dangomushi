#pragma once
#include "Background.hpp"
#include "Common.hpp"
#include "Player.hpp"
#include "Foot.hpp"
#include "Item.hpp"
#include "Enemy.hpp"

constexpr int TW_NUM = 6;		// 塔の段の種類数
constexpr int TW_CENTER_X = 350;	// 塔の描画中心座標X
constexpr int TW_WIDTH = 400;	// 塔の段の横幅
constexpr int TW_HEIGHT = 40;	// 塔の段の高さ
constexpr int LV_NUM = 2;   // 足場の生成アルゴリズムの数

// ゲームシーン
class Game : public MyApp::Scene
{
private:
    // 背景
    Background back;
    Texture texture1;
    Texture texture2;
    Texture ground;
    Texture sunset;
    Texture earth;
    Texture white;
    
    // 塔
    Texture tower[TW_NUM];	// 塔の画像
    Texture tower1; //上段
    Texture tower2; // 下段
    int towerSelect = 0; // 塔の種類
    double towerDir = 0;
    int towerPosY;	// 塔の描画位置Yのずれ

    // プレイヤー
    Player player;

    Texture dango1;
    Texture dango2;
    Texture dango3;
    Texture dango4;
    Texture dango5;
    Texture dango;
    
    // 敵
    int texturetime = 0;
    RectF enemyrect;
    Texture crow1;
    Texture crow2;
    Texture crow;
    Texture crowcharge1;
    Texture crowcharge2;
    Texture crowcharge;
    Texture cubicRed;
    Texture cubicBlue;
    Texture cubic;
    Texture cubiccharge;

    // 足場
    Foot foots[FT_NUM];
    Texture footTextures[FT_TEX_NUM];
    double footWidth; // 足場の横幅
    int Lv;


    // アイテム
    Item items[FT_NUM];
    Enemy enemy;
    const Font font30;
public:

    Game(const InitData& init);
    ~Game() {
        ClearPrint();
    }

    void update() override;

    void draw() const override;
    
    void backUpdate();
    void backDraw() const;
    
    void towerUpdate();
    void towerDraw() const;

    void playerInit();
    void loadPlayer(int selectNum);
    void playerUpdate();
    void collisionY();
    void collisionX();
    void playerDraw() const;

    void footInit();
    void footUpdate();
    void footDrawBefore() const;
    void footDraw() const;

    void itemInit();
    void itemUpdate();
    void itemDrawBefore() const;
    void itemDraw() const;

    void enemyInit(bool type);
    void enemyUpdate();
    void enemyDraw() const;

    // キー入力による角度の回転
    double rotate(double arg);
    // 半径と角度から画面上のX座標を返す
    double calcPos(double arg, double r);
    bool isFront(double arg);
    Rect drawBox(double x1, double y1, double x2, double height) const {
        return Rect(x1, y1, x2 - x1, height);
    }

    // 足場の生成アルゴリズム
    void generateInit(const int Lv);        // 一番最初の生成時アルゴリズムを選択
    void switchGenerateFoot(const int Lv);            // 足場の生成アルゴリズムを選択
    void generateLv1Init();
    int generateLv1();        // 追加した足場を返す(ない場合は-1)
    void  generateLv2Init();
    int generateLv2();
    void generateLv3Init();
    int generateLv3();
    void generateLv4Init();
    int generateLv4();
    void generateLv5Init();
    int generateLv5();
    std::function<int (void)> generateFoot;
};
