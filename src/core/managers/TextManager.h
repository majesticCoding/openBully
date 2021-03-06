#pragma once
#include <cstdint>

class TextManager {
public:
	void LoadConversationText(uint32_t nTextNum);
	void LoadConversationText(char const *textName);
	void LoadMissionText(char const* textName);
	void LoadSecondaryMissionText(uint32_t);
	void LoadSecondaryMissionText(char const *textName);
	void UnloadConversation(void);
};

extern TextManager *theTextManager;