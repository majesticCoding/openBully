#pragma once
#include "hook.h"
#include "Vector.h"
#include "common.h"
#include "Allocation.h"

class Path;

class SplineInterpolater {
	HOOKED_CONSTRUCTOR_CLASS(SplineInterpolater);
	SplineInterpolater *Constructor();

	CVector m_pos;
	CVector pStart;
	CVector pEnd;
	int m_controlIndex;
	float m_fAcceleration;
	float m_fDeceleration;
	float m_fMaxSpeed;
	float m_fSpeed;
	float m_fDist;
	float m_fractPortion;

	struct ControlPointInfo {
		CVector point;
		float fLength;
	} *m_pAInfos;
	
	float m_field48;
	int m_nNumControlPoints;

public:
	SplineInterpolater();
	virtual ~SplineInterpolater() {
		if (m_pAInfos != nullptr) {
			operator delete(m_pAInfos);
			m_pAInfos = nullptr;
		}
	}

	CVector &GetPosition();
	void SetAcceleration(float fAcceleration);
	void SetDeceleration(float fDeceleration);
	void SetMaxSpeed(float fMaxSpeed);
	void UpdateSpeed(float t);
	void UpdateDistance(float t);
	void UpdatePosition(float t);
	void ResetInterpolation(void);
	void IncrementControlIndex(void);
	void CreateInterpolationVector(CVector*, CVector, CVector, CVector*);
	void ClearControlPoints(void);
	void SetControlPointsNoReset(Path const* pPath);
	void SetControlPoints(Path const *pPath);
	float CalculateDistanceToStop(void);
	int &GetNumControlPoints(void);
	ControlPointInfo *GetControlPointInfo(int controlIndex);

	static void InjectHooks(void);
};

//float u - fractional portion
CVector CatmullRomCurve3(CVector const *right, CVector const *forward, CVector const *up, CVector const *pos, float u);
void CalculateSplinePoint(CVector &result, CVector right, CVector forward, CVector up, CVector pos, float u); //leftover