#include "Common.hpp"

String saveDataPath = U"data.bin";

void LoadSaveData(GameData& gameData) {
	BinaryReader reader(saveDataPath);

	// ファイルが開けなかったとき
	if (!reader) {
		gameData.dataLv = 1;
		gameData.highscore = 0;
		gameData.releasedChara = 0;
		return;
	}

	if (reader.read(gameData.dataLv) == false) {
		gameData.dataLv = 1;
	}
	if (reader.read(gameData.highscore) == false) {
		gameData.highscore = 0;
	}
	if (reader.read(gameData.releasedChara) == false) {
		gameData.releasedChara = 0;
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
