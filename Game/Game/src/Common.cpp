﻿#include "Common.hpp"

// セーブデータファイル
String saveDataPath = U"data.bin";

void LoadSaveData(GameData& gameData) {
    BinaryReader reader(saveDataPath);

    // ファイルが開けなかったとき
    if (!reader) {
        gameData.dataLv = 1;
        gameData.highscore = 0;
        gameData.releasedChara = 3;
        return;
    }

    if (reader.read(gameData.dataLv) == false) {
        gameData.dataLv = 1;
    }
    if (reader.read(gameData.highscore) == false) {
        gameData.highscore = 0;
    }
    if (reader.read(gameData.releasedChara) == false) {
        gameData.releasedChara = 3;
    }
}

void WriteSaveData(const GameData& gameData) {
    BinaryWriter writer(saveDataPath);

    if (!writer) {
        throw Error(saveDataPath + U" が開けません");
    }

    writer.write(gameData.dataLv);
    writer.write(gameData.highscore);
    writer.write(gameData.releasedChara);
}

namespace StageSelect {
    void DrawWindow(const GameData& gameData, const uint32 selecter) {
        Point center = Scene::Center();
        // 背景
        Rect(Arg::center(center), windowSize).draw(ColorF(0, 0, 0, 0.85))
            .drawFrame(0, 3, Palette::Lightyellow);
        // ハイスコア
        FontAsset(U"font40")(U"ハイスコア " + Format(gameData.highscore)).drawAt(center - Point(0, windowSize.y / 2 - 30 - 20), Palette::White);
    
        // 選択中のキャラ
        Point charBoxPos = center - Point(-260, windowSize.y / 2 - 30 - 20);
        Rect(Arg::center(charBoxPos), charaBoxSize).drawFrame(0, 3, Palette::White);
        TextureAsset(U"player" + Format(gameData.SelectNum) + Format((int)Periodic::Square0_1(0.3s) + 1)).drawAt(charBoxPos);

        // Line
        Point startPos = center - Point(0, windowSize.y / 2) + Point(0, 100);
        uint32 lineWidth = windowSize.x / 2 - 35;
        Line(startPos - Point(lineWidth, 0), startPos + Point(lineWidth, 0)).draw(LineStyle::SquareDot, 4, Palette::White);

        startPos += Point(0, 22);
        FontAsset(U"font25")(U"開始するステージを選んでください").drawAt(startPos, Palette::White);

        // ステージ
        startPos += Point(0, 25 + 20);
        Point delta(0, 25 + 20);

        int Lv = (int)gameData.dataLv;
        for (int i = 1; i <= Lv; i++) {
            if (i != 7)
                FontAsset(U"font25")(U"Level " + Format(i)).drawAt(startPos + (i - 1) * delta, Palette::White);
            else
                FontAsset(U"font25")(U"BossBattle").drawAt(startPos + (i - 1) * delta, Palette::White);
        }
        // カーソル
        Rect(Arg::center(startPos + (int)(selecter - 1) * delta), btnSize).drawFrame(0, 2, Palette::Yellow);
    }
}
