#pragma once
#include <cstdint>

template<typename T, typename U = T>
class CPool
{
	U *m_entries;
	uint8_t *m_flags;
	int32_t m_size;
	int32_t m_allocPtr;
};