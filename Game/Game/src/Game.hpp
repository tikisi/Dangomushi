# pragma once
#include "Common.hpp"
#include "Player.hpp"
#include "Foot.hpp"

constexpr int TW_NUM = 6;		// 塔の段の種類数
constexpr int TW_CENTER_X = 350;	// 塔の描画中心座標X
constexpr int TW_WIDTH = 400;	// 塔の段の横幅
constexpr int TW_HEIGHT = 40;	// 塔の段の高さ

// ゲームシーン
class Game : public MyApp::Scene
{
private:
	// 塔
	Texture tower[TW_NUM];	// 塔の画像
	Texture tower1; //上段
	Texture tower2; // 下段
	double towerSelect = 0.3; // 塔の種類
	int towerPosY;	// 塔の描画位置Yのずれ

	// プレイヤー
	Player player;
	Texture j1dango;
	Texture j2dango;
	Texture j3dango;
	Texture s1dango;
	Texture s2dango;

	// 足場
	Foot foots[FT_NUM];
	Texture footTextures[FT_TEX_NUM];

public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;


	void towerUpdate();
	void towerDraw() const;

	void playerInit();
	void playerUpdate();
	void collisionY();
	void collisionX();
	void playerDraw() const;
	void playerDrawByDir(Texture texture, int x, int y, int orRight) const;

	void footInit();
	void footUpdate();
    void footDrawBefore() const;
	void footDraw() const;
	
	// キー入力による角度の回転
	double rotate(double arg);
	// 半径と角度から画面上のX座標を返す
	double calcPos(double arg, double r);
    bool isFront(double arg);
    Rect drawBox(double x1, double y1,double x2, double height) const {
        return Rect(x1, y1, x2-x1, height);
    }
};
