#pragma once
#include "hook.h"
#include "Placeable.h"
#include "Reference.h"
#include "CollisionType.h"

class AM_RenObj;
class CRect;
class CPed;
class ActionNode;
class RwObject;

enum class eEntityType : unsigned char {
	ENTITY_TYPE_NOTHING = 0,
	ENTITY_TYPE_BUILDING,
	ENTITY_TYPE_VEHICLE,
	ENTITY_TYPE_PED,
	ENTITY_TYPE_OBJECT,
	ENTITY_TYPE_DUMMY,
	ENTITY_TYPE_PROPANIM,
	ENTITY_TYPE_ACCESSORY
};

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
	unsigned int m_bHasPreRenderEffects;
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
	HOOKED_CONSTRUCTOR_CLASS(CEntity);
protected:
	RwObject *m_pRwObject;
	CEntityFlags m_flags;
	eEntityType m_nType : 3;
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
	void ProcessLightsForEntity();
	bool IsBreakableLight();
	void AttachToRwObject(RwObject *pObject);
	void DetachFromRwObject();

	virtual bool IsType(short type);
	virtual void Add();
	virtual void Remove();
	virtual bool IsBike();
	virtual bool IsCar();
	virtual void SetStatus(int nStatus);
	virtual void SetIsStatic(bool bIsStatic);
	virtual void SetModelIndex(short nModelIndex, bool arg1);
	virtual void SetModelIndexNoCreate(short nModelIndex);
	virtual void CreateRwObject(bool arg0, bool arg1);
	virtual void GetBoundRect(CRect *out);
	virtual void ProcessControl();
	virtual void ProcessShift(bool arg0);
	virtual void Teleport(CVector position);
	virtual bool PlayHitReaction(float a2, float a3, CPed *a4, int a5, CVector *a6, CVector *a7,
		ActionNode *a8, bool a9, const char *a10, bool a11, float a12, float a13, bool a14, bool a15,
		bool a16, int a17, float a18, CollisionType a19);
	virtual void *GetContext();
	virtual void PreRender();
	virtual void Render();
	virtual void UpdateAnim();
	virtual bool CollidePostAnimUpdate();
	virtual bool ShouldUpdateAnim();
	virtual void SetupLighting() = 0;
	virtual void FlagToDestroyWhenNextProcessed();
	virtual void GetClosestPoint(CVector *out, const CVector &arg0);
	virtual float GetHeight();
	virtual float GetWidth();
	virtual float GetBoundRadius();
	virtual bool IsDestroyed();
	virtual bool IsDamageable();
	virtual float GetHitPoints();
	virtual bool HasObstacle();

	static short GetCEntity();
	static void InjectHooks();
};

extern short &g_FakeRTTI_ID;

void HelperCleanupOldReference(CEntity *pEntity, CEntity **ppEntity);
void HelperRegisterReference(CEntity *pEntity, CEntity **ppEntity);