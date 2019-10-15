#pragma once
#include "SceneState.h"
#include <vector>

struct Buffer
{
	int buff;
	VECTOR2 pos;
	VECTOR2 vec;
};

class ResultScene :
	public SceneState
{
public:
	ResultScene(std::shared_ptr<GameBoard>);
	~ResultScene();

	int Init();
	Scene UpDate(Scene & _this);
private:
	void ChangeBlock(bool isEnd);
	std::shared_ptr<GameBoard> gb;
	int Cnt,y,buffnum;
	char lrKey[2][2];
	bool isEnd,isContinue;
	std::vector<Buffer> buff;
};
