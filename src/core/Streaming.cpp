#include "Streaming.h"

void CStreaming::SetModelIsDeletable(int32_t modelId) {
	XCALL(0x52FE40);
}

void CStreaming::DeleteAllRwObjects(void) {
	XCALL(0x52F0E0);
}

void CStreaming::RemoveUnusedModelsInLoadedList(void) {
	XCALL(0x530B50);
}