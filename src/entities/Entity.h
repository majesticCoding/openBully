#pragma once
#include "hook.h"
#include "Placeable.h"
#include "Reference.h"

class AM_RenObj;
class CRect;

struct CEntityFlags {
	int dword0;
	int dword4;
	int dword8;
	unsigned int m_bIsStatic;
	int dword10;
	int dword14;
	int dword18;
	int dword1C;
	int dword20;
	int dword24;
	int dword28;
	int dword2C;
	int dword30;
	int dword34;
	int dword38;
	int dword3C;
	int dword40;
	int dword44;
	int dword48;
	int dword4C;
	int dword50;
	int dword54;
	int dword58;
	int dword5C;
	int dword60;
	int dword64;
	int dword68;
	int dword6C;
	int dword70;
	int dword74;
	int dword78;
	int dword7C;
	int dword80;
	int dword84;
	int dword88;
	int dword8C;
	int dword90;
	int dword94;
	int dword98;
	int dword9C;
	int dwordA0;
	int dwordA4;
	int dwordA8;
	int dwordAC;
	unsigned int m_bIsDestroyed;
	int dwordB4;
	int dwordB8;
	int dwordBC;
	int dwordC0;
	int dwordC4;
	int dwordC8;
	int dwordCC;
	int dwordD0;
	int dwordD4;
	int dwordD8;
	int dwordDC;
	int dwordE0;
	int dwordE4;
	int dwordE8;

	void Clear();
};

class CEntity : public CPlaceable {
protected:
	char *dword18; // maybe RwObject
	CEntityFlags m_flags;
	unsigned char m_nType : 3;
	unsigned char m_nStatus : 5;
	short word10A;
	unsigned short m_nRandomSeed;
	short m_nModelIndex;
	char byte110;
	char byte111;
	short word112;
	AM_RenObj *dword114;
	CReference *m_pReferences;
	float float11C;
public:
	CEntity();
	~CEntity();

	void RegisterReference(CEntity **ppEntity);
	void CleanUpOldReference(CEntity **ppEntity);
	void ResolveReferences();
	void PruneReferences();
	bool HasPreRenderEffects();
	void DeleteRwObject();

	virtual bool IsType(short type) = 0;
	virtual void Add() = 0;
	virtual void Remove() = 0;
	virtual bool IsBike();
	virtual bool IsCar();
	virtual void SetStatus(int nStatus);
	virtual void SetIsStatic(bool bIsStatic) = 0;
	virtual void SetModelIndex(unsigned int nModelIndex, bool arg1) = 0;
	virtual void SetModelIndexNoCreate(unsigned int arg0) = 0;
	virtual int  CreateRwObject(int arg0, bool arg1) = 0;
	virtual void GetBoundRect(CRect *arg0) = 0;
	// not all virtual methods 
};