#include "GameBoard.h"
#include "VECTOR2.h"
#include <DxLib.h>
#include <vector>

constexpr int FontSize = 24;
constexpr int BlockCnt = 4;
constexpr int Second = 60;

GameBoard::GameBoard()
{
	Init();
}


GameBoard::~GameBoard()
{
}

void GameBoard::Init()
{
	Score = 0;
	DownWait = 0;
	DrawWait = 0;
	Create = 0;
	for (auto y = 0; y < BoardSize.y; y++)
	{
		for (auto x = 0; x < BoardSize.x; x++)
		{
			Board[y][x].flag = false;
		}
		Board[3][0].flag = false;
	}
	DxLib::LoadDivGraph("image/blocks.png",8,8,1, BlockSize, BlockSize, blockimg,true);
}

// 空いてる空いてないに関わらずそろっている行があるかのチェックする関数
bool GameBoard::LineCheck()
{	
	bool rtnflag = false;
	for (auto y = 0; y < BoardSize.y; y++)
	{
		for (auto x = 1; x< BoardSize.x;x++)
		{
			if (Board[y][x-1].flag!=Board[y][x].flag)
			{
				break;
			}
			else if (x==BoardSize.x-1)
			{
				rtnflag = true;
			}
		}
	}
	return rtnflag;
}

// 行を消したり降ろしたりして整列させる関数
bool GameBoard::LineClean()
{	
	bool isDel = false, isDown = false;
	std::vector<int> DelLines,DownLine;

	// 消すのか降ろすのかの判定
	for (auto y = 0; y < BoardSize.y; y++)
	{
		for (auto x = 1; x < BoardSize.x; x++)
		{
			if (Board[y][x - 1].flag != Board[y][x].flag)
			{
				break;
			}
			else if (x == BoardSize.x - 1)
			{
				if (Board[y][x-1].flag)
				{
					isDel = true; 
					for (auto x2 = 0; x2 < BoardSize.x; x2++)
					{
						Board[y][x2].deflag = true;
					}
					DelLines.push_back(y);
				}
				else
				{
					isDown = true;
					DownLine.clear();
					DownLine.push_back(y);
				}
			}
		}
	}

	// 実行部分
	if (isDel)
	{
		if (++DownWait >= 30)
		{
			for (auto dl : DelLines)
			{
				for (auto x = 0; x < BoardSize.x; x++)
				{
					lpParticle.Create(VECTOR2(x, dl)*BlockSize + BoardOffset + BlockSize / 2, 300);
					Board[dl][x].flag = false;
				}
				Score += 1000;
			}
			if (DelLines.size() == BlockCnt)
			{
				DrawWait = Second;
				Score += 10000;
			}
		}
	}
	else if (isDown)
	{
		for (auto y = *DownLine.begin(); y > 0; y--)
		{
			for (auto x = 0; x < BoardSize.x; x++)
			{
				Board[y][x] = Board[y - 1][x];
			}
		}
		DownWait = 0;
	}
	return true;
}

void GameBoard::Draw()
{
	auto FontChanger = [](const char Fontname[] = "",const int Fontsize = 16,bool isAntialiasing=false) {
		DxLib::ChangeFont(Fontname);
		DxLib::SetFontSize(Fontsize);
		isAntialiasing ? DxLib::ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE): DxLib::ChangeFontType(DX_FONTTYPE_NORMAL);
	};
	DxLib::DrawBox(BoardOffset.x- BlockSize, BoardOffset.y - BlockSize, BoardOffset.x+BlockSize*(BoardSize.x + 1), BoardOffset.y+BlockSize*(BoardSize.y + 1), 0xaaccaa, true);
	DxLib::DrawBox(BoardOffset.x, BoardOffset.y, BoardOffset.x+BlockSize*(BoardSize.x), BoardOffset.y+BlockSize*(BoardSize.y),0,true);
	DxLib::DrawBox(NextOffset.x - LineSize, NextOffset.y - LineSize, NextOffset.x+ BlockSize*4+ LineSize, NextOffset.y + BlockSize * 3+ LineSize,0xffcccc,true);
	DxLib::DrawBox(NextOffset.x, NextOffset.y, NextOffset.x + BlockSize * 4, NextOffset.y + BlockSize * 3, 0, true);
	DxLib::DrawBox(HoldOffset.x - LineSize, HoldOffset.y - LineSize, HoldOffset.x + BlockSize * 4 + LineSize, HoldOffset.y + BlockSize * 3 + LineSize, 0xffccff, true);
	DxLib::DrawBox(HoldOffset.x, HoldOffset.y, HoldOffset.x + BlockSize * 4, HoldOffset.y + BlockSize * 3, 0, true);

	lpParticle.Draw();
	FontChanger("Comic Sans MS", FontSize,true);
	DxLib::DrawString(NextOffset.x - LineSize, NextOffset.y - BlockSize- LineSize, "NextBlock", 0xaaaaff, 0xffffff);
	DxLib::DrawString(HoldOffset.x - LineSize, HoldOffset.y - BlockSize - LineSize, "HoldBlock", 0xaaffff);
	DxLib::DrawString(HoldOffset.x, HoldOffset.y+ BoardOffset.y+LineSize, "Score", 0xaaffff, 0xffffff);
	DrawFormatString(HoldOffset.x, HoldOffset.y + BoardOffset.y + LineSize+FontSize, 0xaaffff,"%d",Score);
	


	// ブロックがあるところに描画をする
	for (auto y = 0; y < BoardSize.y; y++)
	{
		for (auto x = 0; x < BoardSize.x; x++)
		{
			if (Board[y][x].flag)
			{
				if ((Board[y][x].deflag)&& ((DownWait/5)%2))
				{
					DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
				}
				DxLib::DrawGraph(BoardOffset.x+x*BlockSize, BoardOffset.y+y*BlockSize, blockimg[Board[y][x].color],true);
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
		}
	}
	if ((--DrawWait > 0) && ((DrawWait / 10) % 2))
	{
		DxLib::SetFontSize(FontSize * 2);
		DxLib::DrawString(BoardOffset.x + (BlockSize * (BoardSize.x) + 12 * FontSize*2) / 2, (BlockSize * (BoardSize.y) + FontSize / 2) / 2,
			"T E T R I S", 0xffaaaa, 0xffffff);
	}
	FontChanger();
}

void GameBoard::UpDate()
{
	if (LineCheck())
	{
		LineClean();
	}
}

// 引数でもらった座標にブロックが置けるかどうか(ブロックの有無)を返す関数
bool GameBoard::PutCheck(VECTOR2 pos)
{
	bool rtnFlag = false;
	if ((pos.x < BoardSize.x) && (pos.x >= 0) && (pos.y < BoardSize.y) && (pos.y >= 0))
	{
		if (!Board[pos.y][pos.x].flag)
		{
			rtnFlag = true;
		}
	}
	return rtnFlag;
}

void GameBoard::WriteData(VECTOR2 pos,int color)
{
	Board[pos.y][pos.x].flag = true;
	Board[pos.y][pos.x].color = color;
	for (auto y = 0; y < BoardSize.y; y++)
	{
		for (auto x = 0; x < BoardSize.x; x++)
		{
			if (Board[pos.y][pos.x].color == 7)
			{
				lpParticle.Create(VECTOR2(pos.x, pos.y)*BlockSize + BoardOffset + BlockSize / 2, (++Create/30)%2);
			}
		}
	}
}
