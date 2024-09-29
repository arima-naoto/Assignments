#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include <imgui.h>

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

struct Vector2 {
	float x;
	float y;
};

struct Player {
	Vector2 pos;
	float radius;
	float speed;
	unsigned int color;
	FillMode fillmode;
};

struct Dossun {
	Vector2 pos;
	float speed;
	float radius;
	unsigned int color;
	bool isFall;
	FillMode fillmode;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player player = {
		.pos{200,0},
		.radius{10},
		.speed{4},
		.color = WHITE,
		.fillmode{kFillModeSolid}
	};

	Dossun dossun = {
		.pos{800,400},
		.speed{20},
		.radius{100},
		.color{WHITE},
		.isFall{false},
		.fillmode{kFillModeSolid}
	};

	bool isFall = false;

	float newPosY[2] = { 0,0 };

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

		if (keys[DIK_RIGHT]) {
			player.pos.x += player.speed;
		}

		float distance = fabsf(dossun.pos.x - player.pos.x);

		if (!isFall && distance < 100.0f) {
			isFall = true;
		}

		if (isFall) {
			dossun.pos.y -= dossun.speed;
		}

		newPosY[0] = (player.pos.y - 500) * -1;
		newPosY[1] = (dossun.pos.y - 500) * -1;

		ImGui::DragFloat("player.translate", &distance, 0.01f);
		ImGui::DragFloat2("player.translate", &player.pos.x, 0.01f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse((int)player.pos.x, (int)newPosY[0], (int)player.radius, (int)player.radius, 0.0f, player.color, player.fillmode);
		Novice::DrawBox((int)dossun.pos.x, (int)newPosY[1], (int)dossun.radius, (int)dossun.radius, 0.0f, dossun.color, dossun.fillmode);

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