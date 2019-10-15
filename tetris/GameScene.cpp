#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"

GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
	StopMusic();
}

int GameScene::Init()
{
	DxLib::PlayMusic("BGM/BGM.mp3", DX_PLAYTYPE_LOOP);
	Key[0] = 0;
	Key[1] = 0;
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
