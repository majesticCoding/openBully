#pragma once
#include "patcher.h"
#include "ColModel.h"

enum ModelInfoType {

};

class CBaseModelInfo {
public:
	CBaseModelInfo(ModelInfoType type);

	virtual ~CBaseModelInfo() {};
	virtual void SetModelName(char const *name) {}
	virtual void Shutdown(void) {}
	virtual void DeleteRwObject(void) = 0;
	virtual int *CreateInstance(void) = 0; //TODO: replace with RwObject *
	virtual int *GetRwObject(void) = 0; //TODO: replace with RwObject *
	virtual void SetAnimFile(char const *name) {}
	virtual int32_t GetAnimFileIndex(void) { return -1; }
	virtual int32_t GetAnimFile2Index(void) { return -1; }
	virtual int32_t GetAnimFile3Index(void) { return -1; }
	virtual int32_t GetAnimFile4Index(void) { return -1; }
	virtual int16_t GetActionTreeStreamIndex(void) { return -1; }

	void SetColModel(CColModel *pCol, bool owns = false);
};