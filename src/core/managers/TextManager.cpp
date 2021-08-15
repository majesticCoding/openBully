#include "hook.h"
#include "TextManager.h"

TextManager *theTextManager = reinterpret_cast<TextManager *>(0x20C2FA4);

void TextManager::LoadConversationText(char const *textName) {
	XCALL(0x68FD50);
}

void TextManager::UnloadConversation(void) {
	XCALL(0x68F520);
}

void TextManager::LoadMissionText(char const* textName) {
	XCALL(0x68FCB0);
}

void TextManager::LoadSecondaryMissionText(char const* textName) {
	XCALL(0x68FD00);
}