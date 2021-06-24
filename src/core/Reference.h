#pragma once

class CReference;
class CEntity;

class CReference {
public:
	CReference *m_pNext;
	CEntity **m_ppEntity;
};