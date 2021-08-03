#pragma once

typedef unsigned char RwUInt8;
typedef float RwReal;

struct RwFrame;

struct RwV3d {
	RwReal x;
	RwReal y;
	RwReal z;
};

struct RwMatrix {
	float rightx, forwardx, upx;
	float righty, forwardy, upy;
	float rightz, forwardz, upz;
	RwV3d pos;
};

struct RwLLLink {
	RwLLLink *next;
	RwLLLink *prev;
};

struct RwObject {
	RwUInt8 type;
	RwUInt8 subType;
	RwUInt8 flags;
	RwUInt8 privateFlags;
	void *parent;
};

#define RwObjectGetFrame(_object) \
	(RwFrame *)((_object)->parent)