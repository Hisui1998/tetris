#pragma once
#include "VECTOR2.h"

// �u���b�N�X�̃N���X
class Block
{
public:
	Block(VECTOR2 pos);
	~Block();

	void AddPos(VECTOR2 pos);// ���݂̍��W�ɉ��Z����
	void SetPos(VECTOR2 pos);// ���W���Đݒ肷��
	VECTOR2 GetPos();// ���W���擾����
private:
	VECTOR2 pos;// ���W
};

