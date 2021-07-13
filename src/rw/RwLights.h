#pragma once

class RpWorld;

class CRwLights {
public:
	void Create(RpWorld *pScene);
	void Destroy();
	void Blackout();
	void Colored();
	void SetPropsAmbientColors(float color);
	void SetSkyColors();
	void LightsUpload(unsigned int arg0);
};

extern CRwLights &g_rwLights;