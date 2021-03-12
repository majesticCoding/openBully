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
	CVector(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	const CVector &operator*=(float coefficient) {
		x *= coefficient;
		y *= coefficient;
		z *= coefficient;
		return *this;
	}

	const CVector &operator/=(float coefficient) {
		x /= coefficient;
		y /= coefficient;
		z /= coefficient;
		return *this;
	}

	void Normalize(void);
	float Magnitude(void);
	float MagnitudeSqr(void);
	void LimitDirection(CVector const& dir, float coefficient);

	static void InjectHooks(void);
};

CVector CrossProduct(const CVector &v1, const CVector &v2);

CVector operator-(CVector const &v1, CVector const &v2);
CVector operator-(Vector3 const &v1, CVector const &v2);
CVector operator+(CVector const &v1, CVector const &v2);
CVector operator*(CVector const &v, float coefficient);

float DotProduct(const CVector &v1, const CVector &v2);
float calcNormalizingCoefficient(float f1, float lengthSquared);