#include "Player.h"
#include "GameBoard.h"
#include "ResultScene.h"
#include "Block.h"
#include <random>

const int blockCnt = 4;
const VECTOR2 offSet = {9 ,0};
const VECTOR2 HoldoffSet = { 9 ,8 };

Player::Player(std::weak_ptr<GameBoard> gb)
{
	NowBlock = -1;
	DxLib::LoadDivGraph("image/blocks.png", 8, 8, 1, BlockSize, BlockSize, blockimg, true);
	WaitCnt = 0;
	this->gb = gb.lock();
	NextMino = MinoSelect();
	ReSet();
	HoldUse = false;
}

Player::~Player()
{
}

Scene Player::UpDate(Scene & _this)
{
	auto rtnptr = std::move(_this);
	if (gb->GetDownCnt())
	{
		return rtnptr;
	}
	bool flag=false;
	WaitCnt++;
	int cnt = 0;
	if (WaitCnt>=WaitCntDef)
	{
		cnt++;
		WaitCnt = 0;
		auto ismove = -4;
		for (auto block : Mino)
		{
			if (gb->PutCheck(block->GetPos()+VECTOR2(0,1)))
			{
				ismove++;
			}
			else
			{
				for (auto block : Mino)
				{
					if (!(gb->PutCheck(block->GetPos())))
					{
						gb->WriteData(block->GetPos(), NowBlock);
						flag = true;
					}
					else
					{
						gb->WriteData(block->GetPos(), NowBlock);
					}
					HoldUse = false;
				}
				if (flag)
				{
					return std::make_unique<ResultScene>(gb);
				}
				ReSet();
				break;
			}
		}
		if (!ismove)
		{
			for (auto block : Mino)
			{
				block->AddPos(VECTOR2(0, 1));
			}
		}
	}
	Move();
	for (auto block : Mino)
	{
		lpParticle.Create(block->GetPos()*BlockSize+BoardOffset+ BlockSize/2,1);
	}
	return  rtnptr;
}

void Player::Draw()
{
	lpParticle.Draw(false,0xffffff);
	auto PhantomCnt = 0;
	for (auto block : Mino)
	{
		DrawGraph(block->GetPos()*BlockSize+BoardOffset, blockimg[NowBlock],true); 
		for (;;)
		{
			auto ismove = -4;
			for (auto block : Mino)
			{
				if ((gb->PutCheck(block->GetPos() + VECTOR2(0, 1)* PhantomCnt)))
				{
					ismove++;
				}
			}
			if (ismove)
			{
				PhantomCnt--;
				break;
			}
			else
			{
				PhantomCnt++;
			}
		}
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0x60);
		DrawGraph((block->GetPos()+VECTOR2(0,1)* PhantomCnt)* BlockSize + BoardOffset, blockimg[NowBlock], true);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0xff);
	}
	for (auto block : NextMino)
	{
		DrawGraph((block->GetPos()+ offSet)*BlockSize + BoardOffset, blockimg[NextBlock], true);
	}
	for (auto block : HoldMino)
	{
		DrawGraph((block->GetPos() + HoldoffSet)*BlockSize + BoardOffset, blockimg[HoldBlock], true);
	}
}

void Player::KeyUpDate()
{
	for (auto i = 0;i<(int)Button::max;i++)
	{
		OldKey[i] = Key[i];
		Key[i] = 0;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		Key[(int)Button::right] = 1;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		Key[(int)Button::left] = 1;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		Key[(int)Button::down] = 1;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		Key[(int)Button::up] = 1;
	}
	if ((CheckHitKey(KEY_INPUT_LSHIFT))|| (CheckHitKey(KEY_INPUT_RSHIFT)))
	{
		Key[(int)Button::shift] = 1;
	}
	if (CheckHitKey(KEY_INPUT_H))
	{
		Key[(int)Button::H] = 1;
	}
}

