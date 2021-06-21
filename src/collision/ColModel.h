#pragma once

class CColModel {
public:
	~CColModel();

	void operator delete(void* p);
};