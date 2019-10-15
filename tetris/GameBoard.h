#pragma once
#include <memory>
#include "Particle.h"

constexpr int BlockSize = 32;
constexpr int LineSize = 10;
const VECTOR2 BoardSize = VECTOR2(10, 20);
const VECTOR2 BoardOffset = VECTOR2(BlockSize * 2, BlockSize * 3);
const VECTOR2 NextOffset = VECTOR2(BlockSize * 14, BlockSize * 3);
const VECTOR2 HoldOffset = VECTOR2(BlockSize * 14, BlockSize * 11);

// �~�m�Ɋ܂܂����
struct MinoData {
	bool flag = false;
	bool deflag = false;
	int color = 0;
};

// �Q�[���{�[�h�N���X(���ۂɃ~�m�������Ă�����������肷��ꏊ)
class GameBoard
{
public:
	GameBoard();
	~GameBoard();
	
	void Draw();// �`��
	void UpDate();// �X�V

	// �����ł���������W�Ƀu���b�N���u���邩�ǂ���(�u���b�N�̗L��)��Ԃ��֐�
	bool PutCheck(VECTOR2 pos);

	// �f�[�^���������ފ֐�
	void WriteData(VECTOR2 pos, int color);

	// ������܂ł̃J�E���g���擾����֐�
	int GetDownCnt(){ return DownWait; };

private:
	// ������
	void Init();

	// ���C������
	bool LineCheck();// ���u���b�N��������Ă��邩�ǂ����̃`�F�b�N
	bool LineClean();// ���ɂ�������u���b�N�������֐�

	// �{�[�h�{�̂̃f�[�^�z��
	MinoData Board[20][10];

	// �u���b�N�̉摜�f�[�^�i�[�p
	int blockimg[8];

	// ���̑��ϐ�
	int Create;
	int DownWait,DrawWait;
	int Score;
};

