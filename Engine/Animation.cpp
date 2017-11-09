#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, Surface & sprite, float holdTime, int count, int alpha, Color chroma)
	:
sprite(sprite),
holdTime(holdTime),
chroma(chroma)
{
	if (alpha > 255)alpha = 255;
	else if (alpha < 0) alpha = 0;
	this->alpha = alpha;
	for (int i = 0; i < count; i++)
	{
		frames.emplace_back(RectI(x + i*width, x + (i + 1)*width, y, y + height));
	}
}

void Animation::Draw(const Vei2 & pos, Graphics & gfx) const
{
	gfx.DrawSpriteTransparent(pos.x, pos.y, frames[index], sprite, alpha, chroma);
}

void Animation::Update(float dt)
{
	curTime += dt;
	while (curTime >= holdTime)
	{
		Advance();
		curTime -= holdTime;
	}
}

void Animation::Advance()
{
	if (++index >= frames.size())
	{
		index = 0;
	}
}
