#include <Windows.h>

#include "mem.h"

namespace memory {

unprotect::unprotect(void *_addr, std::size_t _size):
	addr(_addr), size(_size) {
	if (addr && size)
		VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &prot);
}

unprotect::~unprotect() {
	if (addr && size)
		VirtualProtect(addr, size, prot, &prot);
}

}; // namespace memory