#pragma once
#include "patcher.h"
#include "Vector.h"

struct RwMatrix {
	float rightx, forwardx, upx;
	float righty, forwardy, upy;
	float rightz, forwardz, upz;
	RwV3d pos;
};

class CMatrix {
private:
	float rx, ry, rz, rw;
	float fx, fy, fz, fw;
	float ux, uy, uz, uw;
	float px, py, pz, pw;
	RwMatrix *m_pAttachMatrix;

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

	void UpdateRw();
	void SetUnity();
	void ResetOrientation();
	void UpdateRwMatrix(RwMatrix *mat);

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