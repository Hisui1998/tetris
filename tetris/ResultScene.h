#pragma once
#include "SceneState.h"

class ResultScene :
	public SceneState
{
public:
	ResultScene(std::shared_ptr<GameBoard>);
	~ResultScene();

	int Init();
	Scene UpDate(Scene & _this);
private:
	std::shared_ptr<GameBoard> gb;
	int Cnt,y;
};
