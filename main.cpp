#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int mouseX = 0;
	int mouseY = 0;

	float positionX = 400;
	float positionY = 400;

	int radius = 20;

	float theta = 0;

	int isAdvent = FALSE;


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

		if (!isAdvent) {
			Novice::GetMousePosition(&mouseX, &mouseY);
		}
		if (Novice::IsTriggerMouse(0)) {
			isAdvent = TRUE;
		}

		if (isAdvent) {

			theta -= 1.0f / 60.0f * float(M_PI);

			positionX = mouseX - (200 * cosf(theta));
			positionY = mouseY + (200 * sinf(theta));

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
	

		Novice::DrawEllipse((int)positionX, (int)positionY, radius, radius, theta, WHITE, kFillModeSolid);

		if (isAdvent) {
			Novice::DrawEllipse(mouseX, mouseY, 10, 10, 0.0f, RED, kFillModeSolid);
		}

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