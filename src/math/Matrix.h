#pragma once
#include "patcher.h"
#include "Vector.h"

class CMatrix {
private:
	struct
	{
		float rx, ry, rz, rw;
		float fx, fy, fz, fw;
		float ux, uy, uz, uw;
		float px, py, pz, pw;
	};
public:
	void SetRotateXOnly(float angle);
	void SetRotateYOnly(float angle);
	void SetRotateZOnly(float angle);

	void SetRotateX(float angle);
	void SetRotateY(float angle);
	void SetRotateZ(float angle);
	void SetRotate(Vector3 const& rot); 

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Rotate(Vector3 const& rot);

	void Reorthogonalize(void);

	CVector &GetPosition(void) { return *(CVector*)&px; }
	CVector &GetRight(void) { return *(CVector*)&rx; }
	CVector &GetForward(void) { return *(CVector*)&fx; }
	CVector &GetUp(void) { return *(CVector*)&ux; }

	static void InjectHooks(void);
};

class MyMatrix44 {
public:
	struct
	{
		float rx, ry, rz, rw;
		float fx, fy, fz, fw;
		float ux, uy, uz, uw;
		float px, py, pz, pw;
	};

	void operator=(MyMatrix44 const &m);
	MyMatrix44 &operator*=(MyMatrix44 const &m);
};

MyMatrix44 operator*(const MyMatrix44 &m1, const MyMatrix44 &m2);