#pragma once
#include "SceneState.h"
class GameBoard;
class Player;

// �Q�[���V�[���N���X
class GameScene :
	public SceneState
{
public:
	GameScene();
	~GameScene();

	int Init();// ������
	Scene UpDate(Scene & _this);// �X�V
private:
	std::shared_ptr<GameBoard> gameboard;// �Q�[���{�[�h�ւ̃|�C���^
	std::shared_ptr<Player> player;// �v���C���[�ւ̃|�C���^

	// ���̑��ϐ�
	VECTOR2 boardSize;
	bool isResult;
	int BGM_mem;
};

