#pragma once

class cSCREAMAudioManager {
public:
	void PrepareForCutScene(char const *name, float volume);
	void PlayCutSceneAudio(void);
	void CleanupAfterCutScene(void);
};

extern cSCREAMAudioManager *Screamer;