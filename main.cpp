#include <Novice.h>
#include <math.h>

#include <imgui.h>

#define p_vi 3.14f;

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

struct Vector2 {
	float x;
	float y;
};

struct Player {
	Vector2 pos;
	float newPosY;
	float speed;
	float radius;
	unsigned int color;
};

struct FireBar {
	Vector2 pos;
	unsigned int color;
};

struct Circle {
	Vector2 pos;
	float newPosY;
	unsigned int color;
};

void Move(Player& player,char *keys) {

	if (keys[DIK_RIGHT]) {
		player.pos.x += player.speed;
	}

	if (keys[DIK_LEFT]) {
		player.pos.x -= player.speed;
	}

	if (keys[DIK_UP]) {
		player.pos.y += player.speed;
	}

	if (keys[DIK_DOWN]) {
		player.pos.y -= player.speed;
	}
}

bool IsCollision(Player &player,Circle circle[5]) {

	for (int i = 0; i < 5; i++) {

		float dx = circle[i].pos.x - player.pos.x;
		float dy = circle[i].pos.y - player.pos.y;

		float distance = sqrtf(powf(dx, 2) + powf(dy, 2));

		if (distance < 30 + 50) {
			return true;
			break;
		}
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

	Player player = {
		.pos = { 200,50 },
		.speed = { 5 },
		.radius = { 50 },
		.color = WHITE
	};

	FireBar fireBar = {
		.pos{600,200},
		.color = RED
	};

	const int Max = 5;

	Circle circle[Max];
	for (int i = 0; i < Max; i++) {
		circle[i].pos = { 0,0 };
		circle[i].color = RED;
	}

	float kRadius = 30;

	float theta = 0.0f;

	bool isFireBar = false;

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

		Move(player, keys);

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			isFireBar = true;
		}

		if (isFireBar) {
			theta += 1.0f / 90.0f * p_vi;
		}

		for (int i = 0; i < Max; i++) {
			float localX = 2.0f * kRadius * i;
			circle[i].pos.x = localX * cosf(theta) + fireBar.pos.x;
			circle[i].pos.y = localX * sinf(theta) + fireBar.pos.y;
		}

		if (IsCollision(player, circle)) {
			player.color = BLUE;
		}
		else {
			player.color = WHITE;
		}

		for (int i = 0; i < Max; i++) {
			circle[i].newPosY = (circle[i].pos.y - 500) * -1;
		}

		player.newPosY = (player.pos.y - 500) * -1;

		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int i = 0; i < Max;i++) {
			Novice::DrawEllipse((int)circle[i].pos.x, (int)circle[i].newPosY, (int)kRadius, (int)kRadius, theta, circle[i].color, kFillModeSolid);
		}

		Novice::DrawEllipse((int)player.pos.x, (int)player.newPosY, (int)player.radius, (int)player.radius, 0.0f, player.color, kFillModeSolid);

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