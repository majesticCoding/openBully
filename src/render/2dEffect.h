#pragma once
#include "Texture2D.h"

class C2dEffect {
public:
	char gap0[16];
	short int16;
	char gap12[2];
	Texture2D *dword14;
	Texture2D *dword18;
	char gap1C[28];
	char byte38;
	char gap39[7];

	C2dEffect *Next();
};
