#pragma once
#include "patcher.h"

#define NUM_DIRENTRIES 864

class CDirectoryInfo {
	
};

class CDirectoryWithNamesInfo : public CDirectoryInfo {

};

class CDirectoryBase {
	int32_t __vmt; 
};

template <class T>
class CDirectoryTemplate : public CDirectoryBase {
public:
	virtual ~CDirectoryTemplate();
	CDirectoryTemplate(int32_t nDirEntries);

	void ReadDirFile(char const *fileName);
	bool FindItem(char const *itemName, uint32_t &, uint32_t &);
	bool FindItem(uint32_t itemNum, uint32_t &, uint32_t &);
	void FindItem(uint32_t itemNum);
	int32_t GetPositionSize(int32_t, uint32_t &, uint32_t &);
	void SetPositionSize(int32_t, uint32_t, uint32_t);
	void Empty(void);
	int32_t GetNumItems(void);
};

class CDirectory : public CDirectoryTemplate<CDirectoryInfo> {
private:
	char _pad[8];
public:
	virtual ~CDirectory();

	CDirectory(int32_t nDirEntries) : CDirectoryTemplate(nDirEntries) {

	}
};