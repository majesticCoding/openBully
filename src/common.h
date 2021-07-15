#pragma once
#include "hook.h"

#define FIX_STRANGE_MATH

template <typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T sqr(T x) { return x*x; }

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

template <typename T>
T max(T a, T b) { return a > b ? a : b; }

template <typename T>
T min(T a, T b) { return a > b ? a : b; }

template <typename T>
T clamp(T v, T low, T high) { return max(min(v, high), low); }

