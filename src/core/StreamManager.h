#pragma once
#include "patcher.h"

class StreamManager {
public:
	void StopStream(int32_t param);
};

extern StreamManager *g_StreamManager;