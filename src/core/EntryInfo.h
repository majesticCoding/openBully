#pragma once

class CEntryInfoNode {
public:
	int dword0;
	int dword4;
	int dword8;
	CEntryInfoNode *m_pPrevious;
	CEntryInfoNode *m_pNext;
};

class CEntryInfoList {
public:
	CEntryInfoNode *m_pNode;

	void Flush();
};