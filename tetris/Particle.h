#pragma once
#include "VECTOR2.h"
#include <thread>
#include <vector>

// �C���X�^���X�ȗ���`
#define lpParticle Particle::GetInstance()
#define MAX_SPARK 10000 // �p�[�e�B�N���̗�

// �p�[�e�B�N���X�̏��\����
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

