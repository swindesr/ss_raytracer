#pragma once
#include <FreeImage.h>
#include "Light/Color.h"

class Painter
{
public:
	// Constructor
	Painter(BYTE* pixels);

	// Methods
	void paint(int index, const Color& color);

private:
	// Members
	BYTE* pixels_;
};

