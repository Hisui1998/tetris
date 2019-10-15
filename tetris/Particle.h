#pragma once
#include "VECTOR2.h"
#include <thread>
#include <vector>

struct Element
{
	bool isUsed;
	VECTOR2 pos;
	VECTOR2 v;
	int light;
};

class Particle
{
public:
	Particle();
	~Particle();
	void Move(bool);
	void Create(VECTOR2 pos,int rand);
	void Draw(bool isGravity=false);
private:
	void Init();
	const int MAX_SPARK;
	std::vector<Element> particle;
};

