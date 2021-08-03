#include "hook.h"
#include "rwcore.h"

void RwFrameUpdateObjects(RwFrame *frame) {
	XCALL(0x6C9AF0);
}

RwMatrix *RwFrameGetMatrix(RwFrame *frame) {
	return &frame->matrix;
}