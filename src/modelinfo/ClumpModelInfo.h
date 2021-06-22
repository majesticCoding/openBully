#pragma once
#include "BaseModelInfo.h"

class CClumpModelInfo : public CBaseModelInfo {
public:
	int *m_clump; //RpClump
	union {
		int32_t m_animFileIndex;
		char *m_animFileName;
	};

	CClumpModelInfo(void) : CBaseModelInfo(MITYPE_CLUMP) {}
	CClumpModelInfo(ModelInfoType Type) : CBaseModelInfo(Type) {}

	~CClumpModelInfo();
	void DeleteRwObject(void);
	int *CreateInstance(void) { return nullptr; }; //TODO: replace with RwObject *
	int *GetRwObject(void) { return nullptr; }; //TODO: replace with RwObject *
	void SetAnimFile(char const *file) {};

	virtual int GetAnimFileIndex(void) { return m_animFileIndex; }
};
