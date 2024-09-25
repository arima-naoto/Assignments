#include <Novice.h>
#define _USE_MATH_DEFINES
#include "math.h"

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

struct Vector2 {
	float x;
	float y;
};



void RotateCircle(float& theta, Vector2& position, const Vector2& circle, const Vector2& targetRadius) {

	theta += 1.0f / 60.0f * float(M_PI);

	position.x = circle.x + (targetRadius.x * cosf(theta));
	position.y = circle.y + (targetRadius.y * sinf(theta));

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	float theta = 0;

	Vector2 position = { 0,0 };
	Vector2 circlePos = { 400,400 };
	Vector2 targetRadius = { 200,200 };

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

		RotateCircle(theta, position, circlePos, targetRadius);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
	
		Novice::DrawEllipse((int)position.x, (int)position.y, 50, 50, theta, RED, kFillModeSolid);

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