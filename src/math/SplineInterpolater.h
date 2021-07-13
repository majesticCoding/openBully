#pragma once
#include "Vector.h"
#include "common.h"

class SplineInterpolater {
	CVector m_pos;
	CVector p1;
	CVector p2;
	int m_controlIndex;
	float m_fAcceleration;
	float m_fDeceleration;
	float m_fMaxSpeed;
	float m_fSpeed;
	float m_fUnk;
	char _pad[12];
	int m_nNumControlPoints;

public:
	SplineInterpolater();
	virtual ~SplineInterpolater() {}

	CVector &GetPosition();
	void SetAcceleration(float fAcceleration);
	void SetDeceleration(float fDeceleration);
	void SetMaxSpeed(float fMaxSpeed);
	void UpdateSpeed(float f);
	void UpdatePosition(float f);
	void ResetInterpolation(void);
	float CalculateDistanceToStop(void);
	int &GetNumControlPoints(void);

	static void InjectHooks(void);
};

//float u - fractional portion
CVector CatmullRomCurve3(CVector const *right, CVector const *forward, CVector const *up, CVector const *pos, float u);
void CalculateSplinePoint(CVector &result, CVector right, CVector forward, CVector up, CVector pos, float u); //leftover