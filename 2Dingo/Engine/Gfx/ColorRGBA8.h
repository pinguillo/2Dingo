#pragma once

struct ColorRGBA8
{
	ColorRGBA8() : r(255), g(255), b(255), a(255) {	}
	ColorRGBA8(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : r(R), g(G), b(B), a(A) {	}
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};