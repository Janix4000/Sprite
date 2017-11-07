#pragma once
#include "Surface.h"
#include <vector>
#include "RectI.h"
#include "Graphics.h"

class Animation
{
public:
	Animation(int x, int y, int width, int height, Surface& sprite,
		float holdTime, int count, Color chroma = Colors::Magenta);
	void Draw(const Vei2& pos, Graphics& gfx) const;
	void Update(float dt);
private:
	//Private Functions
	void Advance();

	const Surface& sprite;
	std::vector<RectI> frames;
	float holdTime;
	float curTime = 0.0f;
	int index = 0;
	Color chroma;
};