#pragma once
#include "hook.h"
#include "Vector.h"
#include "common.h"

class SplineInterpolater {
	HOOKED_CONSTRUCTOR_CLASS(SplineInterpolater);

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
	} *m_pInfos[2];
	
	int m_nNumControlPoints;

public:
	SplineInterpolater();
	virtual ~SplineInterpolater() {
		if (m_pInfos[0] != nullptr) {
			delete[] m_pInfos[0];
			m_pInfos[0] = nullptr;
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
	float CalculateDistanceToStop(void);
	int &GetNumControlPoints(void);
	ControlPointInfo *GetControlPointInfo(int controlIndex); //TODO: the returning value is incorrect!

	static void InjectHooks(void);
};

//float u - fractional portion
CVector CatmullRomCurve3(CVector const *right, CVector const *forward, CVector const *up, CVector const *pos, float u);
void CalculateSplinePoint(CVector &result, CVector right, CVector forward, CVector up, CVector pos, float u); //leftover