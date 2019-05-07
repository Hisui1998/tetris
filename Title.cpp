#include "Title.h"
#include "GameScene.h"

Title::Title()
{
	Init();
}

Title::~Title()
{
}

int Title::Init()
{
	Titleimg = LoadGraph("image/Title.png",true);
	Key[0]=Key[1] = 1;
	return 0;
}

Scene Title::UpDate(Scene & _this)
{
	Key[1] = Key[0];
	Key[0] = CheckHitKey(KEY_INPUT_RETURN);
	DrawString(0,0,"Title",0xffffff);
	DrawGraph(0,0,Titleimg,true);
	if ((Key[0] & ~Key[1])==1)
	{
		return std::make_unique<GameScene>();
	}
	return  std::move(_this);
}
