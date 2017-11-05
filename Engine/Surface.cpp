#include "Surface.h"
#include <cassert>

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixels(new Color[width*height])
{
}

Surface::Surface(const std::string & filename)
{
	std::ifstream in(filename.c_str(), std::ios::binary);
	assert(in);
	BITMAPFILEHEADER bmFH;
	in.read(reinterpret_cast<char*>(&bmFH), sizeof(bmFH));

	BITMAPINFOHEADER bmIH;
	in.read(reinterpret_cast<char*>(&bmIH), sizeof(bmIH));

	assert(bmIH.biBitCount == 24 || bmIH.biBitCount==32);
	assert(bmIH.biCompression == BI_RGB);

	width = bmIH.biWidth;

	int add;
	int yStart;
	int yEnd;
	if (bmIH.biHeight >= 0)
	{
		add = -1;
		yStart = bmIH.biHeight - 1;
		yEnd = -1;
	}
	else
	{
		add = 1;
		yStart = 0;
		yEnd = bmIH.biHeight;
	}


	height = abs(bmIH.biHeight);

	pPixels = new Color[width*height];

	const int padding = (4 - (width * bmIH.biBitCount/8) % 4) % 4;
	in.seekg(bmFH.bfOffBits);

	for (int y = yStart; y != yEnd; y+=add)
	{
			for (int x = 0; x < width; x++)
			{
				PutPixel(x, y, Color(in.get(), in.get(), in.get()));
				if (bmIH.biBitCount == 32) in.get();
			}
		in.seekg(padding, std::ios::cur);
	}
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface::Surface(const Surface & src)
	:
	Surface(src.width, src.height)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			pPixels[y*width + x] = src.pPixels[y*width + x];
		}
	}
}

Surface & Surface::operator=(const Surface & src)
{
	delete[] pPixels;
	pPixels = new Color[width*height];
	width = src.width;
	height = src.height;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			pPixels[y*width + x] = src.pPixels[y*width + x];
		}
	}
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y*width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y*width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

RectI Surface::GetRect() const
{
	return { 0, width, 0, height };
}
