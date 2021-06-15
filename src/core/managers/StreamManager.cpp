#include "StreamManager.h"

StreamManager *g_StreamManager = reinterpret_cast<StreamManager *>(0xCF4284);

void StreamManager::StopStream(int32_t param) {
	XCALL(0x5A6210);
}