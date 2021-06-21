#pragma once

class PathManager {
	char _pad[0x10];
public:
	PathManager(void);
};

extern PathManager *g_PathManager;