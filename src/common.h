#pragma once

#define FIX_STRANGE_MATH

template <typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T sqr(T x) { return x*x; }

#define Max(a,b) ((a) > (b) ? (a) : (b))
#define Min(a,b) ((a) < (b) ? (a) : (b))

#define Clamp(v, low, high) ((v)<(low) ? (low) : (v)>(high) ? (high) : (v))