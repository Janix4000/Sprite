#pragma once
#include "Colors.h"
#include <string>
#include "ChiliWin.h"
#include <fstream>
#include "RectI.h"

class Surface
{

public:
	Surface(int width, int height );
	Surface(const std::string& filename);
	~Surface();
	Surface(const Surface& src);
	Surface& operator=(const Surface& src);

	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;

private:
	Color *pPixels = nullptr;
	int width;
	int height;
};