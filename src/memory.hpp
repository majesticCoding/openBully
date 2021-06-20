#pragma once

#include <cstdint>
#include <algorithm>

namespace memory {
class unprotect {
	void         *addr;
	std::size_t   size;
	unsigned long prot;

public:
	unprotect(void *_addr, std::size_t _size);
	~unprotect();
};

template <typename T>
T &read(std::uintptr_t addr, bool vp = true) {
	if (vp)
		unprotect prot(reinterpret_cast<void*>(addr), sizeof(T));
	
	return *reinterpret_cast<T *>(addr);
}

template <typename T>
void write(std::uintptr_t addr, T val, bool vp = true) {
	read<T>(addr, vp) = val;
}

template <typename T>
void fill(std::uintptr_t addr, std::size_t count, T val, bool vp = true) {
	if (vp)
		unprotect prot(reinterpret_cast<void*>(addr), sizeof(T) * count);

	std::fill_n(reinterpret_cast<T*>(addr), count, val);
}

inline void nop(std::uintptr_t addr, std::size_t count, bool vp = true) {
	fill<unsigned char>(addr, count, 0x90, vp);
}

template <typename RetT = void, typename... Args>
RetT call(std::uintptr_t addr, Args... args) {
	return reinterpret_cast<RetT(*)(Args...)>(addr)
		(args...);
}

template <typename ClassT, typename RetT = void, typename... Args>
RetT call_method(std::uintptr_t addr, ClassT _this, Args... args) {
	return reinterpret_cast<RetT(__thiscall*)(ClassT, Args...)>(addr)
		(_this, args...);
}
}; // namespace memory