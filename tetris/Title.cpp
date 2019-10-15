#include "Title.h"
#include "GameScene.h"
#include <string>

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
	Key[1] = 1;
	cnt = 0;
	return 0;
}

Scene Title::UpDate(Scene & _this)
{
	int x, y;
	GetWindowSize(&x,&y);
	char str[] = "Press enter to play the game !!";
	Key[1] = Key[0];
	Key[0] = CheckHitKey(KEY_INPUT_RETURN);
	DrawGraph(0,0,Titleimg,true);
	if ((Key[0] & ~Key[1])==1)
	{
		DrawString(x / 2 - 256, y * 3 / 4, str, 0x80c0ff);
		DxLib::ChangeFontType(DX_FONTTYPE_NORMAL);
		DxLib::SetFontSize(16);
		return std::make_unique<GameScene>();
	}
	DxLib::ChangeFont("Comic Sans MS");
	DxLib::SetFontSize(32);
	DxLib::ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	if ((++cnt/30)%2)
	{
		DrawString(x/2-256, y*3/4, str, 0x80c0ff);
	}
	return  std::move(_this);
}
