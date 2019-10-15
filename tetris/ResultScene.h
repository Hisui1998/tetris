#pragma once
#include "SceneState.h"
#include <vector>

// �摜�����A�`��p�̍\����
struct ImgInfo
{
	int buff;// �C���[�W�f�[�^
	VECTOR2 pos;// ���W
	VECTOR2 vec;// ���x
};

// ���U���g�V�[���N���X
class ResultScene :
	public SceneState
{
public:
	ResultScene(std::shared_ptr<GameBoard>);
	~ResultScene();

	int Init();
	Scene UpDate(Scene & _this);
private:
	// �u���b�N���D�F�̃u���b�N�ɕς��Ă����֐�
	void ChangeBlock(bool isEnd);

	// ���̑��ϐ�
	std::shared_ptr<GameBoard> gb;
	int Cnt,y,buffnum,frame;
	char lrKey[2][2];
	bool isEnd,isContinue;
	std::vector<ImgInfo> imgvec;
};
