#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "imgui.h"

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

bool StartWave(char* keys, char* preKeys) {
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		return true;
	}
	return false;
}

float MoveWave(float wave[3]) { return wave[0] + wave[1] + wave[2]; }

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	float  PositionX = 0;
	float  PositionY = 360;
	float Radius = 50;

	float amplitube[3] = {0.0f,0.0f,0.0f};

	float theta = -1;

	bool isWave = false;
	

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

		if (StartWave(keys, preKeys)) {
			isWave = true;
		}

		if (isWave) {
			amplitube[0] = (4 / float(M_PI)) * sinf(theta);
			amplitube[1] = (4 / (3 * float(M_PI))) * sinf(3 * theta);
			amplitube[2] = (4 / (5 * float(M_PI))) * sinf(5 * theta);

			PositionX += 7.0f;
			PositionY =  360 + (MoveWave(amplitube)) * 120;

			theta += float(M_PI) / 45.0f;
		}

		ImGui::DragFloat("translateX", &PositionX, 0.01f);
		ImGui::DragFloat("translateY", &PositionY, 0.01f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse(int(PositionX), int(PositionY), int(Radius), int(Radius), 0.0f, WHITE, kFillModeSolid);
	
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