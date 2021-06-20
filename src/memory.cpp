#include <Windows.h>

#include "memory.hpp"

namespace memory {

unprotect::unprotect(void *_addr, std::size_t _size):
	addr(_addr), size(_size) {
	VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &prot);
}

unprotect::~unprotect() {
	VirtualProtect(addr, size, prot, &prot);
}

}; // namespace memory