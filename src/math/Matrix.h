#pragma once
#include "hook.h"
#include "Vector.h"
#include "rwplcore.h"

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
	void UpdateMatrix(RwMatrix *mat);

	void Reorthogonalize(void);

	CVector &GetPosition(void) { return pos; }
	CVector &GetRight(void) { return right; }
	CVector &GetForward(void) { return forward; }
	CVector &GetUp(void) { return up; }

	CMatrix& operator=(const CMatrix& b);

	static void InjectHooks(void);
};

CVector operator*(const CMatrix &a, const CVector &b);

class MyMatrix44 {
public:
	float rx, ry, rz, rw;
	float fx, fy, fz, fw;
	float ux, uy, uz, uw;
	float px, py, pz, pw;

	MyMatrix44() = default;
	MyMatrix44(float _rx, float _ry, float _rz, float _rw, float _fx, float _fy, float _fz, float _fw,
		float _ux, float _uy, float _uz, float _uw, float _px, float _py, float _pz, float _pw) {
		
		rx = _rx; ry = _ry; rz = _rz; rw = _rw;
		fx = _fx, fy = _fy, fz = _fz, fw = _fw;
		ux = _ux, uy = _uy, uz = _uz, uw = _uw;
		px = _px, py = _py, pz = _pz, pw = _pw;
	};

	void operator=(MyMatrix44 const &m);
	MyMatrix44 &operator*=(MyMatrix44 const &m);
};

MyMatrix44 operator*(const MyMatrix44 &m1, const MyMatrix44 &m2);