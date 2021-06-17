#pragma once
#include "patcher.h"

class ActionController {
public:
	ActionController();
	~ActionController();

	void Stop(void);

	char _pad[56];
};