#include <Novice.h>
#define _USE_MATH_DEFINES
#include "math.h"

#include "imgui.h"

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

bool isCollision(int mouseX, int mouseY, float positionX, float positionY,int radius) {
	
	Novice::GetMousePosition(&mouseX, &mouseY);

	float a = positionX - (float)mouseX;
	float b = positionY - (float)mouseY;

	float c = sqrtf(powf(a, 2) + powf(b, 2));

	if (c <= (float)radius) {
		return true;
	}

	return false;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int timer = 0;

	float positionX = 500;
	float positionY = 500;
	int radius = 30;
	float theta = 0;
	unsigned int color = WHITE;

	FillMode fillMode = kFillModeSolid;

	bool inverse = false;

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

		if (++timer >= 60) {
			inverse = true;

			if (timer >= 120) {
				inverse = false;
				timer = 0;
			}

		}

		if (!inverse) {
			theta -= (1.0f / 394.0f) * float(M_PI);
		}
		else {
			theta += (1.0f / 394.0f) * float(M_PI);
		}

		float newPositionX = positionX * cosf(theta) - positionY * sinf(theta);
		float newPositionY = positionY * cosf(theta) + positionX * sinf(theta);

		if (isCollision(mouseX, mouseY, newPositionX, newPositionY, radius)) {
			color = RED;
		}
		else {
			color = WHITE;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
	
		Novice::DrawEllipse(int(newPositionX), int(newPositionY), radius, radius, theta, color, fillMode);

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