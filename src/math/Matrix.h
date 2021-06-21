#pragma once
#include "hook.h"
#include "Vector.h"

struct RwMatrix {
	float rightx, forwardx, upx;
	float righty, forwardy, upy;
	float rightz, forwardz, upz;
	RwV3d pos;
};

class CMatrix {
	HOOKED_CONSTRUCTOR_CLASS(CMatrix)
public:
	CMatrix() = default;
	CMatrix(const CMatrix &m);

	CVector right;
	float rw;
	CVector forward;
	float fw;
	CVector up;
	float uw;
	CVector pos;
	float pw;
	
	RwMatrix *m_pAttachMatrix;

	void SetRotateXOnly(float angle);
	void SetRotateYOnly(float angle);
	void SetRotateZOnly(float angle);

	void SetRotateX(float angle);
	void SetRotateY(float angle);
	void SetRotateZ(float angle);
	void SetRotate(Vector3 const &rot);

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Rotate(Vector3 const &rot);

	void UpdateRw(void);
	void SetUnity(void);
	void ResetOrientation(void);
	void UpdateRwMatrix(RwMatrix *mat);

	void Reorthogonalize(void);

	CVector &GetPosition(void) { return pos; }
	CVector &GetRight(void) { return right; }
	CVector &GetForward(void) { return forward; }
	CVector &GetUp(void) { return up; }

	CMatrix& operator=(const CMatrix& b);

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