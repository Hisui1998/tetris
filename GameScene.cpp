#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"

GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
	StopSoundMem(BGM_mem);
}

int GameScene::Init()
{
	BGM_mem = DxLib::LoadSoundMem("BGM/BGM.mp3");
	DxLib::ChangeVolumeSoundMem(96, BGM_mem);
	DxLib::PlaySoundMem(BGM_mem, DX_PLAYTYPE_LOOP);
	gameboard = std::make_shared<GameBoard>();
	player = std::make_shared<Player>(gameboard);

	isResult = false;
	return 0;
}

Scene GameScene::UpDate(Scene & _this)
{
	DrawString(0, 0, "Game", 0xffffff);
	gameboard->Draw();
	player->Draw();
	gameboard->UpDate();
	return  std::move(player->UpDate(_this));
}
