#pragma once
#include "hook.h"

#define FIX_STRANGE_MATH

class CRGBA
{
public:
	union
	{
		uint32_t color32;
		struct { uint8_t red, green, blue, alpha; };
	};

	CRGBA() = default;
	CRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : red(r), green(g), blue(b), alpha(a) { }

	bool operator ==(const CRGBA& right)
	{
		return this->red == right.red && this->green == right.green && 
			this->blue == right.blue && this->alpha == right.alpha;
	}

	bool operator !=(const CRGBA& right)
	{
		return !(*this == right);
	}

	CRGBA& operator =(const CRGBA& right)
	{
		this->red = right.red;
		this->green = right.green;
		this->blue = right.blue;
		this->alpha = right.alpha;
		return *this;
	}
};

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

