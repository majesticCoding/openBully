#pragma once

#include "mem.h"

// macros
#define CALL_CONSTRUCTOR(c, ...) this->c::c(__VA_ARGS__)
#define HOOKED_CONSTRUCTOR_CLASS(c) \
template <typename... Args> \
c *Constructor(Args... args) { \
	CALL_CONSTRUCTOR(c, args...); \
	return this; \
}

#define CALL_DESTRUCTOR(c) this->c::~c()
#define HOOKED_DESTRUCTOR_CLASS(c) \
c *Destructor() { \
	CALL_DESTRUCTOR(c); \
	return this; \
}

namespace memory {
namespace hook {
enum class HookType {
	Jump,
	Call
};

constexpr std::size_t jmp_call_size = 5;

template <typename FuncT>
void inject_hook(std::uintptr_t addr, FuncT hook, HookType type = HookType::Jump) {
	unprotect unprot(reinterpret_cast<void*>(addr), jmp_call_size);
	std::uintptr_t addrhook = reinterpret_cast<std::uintptr_t>(
		reinterpret_cast<void *&>(hook));

	write<unsigned char>(addr, type == HookType::Jump ? 0xE9 : 0xE8);
	write<std::uintptr_t>(addr + 1, addrhook - addr - jmp_call_size);
}
}; // namespace hook
}; // namespace memory