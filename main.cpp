#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include <SafeDelete.h>


#include <player.h>
#include <WEnemy.h>
#include <BEnemy.h>
#include <collision.h>

const char kWindowTitle[] = "LC1A_10_キョウ_ゲンソ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	int windowX = 1280;
	int windowY = 720;
	Novice::Initialize(kWindowTitle, windowX, windowY);

	srand(static_cast<unsigned int>(time(nullptr)));

	Player* player = new Player();

	WEnemy* wEnemy = new WEnemy();

	BEnemy* bEnemy = new BEnemy();

	Collision* collision = new Collision();

	//シーン遷移変数
	bool isGameStart = false;
	bool isGameOver = false;
	bool gameTitle = true;

	//画像ハンドラー
	int tittleImage = Novice::LoadTexture("./Res/tittle.png");
	int tittleSelectImage = Novice::LoadTexture("./Res/tittle select layer.png");
	int gameStartImage = Novice::LoadTexture("./Res/GAMESTART.png");
	int exitGameImage = Novice::LoadTexture("./Res/exit game.png");
	int gameOverScene = Novice::LoadTexture("./Res/GameOverScene.png");

	//サウンドハンドラー
	int menuSelectSound = Novice::LoadAudio("./Res/select.wav");

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		int mouseX, mouseY;
		Novice::GetMousePosition(&mouseX, &mouseY);

		///-------------------///
		/// ↓更新処理ここから///
		///-------------------///

		/*---------------------------------

　　　　　　タイトルシーン

　　　　　---------------------------------*/
		if (gameTitle) {

			Novice::SetMouseCursorVisibility(1);

			Novice::DrawSprite(0, 0, tittleImage, 1, 1, 0.0f, 0xffffffff);
			Novice::DrawSprite(534, 550, gameStartImage, 1, 1, 0.0f, 0xffffffff);
			Novice::DrawSprite(534, 634, exitGameImage, 1, 1, 0.0f, 0xffffffff);

			if (mouseX > 445 && mouseX < 837) {
				if (mouseY > 535 && mouseY < 609) {
					Novice::DrawSprite(445, 535, tittleSelectImage, 1, 1, 0.0f, 0xffffffff);
					if (Novice::IsPressMouse(0)) {
						Novice::PlayAudio(menuSelectSound, false, 0.5f);
						isGameStart = true;
						gameTitle = false;
					}
				}

				if (mouseY > 619 && mouseY < 693) {
					Novice::DrawSprite(445, 619, tittleSelectImage, 1, 1, 0.0f, 0xffffffff);
					if (Novice::IsPressMouse(0)) {
						Novice::PlayAudio(menuSelectSound, false, 0.5f);

						break;
					}
				}

			}
		}

		/*---------------------------------

　　　　　　ゲームシーン

　　　　　---------------------------------*/
		if (!isGameOver && isGameStart) {

			Novice::SetMouseCursorVisibility(0);

			collision->Update(*player, *wEnemy, *bEnemy);

			player->Update(keys, preKeys, mouseX, mouseY, isGameOver);

			wEnemy->Update(*player);

			bEnemy->Update(*player);
		}


		/*---------------------------------

　　　　　　ゲームオーバーシーン

　　　　　---------------------------------*/
		if (isGameOver) {

			//Init
			player->Init();
			wEnemy->Init();
			bEnemy->Init();
			collision->Init();

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				isGameStart = false;
				gameTitle = true;
				isGameOver = false;
			}

			Novice::DrawSprite(0, 0, gameOverScene, 1, 1, 0.0f, 0xffffffff);
		}

		///-------------------///
		/// ↑更新処理ここまで///
		///-------------------///

		///-------------------///
		/// ↓描画処理ここから///
		///-------------------///

		if (!isGameOver && isGameStart) {
			player->BGDraw();

			player->Draw(mouseX, mouseY);

			wEnemy->Draw();

			bEnemy->Draw();
		}

		///-------------------///
		/// ↑描画処理ここまで///
		///-------------------///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	SafeDelete(player);
	SafeDelete(wEnemy);
	SafeDelete(bEnemy);
	SafeDelete(collision);

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
