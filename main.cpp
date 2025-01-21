#include <Novice.h>
#include "Enemy.h"
#include <math.h>

const char kWindowTitle[] = "LC1B_03_イトウカズイ_タイトル";

bool Enemy::isAlive_ = true;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	//自機
	Circle player{};
	player.pos = { 640.0f,600.0f };
	player.radius = { 30.0f,30.0f };
	player.angle = 0.0f;
	player.color = GREEN;
	player.shape = kFillModeSolid;
	float playerSpeed = 5.0f;
	//自機の弾
	Circle bullet[10]{};
	float bulletSpeed[10]{};
	bool isExist[10]{};
	for (int i = 0; i < 10; i++) {
		bullet[i].pos = {};
		bullet[i].radius = {20.0f,20.0f};
		bullet[i].angle = 0.0f;
		bullet[i].color = WHITE;
		bullet[i].shape = kFillModeSolid;
		bulletSpeed[i] = 10.0f;
		isExist[i] = false;
	}
	int bulletCoolTimeSet = 10;
	int bulletCoolTime = bulletCoolTimeSet;
	//敵
	Enemy* enemys[2];
	enemys[0] = new Enemy(640.0f, 240.0f, 20.0f, 5.0f);
	enemys[1] = new Enemy(640.0f, 480.0f, 20.0f, -5.0f);
	//当たり判定
	float a = {};
	float b = {};
	float distance = {};

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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

		//自機の操作
		if (keys[DIK_W]) {
			player.pos.y -= playerSpeed;
		}
		if (keys[DIK_S]) {
			player.pos.y += playerSpeed;
		}
		if (keys[DIK_A]) {
			player.pos.x -= playerSpeed;
		}
		if (keys[DIK_D]) {
			player.pos.x += playerSpeed;
		}
		//範囲制限Xr
		if (player.pos.x <= 0.0f + player.radius.x) {
			player.pos.x = 0.0f + player.radius.x;
		} else if (player.pos.x >= kWindowWidth - player.radius.x) {
			player.pos.x = kWindowWidth - player.radius.x;
		}
		//範囲制限Y
		if (player.pos.y <= 0.0f + player.radius.y) {
			player.pos.y = 0.0f + player.radius.y;
		} else if (player.pos.y >= kWindowHeight - player.radius.y) {
			player.pos.y = kWindowHeight - player.radius.y;
		}

		//弾の動き
		if (bulletCoolTime > 0) {
			bulletCoolTime--;
		}
		if (keys[DIK_SPACE]) {
			if (bulletCoolTime <= 0) {
				bulletCoolTime = bulletCoolTimeSet;
				for (int i = 0; i < 10; i++) {
					if (!isExist[i]) {
						isExist[i] = true;
						bullet[i].pos = player.pos;
						break;
					}
				}
			}
		}
		for (int i = 0; i < 10; i++) {
			if (isExist[i]) {
				bullet[i].pos.y -= bulletSpeed[i];
				if (bullet[i].pos.y <= 0) {
					isExist[i] = false;
				}
			}
		}

		//敵の動き
		for (int i = 0; i < 2; i++) {
			enemys[i]->Update();
		}

		//弾と敵の当たり判定
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 2; j++) {
				if (isExist[i] && Enemy::isAlive_) {
					a = bullet[i].pos.x - enemys[j]->enemy_.pos.x;
					b = bullet[i].pos.y - enemys[j]->enemy_.pos.y;
					distance = sqrtf(a * a + b * b);
					//当たっていたら
					if (distance <= bullet[i].radius.x + enemys[j]->enemy_.radius.x) {
						Enemy::isAlive_ = false;
					}
				}
			}
		}

		//リセット
		if (keys[DIK_R]) {
			Enemy::isAlive_ = true;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//弾の描画
		for (int i = 0; i < 10; i++) {
			if (isExist[i]) {
				Novice::DrawEllipse(
					static_cast<int>(bullet[i].pos.x), static_cast<int>(bullet[i].pos.y),
					static_cast<int>(bullet[i].radius.x), static_cast<int>(bullet[i].radius.y),
					bullet[i].angle, bullet[i].color, bullet[i].shape
				);
			}
		}

		//敵の描画
		for (int i = 0; i < 2; i++) {
			enemys[i]->Draw();
		}

		//自機の描画
		Novice::DrawEllipse(
			static_cast<int>(player.pos.x), static_cast<int>(player.pos.y),
			static_cast<int>(player.radius.x), static_cast<int>(player.radius.y),
			player.angle, player.color, player.shape
		);

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
