#include "ResultScene.h"
#include "Title.h"
#include "GameBoard.h"

ResultScene::ResultScene(std::shared_ptr<GameBoard> gb)
{
	this->gb = gb;
	Init();
}

ResultScene::~ResultScene()
{
}

int ResultScene::Init()
{
	Cnt = 0;
	y = 20;
	Key[1] = 1;
	return 0;
}

Scene ResultScene::UpDate(Scene & _this)
{
	Cnt++;
	Key[1] = Key[0];
	Key[0] = CheckHitKey(KEY_INPUT_RETURN);
	DrawString(0, 0, "‚è‚´‚é‚Æ", 0xffffff);
	if (((Cnt / 5) % 2)&&(y))
	{
		y--;
		Cnt = 0;
		for (int x = 0; x < BoardSize.x; x++)
		{
			if (!gb->PutCheck(VECTOR2(x, y)))
			{
				for (int fin = 0; fin < BoardSize.x; fin++)
				{
					if (!gb->PutCheck(VECTOR2(fin, y)))
					{
						gb->WriteData(VECTOR2(fin, y), 7);
					}
				}
				break;
			}
		}
	}
	else if ((Key[0] & ~Key[1]) == 1)
	{
		auto testGraph= MakeGraph(BlockSize*BoardSize.x, BlockSize*BoardSize.y);
		GetDrawScreenGraph(offset.x, offset.y, BlockSize*BoardSize.x+ offset.x, BlockSize*BoardSize.y+ offset.y, testGraph);
		DrawGraph(0,0, testGraph,true);
		return std::make_unique<Title>();
	}

	gb->Draw();
	return  std::move(_this);
}
