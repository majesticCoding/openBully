#pragma once
#include "patcher.h"

class TextManager {
public:
	void LoadConversationText(uint32_t nTextNum);
	void LoadConversationText(char const *textName);
};

extern TextManager *theTextManager;