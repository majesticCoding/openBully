#include "AudioManager.h"

cSCREAMAudioManager *Screamer = reinterpret_cast<cSCREAMAudioManager *>(0xCF3DA0);

void cSCREAMAudioManager::PrepareForCutScene(char const *name, float volume) {
	XCALL(0x5951C0);
}

void cSCREAMAudioManager::PlayCutSceneAudio(void) {
	XCALL(0x595AD0);
}

void cSCREAMAudioManager::CleanupAfterCutScene(void) {
	XCALL(0x595290);
}