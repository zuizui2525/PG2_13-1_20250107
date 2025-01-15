#pragma once
#include "struct.h"

class Enemy {
public:
	Circle enemy_;
	float speed_;
	static bool isAlive_;
	Enemy(float posX,float posY,float radius,float speed);
	~Enemy();
	void Update();
	void Draw();
};

