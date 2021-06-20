#pragma once

#include <cstdint>
#include <algorithm>

namespace memory {
class unprotect {
	void         *addr = nullptr;
	std::size_t   size = 0;
	unsigned long prot = 0;

public:
	unprotect(void *_addr, std::size_t _size);
	~unprotect();
};

template <typename T>
T &read(std::uintptr_t addr, bool vp = true) {
	unprotect prot(vp ? reinterpret_cast<void*>(addr) : nullptr, sizeof(T));

	return *reinterpret_cast<T *>(addr);
}

template <typename T>
void write(std::uintptr_t addr, T val, bool vp = true) {
	unprotect prot(vp ? reinterpret_cast<void*>(addr) : nullptr, sizeof(T));

	*reinterpret_cast<T *>(addr) = val;
}

template <typename T>
void fill(std::uintptr_t addr, std::size_t count, T val, bool vp = true) {
	unprotect prot(vp ? reinterpret_cast<void*>(addr) : nullptr,
		sizeof(T) * count);

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