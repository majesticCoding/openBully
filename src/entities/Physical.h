#pragma once
#include "Entity.h"
#include "EntryInfo.h"

class CColPoint;

class CPhysical : public CEntity {
public:
	CPhysical();
	~CPhysical();

	float float120;
	CVector m_vecMoveSpeed;
	CVector m_vecTurnSpeed;
	float float13C;
	float float140;
	float float144;
	float float148;
	float float14C;
	float float150;
	float float154;
	unsigned char gap158[20];
	float float16C;
	float float170;
	float float174;
	CEntryInfoList dword178;
	short *dword17C;
	unsigned char byte180;
	unsigned char byte181;
	unsigned char gap182[2];
	int dword184;
	int dword188;
	int dword18C;
	int dword190;
	int dword194;
	int dword198;
	float float19C;
	float float1A0;
	unsigned int dword1A4;
	float float1A8;
	float float1AC;
	float float1B0;
	unsigned short word1B4;
	unsigned char gap1B6[2];
	unsigned int dword1B8;
	unsigned char byte1BC;
	unsigned char byte1BD;

	// virtual methods
	bool IsType(short type);
	void Add();
	void Remove();
	void GetBoundRect(CRect *out);
	void ProcessControl();
	void ProcessShift(bool arg0);

	virtual bool GetUsesSimpleIntegration();
	virtual float GetGravityForce();
	virtual void ApplyGravity();
	virtual void ApplyMoveSpeed();
	virtual void ApplyTurnSpeed();
	virtual void SetOldMat(const CMatrix &mat);
	virtual void GetOldMat(CMatrix &out);
	virtual bool ProcessEntityCollision(CMatrix &arg0, CEntity *arg1,
		CColPoint *arg2, int arg3);

	static short GetCPhysical();
};