#pragma once
#include "patcher.h"
#include "ColModel.h"

enum ModelInfoType {

};

class CBaseModelInfo {
public:
	virtual ~CBaseModelInfo();
	virtual void SetModelName(char const *name);
	virtual void Shutdown(void);
	virtual void _mB0(void) = 0;
	virtual void _mB4(void) = 0;
	virtual void _mB8(void) = 0;
	virtual void SetAnimFile(char const *name); // = 0; ??
	virtual int32_t GetAnimFileIndex(void) { return -1; }
	virtual int32_t GetAnimFile2Index(void) { return -1; }
	virtual int32_t GetAnimFile3Index(void) { return -1; }
	virtual int32_t GetAnimFile4Index(void) { return -1; }
	virtual int16_t GetActionTreeStreamIndex(void) { return -1; }

	CBaseModelInfo(ModelInfoType type);
	void SetColModel(CColModel *pCol, bool owns = false);
};