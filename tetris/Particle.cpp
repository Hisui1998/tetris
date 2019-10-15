#include "Particle.h"
#include <DxLib.h>
#include <amp.h>

std::unique_ptr<Particle, Particle::Particle_deleter> Particle::s_Instance(new Particle());

// �����̌��鑬�x
constexpr int lifeSpeed = 5;

// �v�Z�{��
constexpr int magnification = 50;

// �u���b�N�̑傫��
constexpr int blockSize = 32;

Particle::Particle()
{
	// �p�[�e�B�N���z��̏�����
	particle.resize(MAX_SPARK);
	for (auto& p :particle)
	{
		p = {0,0,0};
	}
}


Particle::~Particle()
{
}

void Particle::Create(VECTOR2 pos,int rand)
{
	// �����_���ň��̐��������擾
	for (int r = 0 ;r < GetRand(rand);r++)
	{
		for (int i = 0;i<particle.size();++i)
		{
			// ���S��Ԃ̃p�[�e�B�N������������
			if (particle[i].lifeSpan > 0)
			{
				continue;
			}

			// �����Ƒ��x��t�^����
			particle[i].pos = pos * magnification;
			(i % 2 ? particle[i].v.x : particle[i].v.y) = (GetRand(20) - 10)*magnification;
			particle[i].lifeSpan = 0xff;
			break;
		}
	}
}

void Particle::Move()
{
	// �p�[�e�B�N���̈ړ�����
	for (auto& p : particle)
	{
		if (p.lifeSpan <= 0)
		{
			p = { 0,0,0 };
			continue;
		}

		// �ړ���������A���������炷
		p.pos += p.v;
		p.lifeSpan -= lifeSpeed;
	}
}

void Particle::Draw(int Color)
{
	// ���W�ړ����s��
	Move();

	// �`����s��
	for (auto& p : particle)
	{
		if (p.lifeSpan > 0)
		{
			DrawBox(p.pos.x / magnification - blockSize/2, p.pos.y / magnification - blockSize/2,
					p.pos.x / magnification + blockSize/2, p.pos.y / magnification + blockSize/2,
				(Color == -1) ? GetColor(p.lifeSpan, 0, 0) : GetColor(p.lifeSpan/0xffff*Color, (p.lifeSpan / 0xff)% 0xffff * Color, p.lifeSpan%0xff * Color), false);
		}
	}
}