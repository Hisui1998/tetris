#include "GameBoard.h"
#include "VECTOR2.h"
#include <DxLib.h>
#include <vector>


GameBoard::GameBoard()
{
	Init();
}


GameBoard::~GameBoard()
{
}

void GameBoard::Init()
{
	DownWait = 0;
	for (auto y = 0; y < BoardSize.y; y++)
	{
		for (auto x = 0; x < BoardSize.x; x++)
		{
			Board[y][x].flag = false;
		}
		Board[3][0].flag = false;
	}
	particle = std::make_unique<Particle>();
	DxLib::LoadDivGraph("image/blocks.png",8,8,1, BlockSize, BlockSize, blockimg,true);
}

// �󂢂Ă�󂢂ĂȂ��Ɋւ�炸������Ă���s�����邩�̃`�F�b�N����֐�
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

// �s����������~�낵���肵�Đ��񂳂���֐�
bool GameBoard::LineClean()
{	
	bool isDel = false, isDown = false;
	std::vector<int> DelLines,DownLine;

	// �����̂��~�낷�̂��̔���
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

	// ���s����
	if (isDel)
	{
		if (++DownWait >= 30)
		{
			for (auto dl : DelLines)
			{
				for (auto x = 0; x < BoardSize.x; x++)
				{
					particle->Create(VECTOR2(x, dl)*BlockSize + offset + BlockSize / 2, 300);
					Board[dl][x].flag = false;
				}
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
	DxLib::DrawBox(offset.x- BlockSize, offset.y - BlockSize, offset.x+BlockSize*(BoardSize.x + 1), offset.y+BlockSize*(BoardSize.y + 1), 0xcccccc, true);
	DxLib::DrawBox(offset.x, offset.y, offset.x+BlockSize*(BoardSize.x), offset.y+BlockSize*(BoardSize.y),0,true);
	// �u���b�N������Ƃ���ɕ`�������
	for (auto y = 0; y < BoardSize.y; y++)
	{
		for (auto x = 0; x < BoardSize.x; x++)
		{
			if (Board[y][x].flag)
			{
				if (Board[y][x].deflag)
				{
					DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
				}
				DxLib::DrawGraph(offset.x+x*BlockSize, offset.y+y*BlockSize, blockimg[Board[y][x].color],true);
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
		}
	}
	particle->Draw();
}

void GameBoard::UpDate()
{
	if (LineCheck())
	{
		LineClean();
	}
}

// �����ł���������W�Ƀu���b�N���u���邩�ǂ���(�u���b�N�̗L��)��Ԃ��֐�
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
				particle->Create(VECTOR2(pos.x, pos.y)*BlockSize + offset + BlockSize / 2, 1);
			}
		}
	}
}
