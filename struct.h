#pragma once
#include "Novice.h"

//画面サイズ
int const kWindowWidth = 1280;
int const kWindowHeight = 720;

template <typename T>
struct Vector2 {
	T x;
	T y;
};

struct Circle {
	Vector2<float> pos;
	Vector2<float> radius;
	float angle;
	unsigned int color;
	FillMode shape;
};
