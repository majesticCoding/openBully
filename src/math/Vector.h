#pragma once
#include "patcher.h"

typedef struct RwV3d {
	float x;
	float y;
	float z;
} Vector3;

class CVector : public RwV3d {
public:
	CVector(void) {}
	CVector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Normalize(void);
	void LimitDirection(CVector const& dir, float coefficient);

	static void InjectHooks(void);
};

CVector CrossProduct(const CVector &v1, const CVector &v2);

CVector operator-(CVector const &v1, CVector const &v2);

float calcNormalizingCoefficient(float f1, float lengthSquared);