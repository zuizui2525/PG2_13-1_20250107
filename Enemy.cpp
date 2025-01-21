#include "Enemy.h"
#include "struct.h"

Enemy::Enemy(float posX, float posY, float radius, float speed) {
	enemy_.pos = { posX,posY };
	enemy_.radius = { radius,radius };
	enemy_.angle = 0.0f;
	enemy_.color = RED;
	enemy_.shape = kFillModeSolid;
	speed_ = speed;
}

Enemy::~Enemy() {
}

void Enemy::Update() {
	if (Enemy::isAlive_) {
		//速度を加算
		enemy_.pos.x += speed_;
		//行動範囲制限(反射)
		if (enemy_.pos.x - enemy_.radius.x <= 0.0f || enemy_.pos.x + enemy_.radius.x >= kWindowWidth) {
			speed_ *= -1.0f;
		}
	}
}

void Enemy::Draw() {
	if (Enemy::isAlive_) {
		Novice::DrawEllipse(
			static_cast<int>(enemy_.pos.x), static_cast<int>(enemy_.pos.y),
			static_cast<int>(enemy_.radius.x), static_cast<int>(enemy_.radius.y),
			enemy_.angle, enemy_.color, enemy_.shape
		);
	}
}
