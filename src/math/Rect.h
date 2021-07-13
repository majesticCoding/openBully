#pragma once
#include "Vector2D.h"

class CRect {
public:
	CRect() = default;
	CRect(float l, float t, float r, float b):
		left(l), bottom(b), right(r), top(t) {}

	float left;
	float bottom;
	float right;
	float top;

	void Add(float x, float y);

	CRect &operator+=(const CVector2D &vec);

	static void InjectHooks();
};