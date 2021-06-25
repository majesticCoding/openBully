#pragma once

class CColData;
class CEntity;

class CColModel {
public:
	CColModel();
	~CColModel();

	float dword0;
	float dword4;
	float dword8;  // maybe CVector
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