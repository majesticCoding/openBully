#pragma once
#include "patcher.h"

#define NUM_DIRENTRIES 864

class CDirectory {

};

class CDirectoryInfo {

};

class CDirectoryWithNamesInfo {

};

template <class T>
class CDirectoryTemplate {
public:
	CDirectoryTemplate(int32_t n);
	~CDirectoryTemplate();

	void ReadDirFile(char const *fileName);
	bool FindItem(char const *itemName, uint32_t &, uint32_t &);
	bool FindItem(uint32_t itemNum, uint32_t &, uint32_t &);
	void FindItem(uint32_t itemNum);
	int32_t GetPositionSize(int32_t, uint32_t &, uint32_t &);
	void SetPositionSize(int32_t, uint32_t, uint32_t);
	void Empty(void);
	int32_t GetNumItems(void);
};