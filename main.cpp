#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int posX = 640;
	int posY = 400;
	int speedX = 5;
	int speedY = 5;

	float targetPosX = 400;
	float targetPosY = 400;

	unsigned int color = RED;
	float a = 0;
	float b = 0;
	float distance = 0;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
	
#pragma region プレイヤーの移動処理

		if (keys[DIK_D])
		{

			posX += speedX;

		}

		if (keys[DIK_A])
		{

			posX -= speedX;

		}

		if (keys[DIK_W])
		{

			posY -= speedY;

		}

		if (keys[DIK_S])
		{

			posY += speedY;

		}

#pragma endregion

		a = targetPosX - (float)posX;
		b = targetPosY - (float)posY;
		distance = sqrtf(powf(a, 2) + powf(b, 2));
		//衝突判定
		if (distance <= 100 - 50) {
			color = BLUE;

		}
		else {
			color = RED;
		}



		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse((int)targetPosX, (int)targetPosY, 100, 100, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawEllipse(posX, posY, 50, 50, 0.0f, color, kFillModeSolid);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}