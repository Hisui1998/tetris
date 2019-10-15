#include "Particle.h"
#include <DxLib.h>


Particle::Particle():MAX_SPARK(8000)
{
	for (int i = 0; i < MAX_SPARK; i++)
	{
		spark[i].isUsed = false;
		spark[i].v = { 0,0 };
	}
}


Particle::~Particle()
{
}


void Particle::Init()
{
	Element e;
	e.isUsed = false;
	e.light = 0;
	e.pos = { 0,0 };
	e.v = { 0,0 };

	for (int cnt = 0;cnt<)
	{

	}
}

void Particle::Create(VECTOR2 pos,int rand)
{
	for (int r = 0 ;r < GetRand(rand);r++)
	{
		int i;
		for (i = 0; i < MAX_SPARK; i++)
		{
			if (!spark[i].isUsed)
			{
				break;
			}
		}
		if (i != MAX_SPARK)
		{
			spark[i].pos = pos*32;
			(GetRand(2)?spark[i].v.x: spark[i].v.y)= GetRand(500) - 250;
			spark[i].light = 0xff;
			spark[i].isUsed = true;
		}
	}
}

void Particle::Move(bool isGravity)
{
	int i;

	// ‰Î‰Ô‚ÌˆÚ“®ˆ—
	for (i = 0; i < MAX_SPARK; i++)
	{
		if (!spark[i].isUsed)
		{
			continue;
		}
		//spark[i].v.y += isGravity ? GetRand(10) : 0;

		spark[i].pos.x += spark[i].v.x;
		spark[i].pos.y += spark[i].v.y;

		spark[i].light -= 3;

		if (spark[i].light < 0)
		{
			spark[i].isUsed = false;
		}
	}
}

void Particle::Draw(bool isGravity)
{
	Move(isGravity);
	for (int j = 0; j < MAX_SPARK; j++)
	{
		if (spark[j].isUsed == 1)
		{
			DrawPixel(spark[j].pos.x/32, spark[j].pos.y/32,
				GetColor(spark[j].light/2, spark[j].light, spark[j].light));
		}
	}
}