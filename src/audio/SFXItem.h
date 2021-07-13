#pragma once

class SFXItem;

class SFXItemPtr {
public:
	SFXItem *item;

	void Set(SFXItem *_item);
};