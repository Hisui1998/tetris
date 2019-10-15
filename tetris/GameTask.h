#pragma once
#include <Dxlib.h>
#include <memory>
#include <array>

class VECTOR2;
class SceneState;

// �Q�[���^�X�N�C���X�^���X�̏ȗ�
#define lpGameTask GameTask::GetInstance()

// �Q�[���^�X�N�N���X(�Q�[�����[�v�֌W���������Ă���)
class GameTask
{
public:
	// Singleton
	static GameTask & GetInstance() {
		return *s_Instance;
	}

	// public�֐�
	void Run(void);
	VECTOR2 GetScreenSize(void);// �E�B���h�E�T�C�Y���擾����
private:
	// Singleton
	GameTask();
	~GameTask();
	struct gametask_deleter	// custom_deleter
	{
		void operator()(GameTask * gameptr)const{
			delete gameptr;
		}
	};
	static std::unique_ptr<GameTask,gametask_deleter> s_Instance;

	// �V�[���J�ڗp�̃|�C���^
	std::unique_ptr<SceneState> ActiveScene;

	int SysInit(void);
};
