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

	int mouseX = 0;
	int mouseY = 0;

	float circlePositionX[3] = {120,360,600};
	float circlePositionY[3] = {250,350,500};

	unsigned int color[3] = { WHITE,WHITE,WHITE };

	FillMode kFillMode = kFillModeSolid;

	float a[3] = { 0.f,0.f,0.f };
	float b[3] = { 0.f,0.f,0.f };
	float c[3] = { 0.f,0.f,0.f };

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

		ImGui::DragInt("mouse.positionX", &mouseX, 0.01f);
		ImGui::DragInt("mouse.positionY", &mouseY, 0.01f);

		a[0] = circlePositionX[0] - float(mouseX);
		b[0] = circlePositionY[0] - float(mouseY);

		c[0] = sqrtf(powf(a[0], 2) + powf(b[0], 2));

		if (c[0] <= 100.0f) {
			color[0] = RED;
		}
		else {
			color[0] = WHITE;
		}

		a[1] = circlePositionX[1] - float(mouseX);
		b[1] = circlePositionY[1] - float(mouseY);

		c[1] = sqrtf(powf(a[1], 2) + powf(b[1], 2));

		if (c[1] <= 100.0f) {
			color[1] = RED;
		}
		else {
			color[1] = WHITE;
		}

		a[2] = circlePositionX[2] - float(mouseX);
		b[2] = circlePositionY[2] - float(mouseY);

		c[2] = sqrtf(powf(a[2], 2) + powf(b[2], 2));

		if (c[2] <= 100.0f) {
			color[2] = RED;
		}
		else {
			color[2] = WHITE;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
	
		for (int i = 0; i < 3; i++) {
			Novice::DrawEllipse((int)circlePositionX[i], (int)circlePositionY[i], 100, 100, 0.0f, color[i], kFillMode);
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