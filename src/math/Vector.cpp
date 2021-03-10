#include <math.h>
#include <limits>
#include "Vector.h"

void CVector::InjectHooks(void) {
	InjectHook(0x414E10, &CVector::Normalize, PATCH_JUMP);
	InjectHook(0x414B70, (CVector(*)(CVector const &, CVector const &))&operator-, PATCH_JUMP);
	InjectHook(0x414BA0, (CVector(*)(Vector3 const &, CVector const &))&operator-, PATCH_JUMP);
	InjectHook(0x414C20, &calcNormalizingCoefficient, PATCH_JUMP);
}

CVector CrossProduct(const CVector &v1, const CVector &v2) {
	return CVector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

float calcNormalizingCoefficient(float f1, float lengthSquared) {
	float length = sqrtf(abs(lengthSquared));

	if (length != 0.0f) {
		return f1 / length;
	}
	else {
		if (f1 < 0.0f)
			return FLT_MIN;
		else
			return FLT_MAX;
	}
}

void CVector::Normalize() {
	float lengthSquared = x * x + y * y + z * z;
	float coefficient = calcNormalizingCoefficient(1.0f, lengthSquared);
	x *= coefficient;
	y *= coefficient;
	z *= coefficient;
}

void CVector::LimitDirection(CVector const& dir, float coefficient) {
	float magnitude = sqrtf(fabsf(x * x + y * y + z * z));
}

CVector operator-(CVector const &v1, CVector const &v2) {
	return CVector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

CVector operator-(Vector3 const &v1, CVector const &v2) {
	return CVector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline CVector operator+(CVector const &v1, CVector const &v2) {
	return CVector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}