#include "Painter.h"
#include <iostream>
#include "variables.h"

Painter::Painter(BYTE* pixels)
	: pixels_(pixels) {}

// Convert colors to bytes for image output
void Painter::paint(int index, const Color& color)
{
	int r, g, b;
	r = static_cast<int>(256 * clamp(color.r, 0.0, 0.999));
	g = static_cast<int>(256 * clamp(color.g, 0.0, 0.999));
	b = static_cast<int>(256 * clamp(color.b, 0.0, 0.999));

	int start = index * 3;
	pixels_[start + 2] = r;
	pixels_[start + 1] = g;
	pixels_[start] = b;
}
