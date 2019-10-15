#include "Particle.h"
#include <DxLib.h>
#include <amp.h>

std::unique_ptr<Particle, Particle::Particle_deleter> Particle::s_Instance(new Particle());

// 寿命の減る速度
constexpr int lifeSpeed = 5;

// 計算倍率
constexpr int magnification = 50;

// ブロックの大きさ
constexpr int blockSize = 32;

Particle::Particle()
{
	// パーティクル配列の初期化
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
	// ランダムで一回の生成数を取得
	for (int r = 0 ;r < GetRand(rand);r++)
	{
		for (int i = 0;i<particle.size();++i)
		{
			// 死亡状態のパーティクルを検索する
			if (particle[i].lifeSpan > 0)
			{
				continue;
			}

			// 寿命と速度を付与する
			particle[i].pos = pos * magnification;
			(i % 2 ? particle[i].v.x : particle[i].v.y) = (GetRand(20) - 10)*magnification;
			particle[i].lifeSpan = 0xff;
			break;
		}
	}
}

void Particle::Move()
{
	// パーティクルの移動処理
	for (auto& p : particle)
	{
		if (p.lifeSpan <= 0)
		{
			p = { 0,0,0 };
			continue;
		}

		// 移動させた後、寿命を減らす
		p.pos += p.v;
		p.lifeSpan -= lifeSpeed;
	}
}

void Particle::Draw(int Color)
{
	// 座標移動を行う
	Move();

	// 描画実行部
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