void Player::Move()
{
	KeyUpDate();

	if ((Key[(int)Button::right] & (~OldKey[(int)Button::right])) == 1)
	{
		auto ismove = -4;
		for (auto block : Mino)
		{
			if ((gb->PutCheck(block->GetPos() + VECTOR2(1, 0))))
			{
				ismove++;
			}
		}
		if (!ismove)
		{
			for (auto block : Mino)
			{
				block->AddPos(VECTOR2(1, 0));
			} 
		}
	}
	if ((Key[(int)Button::left] & (~OldKey[(int)Button::left])) == 1)
	{
		auto ismove = -4;
		for (auto block : Mino)
		{
			if ((gb->PutCheck(block->GetPos() + VECTOR2(-1, 0))))
			{
				ismove++;
			}
		}
		if (!ismove)
		{
			for (auto block : Mino)
			{
				block->AddPos(VECTOR2(-1, 0));
			}
		}
	}
	if ((Key[(int)Button::down] & (~OldKey[(int)Button::down])) == 1)
	{
		auto ismove = -4;
		for (auto block : Mino)
		{
			if ((gb->PutCheck(block->GetPos() + VECTOR2(0, 1))))
			{
				ismove++;
			}
		}
		if (!ismove)
		{
			for (auto block : Mino)
			{
				block->AddPos(VECTOR2(0, 1));
			}
		}
	}
	if ((Key[(int)Button::up] & (~OldKey[(int)Button::up])) == 1)
	{
		for (;;)
		{
			auto ismove = -4;
			for (auto block : Mino)
			{
				if ((gb->PutCheck(block->GetPos() + VECTOR2(0, 1))))
				{
					ismove++;
				}
			}
			if (!ismove)
			{
				for (auto block : Mino)
				{
					if (gb->PutCheck(block->GetPos() + VECTOR2(0, 1)))
					{
						for (auto block : Mino)
						{
							lpParticle.Create(block->GetPos()*BlockSize + BoardOffset + BlockSize / 2, 1);
						}
						block->AddPos(VECTOR2(0, 1));
					}
				}
			}
			else
			{
				WaitCnt = WaitCntDef;
				break;
			}
		}
	}
	if ((Key[(int)Button::shift] & (~OldKey[(int)Button::shift])) == 1)
	{
		Rotation();
	}
	if (((Key[(int)Button::H] & (~OldKey[(int)Button::H])) == 1)&& !HoldUse)
	{
		HoldUse = true;
		if (HoldMino.begin() == HoldMino.end())
		{
			HoldBlock = NowBlock;
			HoldMino = MinoSelect(NowBlock);
			Mino = NextMino;
			NowBlock = NextBlock;
			NextMino = MinoSelect();
		}
		else
		{
			HoldMino = MinoSelect(NowBlock);
			Mino = MinoSelect(HoldBlock);
			auto block = HoldBlock;
			HoldBlock = NowBlock;
			NowBlock = block;
		}
	}
}

void Player::Rotation()
{
	auto ismove = -3;
	for (auto block : Mino)
	{
		int i = 0;
		for (auto d:dir)
		{
			if (block->GetPos() == (*Mino.begin())->GetPos()+d)
			{
				if ((gb->PutCheck(block->GetPos() + -d + rotadir[i])))
				{
					ismove++;
					break;
				}
			}
			else if (block->GetPos() == (*Mino.begin())->GetPos() + d*2)
			{
				if ((gb->PutCheck(block->GetPos() + (-d + rotadir[i]) * 2)))
				{
					ismove++;
					break;
				}
			}
			i++;
		}
	}
	if (!ismove)
	{
		for (auto block : Mino)
		{
			int i = 0;
			for (auto d : dir)
			{
				if (block->GetPos() == (*Mino.begin())->GetPos() + d)
				{
					block->AddPos(-d+rotadir[i]);
					break;
				}
				else if (block->GetPos() == (*Mino.begin())->GetPos() + d * 2)
				{
					block->AddPos((-d + rotadir[i]) * 2);
					break;
				}
				i++;
			}
		}
	}
}

void Player::ReSet()
{
	NowBlock = NextBlock;
	WaitCnt = 0;
	Mino.clear();
	Mino = NextMino;
	NextMino.clear();
	NextMino = MinoSelect();
}

std::vector<std::shared_ptr<Block>> Player::MinoSelect(int isRand)
{	
	std::vector<std::shared_ptr<Block>> seledtedMino;

	std::random_device rd;
	std::mt19937 rand(rd());

	auto selected = [&](std::vector <VECTOR2>pos) {
		for (auto p: pos)
		{
			seledtedMino.push_back(std::make_shared<Block>(p));
		}
	};

	switch ((isRand==-1)?NextBlock = rand() % ((int)MinoType::max - 1) :isRand)
	{
	case (int)MinoType::T_mino:
		selected({ VECTOR2(1, 1) ,VECTOR2(0, 1) ,VECTOR2(2, 1) ,VECTOR2(1, 0) });
		break;
	case (int)MinoType::S_mino:
		selected({ VECTOR2(1, 1) ,VECTOR2(0, 1) ,VECTOR2(2, 0) ,VECTOR2(1, 0) });
		break;
	case (int)MinoType::Z_mino:
		selected({ VECTOR2(1, 1) ,VECTOR2(0, 0) ,VECTOR2(2, 1) ,VECTOR2(1, 0) });
		break;
	case (int)MinoType::L_mino:
		selected({ VECTOR2(1, 1) ,VECTOR2(0, 1) ,VECTOR2(2, 1) ,VECTOR2(2, 0) });
		break;
	case (int)MinoType::J_mino:
		selected({ VECTOR2(1, 1) ,VECTOR2(0, 0) ,VECTOR2(2, 1) ,VECTOR2(0, 1) });
		break;
	case (int)MinoType::I_mino:
		selected({ VECTOR2(1, 1) ,VECTOR2(0, 1) ,VECTOR2(2, 1) ,VECTOR2(3, 1) });
		break;
	case (int)MinoType::O_mino:
		selected({ VECTOR2(1, 1) ,VECTOR2(2, 1) ,VECTOR2(2, 0) ,VECTOR2(1, 0) });
		break;
	default:
		break;
	}

	for (auto block : seledtedMino)
	{
		block->AddPos(VECTOR2(3, 0));
	}
	return seledtedMino;
}

int Player::DrawGraph(VECTOR2 pos,int handle,int Trans)
{
	return DxLib::DrawGraph(pos.x, pos.y, handle, Trans);
}