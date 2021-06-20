#pragma once

#include "memory.hpp"

// macros
#define CALL_CONSTRUCTOR(c, ...) this->c::c(__VA_ARGS__)
#define HOOKED_CONSTRUCTOR_CLASS(c, ...) c *c::Constructor(__VA_ARGS__)

#define CALL_DESTRUCTOR(c, ...) this->c::~c(__VA_ARGS__)
#define HOOKED_DESTRUCTOR_CLASS(c, ...) c *Destructor(__VA_ARGS__)

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