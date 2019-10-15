#pragma once
#include <Dxlib.h>
#include <memory>
#include <array>

class VECTOR2;
class SceneState;

#define lpGameTask GameTask::GetInstance()

class GameTask
{
public:
	// Singleton
	static GameTask & GetInstance() {
		return *s_Instance;
	}

	// publicä÷êî
	void Run(void);
	VECTOR2 GetScreenSize(void);
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

	std::unique_ptr<SceneState> ActiveScene;

	// SystemInitialize
	int SysInit(void);
	// ïœêî

};
