#include "SplineInterpolater.h"
#include "Matrix.h"


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
	inject_hook(0x5091C0, &SplineInterpolater::Constructor<>);
	//inject_hook(0x508530, &SplineInterpolater::UpdateSpeed); //crashes
	inject_hook(0x5083A0, &SplineInterpolater::SetAcceleration);
	inject_hook(0x5083C0, &SplineInterpolater::SetDeceleration);
	inject_hook(0x5083D0, &SplineInterpolater::SetMaxSpeed);
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
	pStart = CVector::Zero;
	pEnd = CVector::Zero;
	m_fAcceleration = 5.0f;
	m_fDeceleration = 5.0f;
	m_controlIndex = 0;
	m_fMaxSpeed = 30.0f;
	m_fSpeed = 0.0f;
	m_fDist = 0.0f;
	m_nNumControlPoints = 0;
	m_pInfos[0] = nullptr;
	m_pInfos[1] = nullptr;
}

void SplineInterpolater::ResetInterpolation(void) {
	m_controlIndex = 0;
	m_fDist = 0.0;
	m_fSpeed = 0.0;
	m_fractPortion = 0.0;
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

void SplineInterpolater::UpdateSpeed(float t) {
	int newControlIdx = m_controlIndex + 2;
	ControlPointInfo *p = GetControlPointInfo(newControlIdx);

	float fDeltaDist = p->fLength - m_fDist;
	if (m_nNumControlPoints - 1 > newControlIdx) {
		do {
			p = GetControlPointInfo(newControlIdx++);
			fDeltaDist += p->fLength;
		} while (m_nNumControlPoints - 1 != newControlIdx);
	}

	if (CalculateDistanceToStop() < fDeltaDist)
		m_fSpeed += m_fAcceleration * t;
	else
		m_fSpeed -= m_fDeceleration * t;

	m_fSpeed = Clamp(m_fSpeed, 0.0f, m_fMaxSpeed);
}

void SplineInterpolater::UpdateDistance(float t) {
	m_fDist += m_fSpeed * t;
	ControlPointInfo *p = GetControlPointInfo(m_controlIndex + 2);
	
	if (p->fLength < m_fDist) {
		IncrementControlIndex();
		m_fDist = m_fDist * 2.0f - p->fLength;
	}
}

void SplineInterpolater::UpdatePosition(float t) {
	if (m_nNumControlPoints == 0)
		return;

	UpdateSpeed(t);
	UpdateDistance(t);

	ControlPointInfo *pMid1 = GetControlPointInfo(m_controlIndex + 1);
	ControlPointInfo *pMid2 = GetControlPointInfo(m_controlIndex + 2);
	if (pMid2->fLength > 0.0f)
		m_fractPortion = m_fDist / pMid2->fLength;

	m_pos = CatmullRomCurve3(&pStart, &pMid1->point, &pMid2->point, &pEnd, m_fractPortion);
}

void SplineInterpolater::ClearControlPoints(void) {
	if (m_pInfos[0] != nullptr) {
		delete[] m_pInfos[0];
		m_pInfos[0] = nullptr;
	}

	//why isn't it deleted the same way as 1st? Bug?
	m_pInfos[1] = nullptr;

	m_nNumControlPoints = 0;
}

void SplineInterpolater::CreateInterpolationVector(CVector *, CVector, CVector, CVector *) {
	;
}

void SplineInterpolater::IncrementControlIndex(void) {
	m_controlIndex++;
	m_fDist = 0.0f;
	m_fractPortion = 0.0f;

	ControlPointInfo *p1 = GetControlPointInfo(m_controlIndex);
	pStart = CVector(p1->point.x, p1->point.y, p1->point.z);
	ControlPointInfo *p2 = GetControlPointInfo(m_controlIndex + 3);
	pEnd = CVector(p2->point.x, p2->point.y, p2->point.z);

	ControlPointInfo *pMid1 = GetControlPointInfo(m_controlIndex + 1);
	ControlPointInfo *pMid2 = GetControlPointInfo(m_controlIndex + 2);

	CreateInterpolationVector(&pStart, pMid1->point, pMid2->point, &pEnd);
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

SplineInterpolater::ControlPointInfo* SplineInterpolater::GetControlPointInfo(int controlIndex) {
	int newIdx = m_nNumControlPoints - 1;
	if (controlIndex <= newIdx)
		newIdx = controlIndex & ~(controlIndex >> 31);

	return m_pInfos[newIdx];
}