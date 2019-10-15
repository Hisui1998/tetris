#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "Particle.h"
#include "GameScene.h"
class GameBoard;
class Block;

// �~�m�̎��
enum class MinoType
{
	T_mino,
	S_mino,
	Z_mino,
	L_mino,
	J_mino,
	I_mino,
	O_mino,
	Fin_mino,
	max
};

// �L�[�̖��O
enum class Button
{
	right,
	left,
	down,
	up,
	shift,
	H,
	max
};

// �v���C���[�N���X
class Player
{
public:
	Player(std::weak_ptr<GameBoard>);
	~Player();

	// �X�V����
	Scene UpDate(Scene & _this);

	// �`��p
	void Draw();

	// ������܂ł̃E�F�C�g�������镔��
	void SetWaitCnt(int i) { WaitCntDef += i; };
private:
	// �L�[�����̍X�V
	void KeyUpDate();

	// �ړ�����
	void Move();

	// ��]����
	void Rotation();

	// ���Z�b�g�֐��i�~�m�̓���ւ��j
	void ReSet();

	// �~�m�̃����_���Z���N�g
	std::vector<std::shared_ptr<Block>> MinoSelect(int isRand = -1);

	// �e�~�m�̃u���b�N�z��
	std::vector<std::shared_ptr<Block>> Mino;
	std::vector<std::shared_ptr<Block>> NextMino;
	std::vector<std::shared_ptr<Block>> HoldMino;

	// �~�m�̎��
	int NowBlock;
	int NextBlock;
	int HoldBlock;

	// �L�[�̓��͏����m�ۂ��Ă����ϐ�
	char Key[(int)Button::max],OldKey[(int)Button::max];

	// �摜���
	int blockimg[(int)MinoType::max];

	// �E�F�C�g�p
	int WaitCnt;
	int WaitCntDef = 30;

	// �ǂݍ���SE���i�[����ϐ�
	int SE_mem;

	// �z�[���h�L�[���g�p���Ă����Ԃ��ǂ���������t���O
	bool HoldUse;

	// ��]�p�ϐ�
	const VECTOR2 dir[8] = { { -1,-1 },{ 0,-1 },{ 1,-1 },{ 1,0 } ,{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 } };
	const VECTOR2 rotadir[8] = { { 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 } ,{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 } };
	
	// �Q�[���{�[�h�ւ̃|�C���^
	std::shared_ptr<GameBoard> gb;

	// DrawGraph��Vector2���g�p�\�ɂ��邽��
	int DrawGraph(VECTOR2 pos, int handle, int Trans);
};
