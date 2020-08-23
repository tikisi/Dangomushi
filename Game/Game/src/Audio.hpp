#pragma once
#include <Siv3D.hpp>

void AudioAssetRegister() {
    AudioAsset::Register(U"Title", U"Sounds/BGM/Title.ogg");
    AudioAsset::Register(U"Main_BGM", U"Sounds/BGM/Main.ogg");
    AudioAsset::Register(U"GameOver_BGM", U"Sounds/BGM/GameOver_remake.ogg");

    AudioAsset::Register(U"beam", U"Sounds/SE/beam.mp3");
    AudioAsset::Register(U"beam-charge", U"Sounds/SE/beam-charge.mp3");
    AudioAsset::Register(U"chakuchi", U"Sounds/SE/chakuchi.mp3");
    AudioAsset::Register(U"damage", U"Sounds/SE/damage.mp3");
    AudioAsset::Register(U"kaiten", U"Sounds/SE/kaiten.mp3");
}
