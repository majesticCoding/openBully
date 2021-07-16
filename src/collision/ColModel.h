#pragma once
#include "Vector.h"

class CColData;
class CEntity;

class CColModel {
public:
	CColModel();
	~CColModel();

	CVector vec0;
	float dwordC;
	float dword10;
	float dword14;
	int dword18[6];
	short short30;
	short short32;
	char byte34;
	CColData *m_pData;
	CEntity *m_pEntity;

	void SetEntity(CEntity *pEntity);
	
	void operator delete(void* p);
};