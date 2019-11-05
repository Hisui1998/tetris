#pragma once
#include "VECTOR2.h"
#include <thread>
#include <vector>

// インスタンス省略定義
#define lpParticle Particle::GetInstance()
#define MAX_SPARK 10000 // パーティクルの量

// パーティクル個々の情報構造体
struct pInfo
{
	int lifeSpan;
	VECTOR2 pos;
	VECTOR2 v;
};

class Particle
{
public:
	// Singleton
	static Particle & GetInstance() {
		return *s_Instance;
	}

	void Create(VECTOR2 pos, int rand);
	void Draw(int Color = -1);

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

	void Move();

	std::vector<pInfo> particle;
};

