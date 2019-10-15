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
				imgvec.push_back({ MakeGraph(BlockSize, BlockSize), VECTOR2(x, y),VECTOR2(GetRand(100)-50,GetRand(100)) });
			}
		}
	}
	frame = 0;
	Cnt = 1;
	buffnum = 0;
	y = 20;
	isEnd = false;
	isContinue = false;
	Key[1] = 1;
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
	++frame;
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
			for (auto img:imgvec)
			{
				GetDrawScreenGraph(BoardOffset.x + BlockSize * img.pos.x, BoardOffset.y + BlockSize * img.pos.y,
					BoardOffset.x + BlockSize * img.pos.x + BlockSize, BoardOffset.y + BlockSize * img.pos.y + BlockSize, img.buff, true);
			}			
			buffnum = 0;
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
		for (auto &img : imgvec)
		{
			DrawGraph(BoardOffset.x + BlockSize * img.pos.x, BoardOffset.y + BlockSize * img.pos.y, img.buff, true);
			img.pos += img.vec/20;
			img.vec.y++;
		}
		if ((lrKey[0][1] & ~lrKey[0][0]) == 1)
		{
			isContinue = false;
		}
		if ((lrKey[1][1] & ~lrKey[1][0]) == 1)
		{
			isContinue = true;
		}
		auto fontsize = isContinue ? 64 : 32;
		DrawString(300 - 5 * 32, 400 - 64, "Continue?", 0xffffff);
		DxLib::SetFontSize(fontsize);
		DrawString(300 - 3 * fontsize, 400 + 64, "YES", 0xffffff);
		fontsize = isContinue ? 32 : 64;
		DxLib::SetFontSize(fontsize);
		DrawString(300 + 2 * fontsize, 400 + 64, "NO", 0xffffff);
	}
	else
	{
		FontChanger("Comic Sans MS", 64, true);
		DrawString(300 - 5 * 32, 400 - 64 * 2, "Game Over", 0xffffff);
		FontChanger("Comic Sans MS", 32, true);
		if ((frame / 30) % 2)
		{
			DrawString(300 - 16 * 16, 400, "Press enter to break the blocks", 0xffffff);
		}
	}

	FontChanger();

	return  std::move(_this);
}

void ResultScene::ChangeBlock(bool isEnd)
{
	if (isEnd)
	{
		gb = std::make_unique<GameBoard>();
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
