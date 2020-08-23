#pragma once
#define FT_NUM 40       // 足場の配列サイズ
#define FT_TEX_NUM 6    // 足場の画像数
#define FT_TEX_HEIGHT 50 // 足場の画像サイズY
#define FT_TEX_WIDTH 600    // 足場の画像サイズX
#define FT_R 250        // 足場の半径
#define FT_ROOT_R 200   // 足場の根元の半径

struct Foot {
    enum Type {
        norm,
        pull,
        spike,
        ice,
        bounce
    };
    Type type;           // 足場の種類
    double dirL;         // 角度L
    double dirR;         // 角度R
    double drawPosY;    // 描画する座標Y
    double posY;    // 座標Y
    double height; // 足場の厚さ

    double posXR;   // 描画座標XR
    double posXL;   // 描画座標XL
    double posRootXR;  // 根元の描画座標XR
    double posRootXL;  // 根元の描画座用XL
    bool isFrontR;  // 後ろに回った足場の横の壁は消える
    bool isFrontL;  // 後ろに回った足場の横の壁は消える
    bool isThere; // 存在するかどうか
    
    double withDraw; // 乗っていた足場が引っこむ
    double time;
};

