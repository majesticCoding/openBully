#pragma once
#include <cstdint>

#include "ColModel.h"

enum ModelInfoType  : uint8_t {
	MITYPE_NA,
	MITYPE_SIMPLE,
	MITYPE_TIME = 3,
	MITYPE_WEAPON,
	MITYPE_CLUMP = 6,
	MITYPE_VEHICLE = 8,
	MITYPE_PED,
	MITYPE_ANIM = 10,
	MITYPE_CLOTH
};

class CBaseModelInfo {
protected:
	char const *m_hash; //0x4
	ModelInfoType m_type;
	bool m_bOwnsColModel;
	int8_t m_fieldA;
	int8_t m_fieldB;
	CColModel *m_pCol;
	int16_t m_2dEffectId;
	int16_t m_objectId;
	uint16_t m_w3;
	int16_t m_txdSlot;
	char _pad[8];

public:
	CBaseModelInfo(ModelInfoType Type);

	virtual ~CBaseModelInfo() {};
	virtual void SetModelName(char const *name);
	virtual void Shutdown(void);
	virtual void DeleteRwObject(void) = 0;
	virtual int *CreateInstance(void) = 0; //TODO: replace with RwObject *
	virtual int *GetRwObject(void) = 0; //TODO: replace with RwObject *
	virtual void SetAnimFile(char const *name) = 0;
	virtual int32_t GetAnimFileIndex(void) { return -1; }
	virtual int32_t GetAnimFile2Index(void) { return -1; }
	virtual int32_t GetAnimFile3Index(void) { return -1; }
	virtual int32_t GetAnimFile4Index(void) { return -1; }
	virtual int16_t GetActionTreeStreamIndex(void) { return -1; }

	void SetColModel(CColModel *pCol, bool bOwns = false);
	void FindBute(void);
	void SetTexDictionary(char const *texDictName, bool bParam);
	void DeleteCollisionModel(void);
	void Delete2dEffects(void);
	bool IsModelName(char const *name);
};