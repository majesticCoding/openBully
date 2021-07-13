#include "SplineInterpolater.h"
#include "Matrix.h"
#include "hook.h"

static const MyMatrix44 CatmullRomMatrix = MyMatrix44
(
	0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.0f, 0.5f, 0.0f,
	1.0f, -2.5f, 2.0f, -0.5f,
	-0.5f, 1.5f, -1.5f, 0.5f
);

void SplineInterpolater::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x412400, &CatmullRomCurve3);
}

CVector CatmullRomCurve3(CVector const *right, CVector const *forward, CVector const *up, CVector const *pos, float u) {
	MyMatrix44 tmpMat;
	tmpMat.rx = right->x;
	tmpMat.ry = right->y;
	tmpMat.rz = right->z;
	tmpMat.fx = forward->x;
	tmpMat.fy = forward->y;
	tmpMat.fz = forward->z;
	tmpMat.ux = up->x;
	tmpMat.uy = up->y;
	tmpMat.uz = up->z;
	tmpMat.px = pos->x;
	tmpMat.py = pos->y;
	tmpMat.pz = pos->z;

	MyMatrix44 newMat = CatmullRomMatrix;
	newMat *= tmpMat;

	tmpMat = MyMatrix44
	(
		1.0f, u, sqr(u), sqr(u) * u,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);

	MyMatrix44 geomMat = tmpMat;
	geomMat *= newMat;

	return CVector(geomMat.rx, geomMat.ry, geomMat.rz);
}

//C(t) = (1-t)^3*p0 + 3t*(1-t)^2*p1 + 3*t^2*(1-t)*p2 + t^3*p3
void CalculateSplinePoint(CVector& result, CVector right, CVector forward, CVector up, CVector pos, float u) {
	float t = sqr(u) * u;

	float fComponent1; 
	float fComponent2; 
	float fComponent3; 

	fComponent1 = sqr(1.0f - u) * (1.0f - u) / 6.0f;
	fComponent2 = (((t * 3.0f) - (sqr(u) * 6.0f)) + 4.0f) / 6.0f;
	fComponent3 = ((((u * 3.0f) + 1.0f) + (sqr(u) * 3.0f)) + (t * -3.0f)) / 6.0f;

	result.x = fComponent1 * right.x + fComponent2 * forward.x + fComponent3 * up.x + (t / 6.0f) * pos.x;
	result.y = fComponent1 * right.y + fComponent2 * forward.y + fComponent3 * up.y + (t / 6.0f) * pos.y;
	result.z = fComponent1 * right.z + fComponent2 * forward.z + fComponent3 * up.z + (t / 6.0f) * pos.z;
}

SplineInterpolater::SplineInterpolater(void) {
	m_pos = CVector::Zero;
	p1 = CVector::Zero;
	p2 = CVector::Zero;
	m_fAcceleration = 5.0f;
	m_fDeceleration = 5.0f;
	m_controlIndex = 0;
	m_fMaxSpeed = 30.0f;
	m_fSpeed = 0.0f;
	m_fUnk = 0.0f;
	m_nNumControlPoints = 0;

	//TODO: add the rest with ControlPointsInfo
}

CVector &SplineInterpolater::GetPosition(void) {
	return m_pos;
}

void SplineInterpolater::SetAcceleration(float fAcceleration) {
	m_fAcceleration = fAcceleration;
	
	if (fAcceleration == 0.0f)
		m_fSpeed = m_fMaxSpeed;
}

void SplineInterpolater::SetDeceleration(float fDeceleration) {
	m_fDeceleration = fDeceleration;
}

void SplineInterpolater::SetMaxSpeed(float fMaxSpeed) {
	m_fMaxSpeed = fMaxSpeed;
}

void SplineInterpolater::UpdateSpeed(float f) {
	;
}

void SplineInterpolater::UpdatePosition(float f) {
	;
}

float SplineInterpolater::CalculateDistanceToStop(void) {
#ifdef FIX_STRANGE_MATH
	return 1.5f * sqr(m_fSpeed) / m_fDeceleration;
#else
	return (m_fSpeed + ((m_fDeceleration / 2.0f) * (m_fSpeed / m_fDeceleration))) * m_fSpeed / m_fDeceleration;
#endif
}

int &SplineInterpolater::GetNumControlPoints(void) {
	return m_nNumControlPoints;
}