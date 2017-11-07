#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, Surface & sprite, float holdTime, int count, Color chroma)
	:
sprite(sprite),
holdTime(holdTime),
chroma(chroma)
{
	for (int i = 0; i < count; i++)
	{
		frames.emplace_back(RectI(x + i*width, x + (i + 1)*width, y, y + height));
	}
}

void Animation::Draw(const Vei2 & pos, Graphics & gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[index], sprite, chroma);
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
