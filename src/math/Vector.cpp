#include <math.h>
#include <limits>

#include "hook.h"
#include "Vector.h"

CVector const &CVector::Zero = CVector(0.0f, 0.0f, 0.0f);

void CVector::InjectHooks(void) {
	using namespace memory::hook;

	inject_hook(0x414E10, &CVector::Normalize);
	inject_hook(0x414E70, &CVector::LimitDirection);
	inject_hook(0x414B70, (CVector(*)(CVector const &, CVector const &))&operator-);
	inject_hook(0x414BA0, (CVector(*)(Vector3 const &, CVector const &))&operator-);
	inject_hook(0x414C20, &calcNormalizingCoefficient);
}

CVector CrossProduct(const CVector &v1, const CVector &v2) {
	return CVector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

float calcNormalizingCoefficient(float f1, float lengthSquared) {
	float length = sqrtf(lengthSquared);

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

float CVector::Magnitude() {
	return sqrtf(x * x + y * y + z * z);
}

float CVector::MagnitudeSqr() {
	return x * x + y * y + z * z;
}

void CVector::Normalize() {
	float magnSqr = MagnitudeSqr();
	float coefficient = calcNormalizingCoefficient(1.0f, magnSqr);
	x *= coefficient;
	y *= coefficient;
	z *= coefficient;
}

void CVector::LimitDirection(CVector const& vec, float coefficient) {
	float magnitude = Magnitude();
	CVector oldDir = *this;
	oldDir.Normalize();

	float fProduct = DotProduct(oldDir, vec);
	if (coefficient > fProduct) {
		float scale = sqrtf(abs(1.0f - (coefficient * coefficient)));
		CVector newDir = vec * fProduct;
		CVector tmp = oldDir - newDir;
		tmp.Normalize();
		oldDir = vec * coefficient;
		newDir = tmp * scale;
		tmp = newDir + oldDir;
		tmp.Normalize();
		newDir = tmp * magnitude;
		*this = newDir;
	}
}

inline CVector operator-(CVector const &v1, CVector const &v2) {
	return CVector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline CVector operator-(Vector3 const &v1, CVector const &v2) {
	return CVector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline CVector operator+(CVector const &v1, CVector const &v2) {
	return CVector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline CVector operator*(CVector const &v, float coefficient) {
	return CVector(v.x * coefficient, v.y * coefficient, v.z * coefficient);
}

inline float DotProduct(const CVector &v1, const CVector &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}