#pragma once
#include <Dxlib.h>
#include <memory>
#include <array>

class VECTOR2;
class SceneState;

// ゲームタスクインスタンスの省略
#define lpGameTask GameTask::GetInstance()

// ゲームタスククラス(ゲームループ関係を処理している)
class GameTask
{
public:
	// Singleton
	static GameTask & GetInstance() {
		return *s_Instance;
	}

	// public関数
	void Run(void);
	VECTOR2 GetScreenSize(void);// ウィンドウサイズを取得する
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

	// シーン遷移用のポインタ
	std::unique_ptr<SceneState> ActiveScene;

	int SysInit(void);
};
