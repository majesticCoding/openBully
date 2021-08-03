#pragma once
#include "rwplcore.h"

struct RwFrame {
	RwObject object;
	int dword8;
	RwLLLink inDirtyList;
	RwMatrix matrix;
	int dword44[18];
	RwFrame *root;
};

void RwFrameUpdateObjects(RwFrame *frame);
RwMatrix *RwFrameGetMatrix(RwFrame *frame);