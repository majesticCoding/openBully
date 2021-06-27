#pragma once
#include "Vector2D.h"

class CRect {
public:
	float left;
	float bottom;
	float right;
	float top;

	void Add(float x, float y);

	CRect &operator+=(const CVector2D &vec);

	static void InjectHooks();
};