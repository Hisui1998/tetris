#include "ResultScene.h"
#include "Title.h"
#include "GameBoard.h"
#include "GameScene.h"

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
	for (int y = 0; y < BoardSize.y; y++)
	{
		for (int x = 0; x < BoardSize.x; x++)
		{
			if (!gb->PutCheck(VECTOR2(x, y)))
			{
				buff.push_back({ MakeGraph(BlockSize, BlockSize), VECTOR2(x, y),VECTOR2((GetRand(2)-1),-GetRand(10)) });
			}
		}
	}
	Cnt = 1;
	buffnum = 0;
	y = 20;
	isEnd = false;
	isContinue = false;
	Key[0] = 0;
	lrKey[0][0] = lrKey[1][0] = 0;
	return 0;
}

Scene ResultScene::UpDate(Scene & _this)
{
	auto FontChanger = [](const char Fontname[] = "", const int Fontsize = 16, bool isAntialiasing = false) {
		DxLib::ChangeFont(Fontname);
		DxLib::SetFontSize(Fontsize);
		isAntialiasing ? DxLib::ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE) : DxLib::ChangeFontType(DX_FONTTYPE_NORMAL);
	};

	Key[1] = Key[0];
	lrKey[0][1] = lrKey[0][0];
	lrKey[1][1] = lrKey[1][0];

	lrKey[0][0] = CheckHitKey(KEY_INPUT_RIGHT);
	lrKey[1][0] = CheckHitKey(KEY_INPUT_LEFT);

	Key[0] = CheckHitKey(KEY_INPUT_RETURN);
	DrawString(0, 0, "Result", 0xffffff);

	ChangeBlock(isEnd);
	gb->Draw();

	FontChanger("Comic Sans MS", 64, true);
	if (((Key[0] & ~Key[1]) == 1)&&(y==0))
	{
		if (!isEnd)
		{
			isEnd = true;
			Cnt = 2;
			for (auto img:buff)
			{
				GetDrawScreenGraph(BoardOffset.x + BlockSize * img.pos.x, BoardOffset.y + BlockSize * img.pos.y,
					BoardOffset.x + BlockSize * img.pos.x + BlockSize, BoardOffset.y + BlockSize * img.pos.y + BlockSize, img.buff, true);
			}
			
			buffnum = 0;
			//return std::make_unique<Title>();
		}
		else
		{
			FontChanger();
			if (isContinue)
			{
				return std::make_unique<GameScene>();
			}
			return std::make_unique<Title>();
		}
	}
	if (isEnd)
	{
		for (auto &img : buff)
		{
			DrawGraphF(BoardOffset.x + BlockSize * img.pos.x, BoardOffset.y + BlockSize * img.pos.y, img.buff, true);
			img.pos += img.vec;
			img.vec.y+=1;
		}
		if ((lrKey[0][1] & ~lrKey[0][0]) == 1)
		{
			isContinue = false;
		}
		if ((lrKey[1][1] & ~lrKey[1][0]) == 1)
		{
			isContinue = true;
		}
		Cnt++;
		int fontsize;
		DrawString(BoardOffset.x + (BlockSize*BoardSize.x) / 2-32*5, BoardOffset.y + (BlockSize*(BoardSize.x)) / 2, "Continue?", 0xffffff);
		DxLib::SetFontSize(fontsize = isContinue ? (64 + abs(Cnt /2 % 20 - 10)) : 32);
		DrawString(BoardOffset.x + (BlockSize*BoardSize.x) / 2 - 3 * fontsize, BoardOffset.y + (BlockSize*BoardSize.x) / 2 + 64*2, "YES", isContinue ? 0xff99ff : 0xffffff);
		DxLib::SetFontSize(fontsize = !isContinue ? (64 + abs(Cnt /2 % 20 - 10)) : 32);
		DrawString(BoardOffset.x + (BlockSize*BoardSize.x) / 2 + 1 * fontsize, BoardOffset.y + (BlockSize*BoardSize.x) / 2 + 64*2, "NO", isContinue?0xffffff:0xff99ff);
	}
	else
	{
		FontChanger("Comic Sans MS", 64, true);
		DrawString(BoardOffset.x+(BlockSize*BoardSize.x)/2 - 32 * 5, BoardOffset.y+ (BlockSize*BoardSize.x) / 2, "Game Over", 0xffffff);
	}

	FontChanger();

	return  std::move(_this);
}

void ResultScene::ChangeBlock(bool isEnd)
{
	if (isEnd)
	{
		int score = gb->GetScore();
		gb = std::make_unique<GameBoard>(score);
	}
	else if (((++Cnt / 5) % 2) && (y))
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
}
