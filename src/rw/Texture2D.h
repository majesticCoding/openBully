#pragma once
#include "patcher.h"

class Texture2D {
	char pad[8];
};

void RwTextureDestroy(Texture2D *);