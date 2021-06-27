#include "hook.h"
#include "Rect.h"

void CRect::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x4144B0, &CRect::Add);
	inject_hook(0x414570, &CRect::operator+=);
}

void CRect::Add(float x, float y) {
	if (x < left)
		left = x;

	if (x > right)
		right = x;

	if (y < top)
		top = y;

	if (y > bottom)
		bottom = y;
}

CRect &CRect::operator+=(const CVector2D &vec) {
	Add(vec.x, vec.y);
	return *this;
}