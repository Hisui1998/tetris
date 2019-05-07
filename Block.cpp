#include "Block.h"



Block::Block(VECTOR2 pos)
{
	this->pos = pos;
}


Block::~Block()
{
}

void Block::AddPos(VECTOR2 pos)
{
	this->pos += pos;
}

void Block::SetPos(VECTOR2 pos)
{
	this->pos = pos;
}

VECTOR2 Block::GetPos()
{
	return pos;
}
