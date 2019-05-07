#pragma once
#include "VECTOR2.h"
#include <thread>

#define lpParticle Particle::GetInstance()
#define MAX_SPARK 1000000 // �ΉԂ̍ő�l

struct Spark
{
	int light;
	float x;
	float y;
	float vx;
	float vy;
};

class Particle
{
public:
	// Singleton
	static Particle & GetInstance() {
		return *s_Instance;
	}

	void Create(VECTOR2 pos, int rand);
	void Draw(bool isGravity = false, int Color = -1, bool isCircle = false);

private:

	Particle();
	~Particle();
	struct Particle_deleter	// custom_deleter
	{
		void operator()(Particle* ptr)const {
			delete ptr;
		}
	};
	static std::unique_ptr<Particle, Particle_deleter> s_Instance;

	void Move(bool);
	Spark spark[MAX_SPARK];
};

