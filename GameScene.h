#pragma once
#include "SceneState.h"
class GameBoard;
class Player;

class GameScene :
	public SceneState
{
public:
	GameScene();
	~GameScene();

	int Init();
	Scene UpDate(Scene & _this);
private:
	std::shared_ptr<GameBoard> gameboard;
	std::shared_ptr<Player> player;

	VECTOR2 boardSize;
	bool isResult;
	int BGM_mem;
};

