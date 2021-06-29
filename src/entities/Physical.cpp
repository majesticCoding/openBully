#include "Physical.h"
#include "Rect.h"

CPhysical::CPhysical() {
	XCALL(0x468E90);
}

CPhysical::~CPhysical() {
	XCALL(0x46A720);
}

// virtual methods
bool CPhysical::IsType(short type) {
	return type == GetCPhysical() || type == GetCEntity();
}

void CPhysical::Add() {
	XCALL(0x4691E0);
}

void CPhysical::Remove() {
	XCALL(0x46A770);
}

void CPhysical::GetBoundRect(CRect *out) {
	CVector vec;
	GetBoundCentre(vec);
	float radius = GetBoundRadius();

	out->left = vec.x - radius;
	out->top = vec.y - radius;
	out->right = vec.x + radius;
	out->bottom = vec.y + radius;
}

void CPhysical::ProcessControl() {
	XCALL(0x469B70);
}

void CPhysical::ProcessShift(bool arg0) {
	XCALL(0x46CB90);
}

bool CPhysical::GetUsesSimpleIntegration() {
	return false;
}

float CPhysical::GetGravityForce() {
	return 0.008f;
}

void CPhysical::ApplyGravity() {
	XCALL(0x46ABE0);
}

void CPhysical::ApplyMoveSpeed() {
	XCALL(0x4698B0);
}

void CPhysical::ApplyTurnSpeed() {
	XCALL(0x469DC0);
}

void CPhysical::SetOldMat(const CMatrix &mat) {
	;
}

void CPhysical::GetOldMat(CMatrix &out) {
	CMatrix *mat = GetMatrix();
	out = CMatrix(*mat);
}

bool CPhysical::ProcessEntityCollision(CMatrix &arg0, CEntity *arg1,
		CColPoint *arg2, int arg3) {
	XCALL(0x46A490);
}

// static
short CPhysical::GetCPhysical() {
	static short s_id = g_FakeRTTI_ID++;
	return s_id;
}