#pragma once
#include <Siv3D.hpp>

void AssetRegister() {
    // Player
    TextureAsset::Register(U"player11", U"asset/player/dangomushi/s1dangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player12", U"asset/player/dangomushi/s2dangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player13", U"asset/player/dangomushi/s1dangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player14", U"asset/player/dangomushi/s2dangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player15", U"asset/player/dangomushi/j2dangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player16", U"asset/player/dangomushi/j3dangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player17", U"asset/player/dangomushi/j2dangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player18", U"asset/player/dangomushi/j3dangomushi.png", AssetParameter::LoadImmediately());


    TextureAsset::Register(U"player21", U"asset/player/ebi/s1ebi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player22", U"asset/player/ebi/s2ebi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player23", U"asset/player/ebi/s1ebi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player24", U"asset/player/ebi/s2ebi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player25", U"asset/player/ebi/j1ebi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player26", U"asset/player/ebi/j2ebi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player27", U"asset/player/ebi/j3ebi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player28", U"asset/player/ebi/j4ebi.png", AssetParameter::LoadImmediately());


    TextureAsset::Register(U"player31", U"asset/player/yadokari/s1yadokari.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player32", U"asset/player/yadokari/s2yadokari.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player33", U"asset/player/yadokari/s1yadokari.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player34", U"asset/player/yadokari/s2yadokari.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player35", U"asset/player/yadokari/j1yadokari.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player36", U"asset/player/yadokari/j2yadokari.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player37", U"asset/player/yadokari/j3yadokari.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player38", U"asset/player/yadokari/j4yadokari.png", AssetParameter::LoadImmediately());


    TextureAsset::Register(U"player41", U"asset/player/gdangomushi/s1gdangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player42", U"asset/player/gdangomushi/s2gdangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player43", U"asset/player/gdangomushi/s3gdangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player44", U"asset/player/gdangomushi/s4gdangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player45", U"asset/player/gdangomushi/j1gdangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player46", U"asset/player/gdangomushi/j2gdangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player47", U"asset/player/gdangomushi/j3gdangomushi.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player48", U"asset/player/gdangomushi/j4gdangomushi.png", AssetParameter::LoadImmediately());


    TextureAsset::Register(U"player51", U"asset/player/kurowassan/s1kurowassan.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player52", U"asset/player/kurowassan/s2kurowassan.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player53", U"asset/player/kurowassan/s1kurowassan.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player54", U"asset/player/kurowassan/s2kurowassan.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player55", U"asset/player/kurowassan/j1kurowassan.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player56", U"asset/player/kurowassan/j2kurowassan.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player57", U"asset/player/kurowassan/j3kurowassan.png", AssetParameter::LoadImmediately());
    TextureAsset::Register(U"player58", U"asset/player/kurowassan/j4kurowassan.png", AssetParameter::LoadImmediately());

    // Boss
    for (int i = 1; i <= 10; i++) {
        TextureAsset::Register(U"boss" + Format(i), U"asset/boss/boss" + Format(i) + U".png", AssetParameter::LoadImmediately());
    }

    // Audio
    AudioAsset::Register(U"Title", U"asset/Sounds/BGM/Title.ogg", AssetParameter::LoadImmediately());
    AudioAsset::Register(U"Main_BGM", U"asset/Sounds/BGM/Main.ogg", AssetParameter::LoadImmediately());
    AudioAsset::Register(U"GameOver_BGM", U"asset/Sounds/BGM/GameOver_remake.ogg", AssetParameter::LoadImmediately());

    AudioAsset::Register(U"beam", U"asset/Sounds/SE/beam.mp3", AssetParameter::LoadImmediately());
    AudioAsset::Register(U"beam-charge", U"asset/Sounds/SE/beam-charge.mp3", AssetParameter::LoadImmediately());
    AudioAsset::Register(U"chakuchi", U"asset/Sounds/SE/chakuchi.mp3", AssetParameter::LoadImmediately());
    AudioAsset::Register(U"damage", U"asset/Sounds/SE/damage.mp3", AssetParameter::LoadImmediately());
    AudioAsset::Register(U"kaiten", U"asset/Sounds/SE/kaiten.mp3", AssetParameter::LoadImmediately());

    // Font
    FontAsset::Register(U"font25", 25);
    FontAsset::Register(U"font40", 40);
}