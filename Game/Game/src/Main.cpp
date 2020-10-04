﻿//
// OpenSiv3D v0.4.3 ゲームテンプレート
//

//
// macOS では README.md と同じフォルダに
// include と lib をコピーしてください。
//

# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"
# include "GameOver.hpp"
# include "CharaSelect.h"
# include "Asset.hpp"
# include "BattleScene/BattleScene.hpp"

void Main()
{
    // （Esc キーで終了しないようにする場合はコメントを外す）
    //System::SetTerminationTriggers(UserAction::CloseButtonClicked);
    
    // タイトルを設定
    Window::SetTitle(U"ダンゴムシ");
    // 画面サイズを変更
    Window::Resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene::Resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // フレームレートを60に固定
    Graphics::SetTargetFrameRateHz(60);
    
    // シーンと遷移時の色を設定
    MyApp manager;
    manager
    .add<Title>(State::Title)
    .add<Game>(State::Game)
    .add<BattleScene>(State::BattleScene)
    .add<CharaSelect>(State::CharaSelect)
    .add<GameOver>(State::GameOver);

    
    AssetRegister();
    
    while (System::Update())
    {
        if (!manager.update())
        {
            break;
        }
    }
}

//
// = クロスプラットフォーム開発の注意 =
//
// Xcode でソースコードを保存すると UTF-8 形式 (BOM 無し) になります。
// MSVC で作業するときはソースコードを UTF-8 (BOM 付き) に直す必要があります。
//
//
// = アドバイス =
// macOS 10.15 Catalina の Xcode プロジェクトで、
// ビルドしたプログラムを起動するたびにファイルアクセス許可のダイアログが表示される場合、
// プロジェクトのフォルダを User/アプリケーション に移動させることで通常は表示されなくなります。
// 特別なファイルシステム関数の使用や、Web カメラ、マイク使用時のダイアログまでは消せません。
//
//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D ユーザコミュニティ Slack への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
