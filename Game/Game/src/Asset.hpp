#pragma once
#include <Siv3D.hpp>

void AssetRegister() {
    // Player
    TextureAsset::Register(U"player11", U"player/dangomushi/s1dangomushi.png");
    TextureAsset::Register(U"player12", U"player/dangomushi/s2dangomushi.png");
    TextureAsset::Register(U"player13", U"player/dangomushi/s1dangomushi.png");
    TextureAsset::Register(U"player14", U"player/dangomushi/s2dangomushi.png");
    TextureAsset::Register(U"player15", U"player/dangomushi/j2dangomushi.png");
    TextureAsset::Register(U"player16", U"player/dangomushi/j3dangomushi.png");
    TextureAsset::Register(U"player17", U"player/dangomushi/j2dangomushi.png");
    TextureAsset::Register(U"player18", U"player/dangomushi/j3dangomushi.png");
    
    
    TextureAsset::Register(U"player21", U"player/ebi/s1ebi.png");
    TextureAsset::Register(U"player22", U"player/ebi/s2ebi.png");
    TextureAsset::Register(U"player23", U"player/ebi/s1ebi.png");
    TextureAsset::Register(U"player24", U"player/ebi/s2ebi.png");
    TextureAsset::Register(U"player25", U"player/ebi/j1ebi.png");
    TextureAsset::Register(U"player26", U"player/ebi/j2ebi.png");
    TextureAsset::Register(U"player27", U"player/ebi/j3ebi.png");
    TextureAsset::Register(U"player28", U"player/ebi/j4ebi.png");
    
    
    TextureAsset::Register(U"player31", U"player/yadokari/s1yadokari.png");
    TextureAsset::Register(U"player32", U"player/yadokari/s2yadokari.png");
    TextureAsset::Register(U"player33", U"player/yadokari/s1yadokari.png");
    TextureAsset::Register(U"player34", U"player/yadokari/s2yadokari.png");
    TextureAsset::Register(U"player35", U"player/yadokari/j1yadokari.png");
    TextureAsset::Register(U"player36", U"player/yadokari/j2yadokari.png");
    TextureAsset::Register(U"player37", U"player/yadokari/j3yadokari.png");
    TextureAsset::Register(U"player38", U"player/yadokari/j4yadokari.png");
    
    
    TextureAsset::Register(U"player41", U"player/gdangomushi/s1gdangomushi.png");
    TextureAsset::Register(U"player42", U"player/gdangomushi/s2gdangomushi.png");
    TextureAsset::Register(U"player43", U"player/gdangomushi/s3gdangomushi.png");
    TextureAsset::Register(U"player44", U"player/gdangomushi/s4gdangomushi.png");
    TextureAsset::Register(U"player45", U"player/gdangomushi/j1gdangomushi.png");
    TextureAsset::Register(U"player46", U"player/gdangomushi/j2gdangomushi.png");
    TextureAsset::Register(U"player47", U"player/gdangomushi/j3gdangomushi.png");
    TextureAsset::Register(U"player48", U"player/gdangomushi/j4gdangomushi.png");
    
    
    TextureAsset::Register(U"player51", U"player/kurowassan/s1kurowassan.png");
    TextureAsset::Register(U"player52", U"player/kurowassan/s2kurowassan.png");
    TextureAsset::Register(U"player53", U"player/kurowassan/s1kurowassan.png");
    TextureAsset::Register(U"player54", U"player/kurowassan/s2kurowassan.png");
    TextureAsset::Register(U"player55", U"player/kurowassan/j1kurowassan.png");
    TextureAsset::Register(U"player56", U"player/kurowassan/j2kurowassan.png");
    TextureAsset::Register(U"player57", U"player/kurowassan/j3kurowassan.png");
    TextureAsset::Register(U"player58", U"player/kurowassan/j4kurowassan.png");

    // Boss
    for(int i = 1; i <= 10; i++) {
        TextureAsset::Register(U"boss" + Format(i), U"boss" + Format(i) + U".png");
    }

    // Audio
    AudioAsset::Register(U"Title", U"Sounds/BGM/Title.ogg");
    AudioAsset::Register(U"Main_BGM", U"Sounds/BGM/Main.ogg");
    AudioAsset::Register(U"GameOver_BGM", U"Sounds/BGM/GameOver_remake.ogg");

    AudioAsset::Register(U"beam", U"Sounds/SE/beam.mp3");
    AudioAsset::Register(U"beam-charge", U"Sounds/SE/beam-charge.mp3");
    AudioAsset::Register(U"chakuchi", U"Sounds/SE/chakuchi.mp3");
    AudioAsset::Register(U"damage", U"Sounds/SE/damage.mp3");
    AudioAsset::Register(U"kaiten", U"Sounds/SE/kaiten.mp3");
}
