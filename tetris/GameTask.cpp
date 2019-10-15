#include "GameTask.h"
#include "VECTOR2.h"
#include "Title.h"

#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 800

std::unique_ptr<GameTask, GameTask::gametask_deleter> GameTask::s_Instance(new GameTask());

GameTask::GameTask()
{
	VECTOR2 mouse = { 0,0 };
	POINT mouse_p = { 0,0 };
	SysInit();
}

GameTask::~GameTask()
{
}

VECTOR2 GameTask::GetScreenSize(void)
{
	return VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

int GameTask::SysInit(void)
{
	DxLib::SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1701337_à‰è„îÚêÅ::Tetris");
	if (DxLib::DxLib_Init() == -1)	// DxLibÇÃèâä˙âª
	{
		return -1;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	return 0;
}

void GameTask::Run(void)
{
	ActiveScene = std::make_unique<Title>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		DxLib::ClsDrawScreen();
		ActiveScene = std::move(ActiveScene->UpDate(ActiveScene));
		DxLib::ScreenFlip();
	}
	DxLib::DxLib_End();	// DxLibÇÃèIóπ
}
