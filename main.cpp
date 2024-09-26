#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "imgui.h"

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

    struct Vector2 {//構造体Vector2を使用する

		float x;//単精度浮動小数点型xを宣言する
		float y;//単精度浮動小数点型yを宣言する

	};

	Vector2 position = { 300,300 };//positionでxとyを初期化する

	float t = 0.01f;//単精度浮動小数点型tを0.01fで初期化する

	int mouseX = 0;
	int mouseY = 0;

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

		Novice::GetMousePosition(&mouseX, &mouseY);

		float dx = mouseX - position.x;
		float dy = mouseY - position.y;

		float distance = sqrtf(powf(dx, 2) + powf(dy, 2));

		float speed = t * (distance / 20.0f);
		if (speed > 2.f) { speed = 2.f; }

		position.x = (1.0f - speed) * position.x + speed * mouseX;
		position.y = (1.0f - speed) * position.y + speed * mouseY;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse(int(position.x), int(position.y), 30, 30, 0.0f, RED, kFillModeSolid);

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