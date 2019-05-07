#pragma once
#include "VECTOR2.h"
class Block
{
public:
	Block(VECTOR2 pos);
	~Block();
	void AddPos(VECTOR2 pos);
	void SetPos(VECTOR2 pos);
	VECTOR2 GetPos();
private:
	VECTOR2 pos;
};

