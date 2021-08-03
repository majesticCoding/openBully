#pragma once
#include "math.h"
#include "rwcore.h"

struct Vector3 : public RwV3d {
	float w;
};

class CVector : public RwV3d {
public:
	CVector() { x = 0.f; y = 0.f; z = 0.f; }
	CVector(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	CVector(RwV3d vec) { x = vec.x; y = vec.y; z = vec.z; }

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

	CVector &operator+=(const CVector &b) {
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	CVector &operator-=(const CVector &b) {
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}

	static CVector const &Zero;

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