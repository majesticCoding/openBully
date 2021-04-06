#pragma once
#include "patcher.h"

class TextManager {
public:
	void LoadConversationText(uint32_t nTextNum);
	void LoadConversationText(char const *textName);
	void UnloadConversation(void);
};

extern TextManager *theTextManager;