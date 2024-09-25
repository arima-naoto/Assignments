#include <Novice.h>
#define _USE_MATH_DEFINES
#include "math.h"
#include "imgui.h"

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

const int Max = 50;

struct Vector2 {
	float x;
	float y;

	Vector2 operator+=(const Vector2& num) {
		x += num.x;
		y += num.y;
		return *this;
	}

};

struct Particle {
	Vector2 pos;
	float radius;
	unsigned int color;
	bool isShot;
};

void RotateCircle(float& theta, Vector2& position, const Vector2& circle, Vector2& targetRadius) {

	theta += 1.0f / 60.0f * float(M_PI);

	targetRadius += Vector2(0.05f, 0.05f);

	position.x = circle.x + (targetRadius.x * cosf(theta));
	position.y = circle.y + (targetRadius.y * sinf(theta));

}

void GenetateParticle(int &shotTimer,Particle particle[Max], const Vector2& position) {

	if (++shotTimer >= 8) {
		shotTimer = 0;
		for (int i = 0; i < Max; i++) {
			if (!particle[i].isShot) {
				particle[i].isShot = true;
				particle[i].pos.x = position.x;
				particle[i].pos.y = position.y;
				particle[i].color = 0xFFFFFF96;
				break;
			}
		}
	}

	for (int i = 0; i < Max; i++) {
		if (particle[i].isShot) {
			particle[i].color -= 0x0000002;

			if (particle[i].color <= 0xFFFFFF00) {
				particle[i].isShot = false;
			}
		}
	}

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
	Vector2 targetRadius = { 0,0 };

	Particle particle[Max];
	for (int i = 0; i < Max; i++) {
		particle[i].pos = { 0,-40 };
		particle[i].radius = { 20 };
		particle[i].color = 0xFFFFFF96;
		particle[i].isShot = false;
	}

	int shotTimer = 0;

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

		GenetateParticle(shotTimer, particle, position);

		ImGui::DragFloat2("targetRotate", &targetRadius.x, 0.01f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int i = 0; i < Max; i++) {
			Novice::DrawEllipse((int)particle[i].pos.x, (int)particle[i].pos.y, 20, 20, 0.0f, particle[i].color, kFillModeSolid);
		}

		Novice::DrawEllipse((int)position.x, (int)position.y, 20, 20, theta, RED, kFillModeSolid);

		

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