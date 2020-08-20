# pragma once
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

    // 足場
    Foot foots[FT_NUM];
    Texture footTextures[FT_TEX_NUM];
    int Lv;


    // アイテム
    Item items[FT_NUM];
    Enemy enemy;
    const Font font30;
public:

    Game(const InitData& init);

    void update() override;

    void draw() const override;


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

    void enemyInit();
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
    void generate();            // 足場の生成アルゴリズムを選択
    void generateInit();        // 足場の初期生成アルゴリズムを選択
    void generateLv1Init();
    void generateLv1();
    void generateLv2Init() {};
    void generateLv2() {};
};
