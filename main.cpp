#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

bool IsCollision(int mouseX, int mouseY, int centerX, int centerY,int width,int height) {

	Novice::GetMousePosition(&mouseX, &mouseY);

	float a = float(centerX - mouseX);
	float b = float(centerY - mouseY);

	float c = ((std::powf(a, 2)) / (std::powf((float)width, 2)) + (std::powf(b, 2)) / (std::powf((float)height, 2)));

	if (c <= 1.0f) {
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

	const int centerX = 400; // 楕円の中心X
	const int centerY = 400; // 楕円の中心Y
	const int width = 100;   // 楕円の幅
	const int height = 50;   // 楕円の高さ
	const int segments = 64; // 分割数

	unsigned int color = WHITE;

	const float deltaTheta = 2.0f * 3.14f / segments;

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		if (IsCollision(mouseX, mouseY, centerX, centerY,width,height)) {
			color = BLUE;
		}
		else {
			color = WHITE;
		}

		   // 各線を順に描画
		for (int i = 0; i < segments; ++i) {
			// 現在の角度と次の角度を計算
			float theta1 = i * deltaTheta;
			float theta2 = (i + 1) * deltaTheta;

			// 楕円の周上の2点を計算
			int x1 = centerX + static_cast<int>((width) * cosf(theta1));
			int y1 = centerY + static_cast<int>((height) * sinf(theta1));
			int x2 = centerX + static_cast<int>((width ) * cosf(theta2));
			int y2 = centerY + static_cast<int>((height) * sinf(theta2));

			// 点1と点2を線で結ぶ
			Novice::DrawLine(x1, y1, x2, y2, color); // 白色の線
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