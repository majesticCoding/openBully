#pragma once
#include "Entity.h"

class CPhysical : public CEntity {
public:
	CPhysical();
	~CPhysical();

	float float120;
	float float124;
	float float128;
	float float12C;
	float float130;
	float float134;
	float float138;
	float float13C;
	float float140;
	float float144;
	float float148;
	float float14C;
	float float150;
	float float154;
	unsigned char gap158[20];
	float float16C;
	float float170;
	float float174;
	unsigned int dword178;
	unsigned int dword17C;
	unsigned char byte180;
	unsigned char byte181;
	unsigned char gap182[2];
	unsigned int dword184;
	unsigned int dword188;
	unsigned int dword18C;
	unsigned int dword190;
	unsigned int dword194;
	unsigned int dword198;
	float float19C;
	float float1A0;
	unsigned int dword1A4;
	float float1A8;
	float float1AC;
	float float1B0;
	unsigned short word1B4;
	unsigned char gap1B6[2];
	unsigned int dword1B8;
	unsigned char byte1BC;
	unsigned char byte1BD;

	// virtual methods
	bool IsType(short type);
	void Add();
	void Remove();
	// not all virtual methods
};