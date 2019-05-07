#include "Particle.h"
#include <DxLib.h>

std::unique_ptr<Particle, Particle::Particle_deleter> Particle::s_Instance(new Particle());

Particle::Particle()
{
	for (int i = 0; i < MAX_SPARK; i++)
	{
		spark[i].x = 0;
		spark[i].y = 0;
		spark[i].vx = 0;
		spark[i].vy = 0;
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
			spark[i].x = 0;
			spark[i].y = 0;
			spark[i].vx = 0;
			spark[i].vy = 0;
			spark[i].light = 0;
			spark[i].x = pos.x * 50;
			spark[i].y = pos.y * 50;
			(i%2?spark[i].vx: spark[i].vy)= GetRand(1000) - 500;
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

		spark[i].x += spark[i].vx;
		spark[i].y += spark[i].vy;

		spark[i].light -= 5;
	}

}

void Particle::Draw(bool isGravity,int Color,bool isCircle)
{
	Move(isGravity);
	for (int j = 0; j < MAX_SPARK; j++)
	{
		if (spark[j].light>0)
		{
			isCircle ?
				DrawCircle(spark[j].x / 50 - 16, spark[j].y / 50 - 16, spark[j].light / 32,
				(Color == -1) ? GetColor(0, 0, spark[j].light) : spark[j].light*Color / 255, false) :
				DrawBox(spark[j].x / 50 - 16, spark[j].y / 50 - 16, spark[j].x / 50 + 16, spark[j].y / 50 + 16,
				(Color == -1) ? GetColor(0, 0, spark[j].light) : spark[j].light*Color / 255, false);
		}
	}
}