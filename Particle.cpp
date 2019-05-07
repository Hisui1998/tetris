#include "Particle.h"
#include <DxLib.h>

std::unique_ptr<Particle, Particle::Particle_deleter> Particle::s_Instance(new Particle());

Particle::Particle()
{
	for (int i = 0; i < MAX_SPARK; i++)
	{
		spark[i].pos = 0;
		spark[i].v = { 0,0 };
		spark[i].light = 0;
	}
}


Particle::~Particle()
{
}

void Particle::Create(VECTOR2 pos,int rand)
{
	for (int r = 0 ;r < GetRand(rand);r++)
	{
		int i;
		for (i = 0; i < MAX_SPARK; i++)
		{
			if (spark[i].light<=0)
			{
				break;
			}
		}
		if (i != MAX_SPARK)
		{
			spark[i].pos = 0;
			spark[i].v = { 0,0 };
			spark[i].light=0;
			spark[i].pos = pos * 50;
			(i%2?spark[i].v.x: spark[i].v.y)= GetRand(1000) - 500;
			spark[i].light = 0xff;
		}
	}
}

void Particle::Move(bool isGravity)
{
	int i;

	// ‰Î‰Ô‚ÌˆÚ“®ˆ—
	for (i = 0; i < MAX_SPARK; i++)
	{
		if (spark[i].light<=0)
		{
			continue;
		}
		//spark[i].v.y += isGravity ? GetRand(10) : 0;

		spark[i].pos += spark[i].v;

		spark[i].light -= 5;
	}

}

void Particle::Draw(bool isGravity,int Color)
{
	Move(isGravity);
	for (int j = 0; j < MAX_SPARK; j++)
	{
		if (spark[j].light>0)
		{
			DrawBox(spark[j].pos.x/50-16, spark[j].pos.y/50-16, spark[j].pos.x / 50+16, spark[j].pos.y / 50+16,
				(Color==-1)?GetColor(spark[j].light, 0, 0): spark[j].light*Color/255,false);
		}
	}
}