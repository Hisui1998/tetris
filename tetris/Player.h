#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "Particle.h"
#include "GameScene.h"
class GameBoard;
class Block;

enum class MinoType
{
	T_mino,
	S_mino,
	Z_mino,
	L_mino,
	J_mino,
	I_mino,
	O_mino,
	Fin_mino,
	max
};

enum class Button
{
	right,
	left,
	down,
	up,
	shift,
	H,
	max
};

class Player
{
public:
	Player(std::weak_ptr<GameBoard>);
	~Player();
	Scene UpDate(Scene & _this);
	void Draw();
	void SetWaitCnt(int i) { WaitCntDef += i; };
private:
	void KeyUpDate();
	void Move();
	void Rotation();
	void ReSet();

	std::vector<std::shared_ptr<Block>> MinoSelect(bool flag = true);

	std::vector<std::shared_ptr<Block>> Mino;
	std::vector<std::shared_ptr<Block>> NextMino;
	std::vector<std::shared_ptr<Block>> HoldMino;

	char Key[(int)Button::max],OldKey[(int)Button::max];
	int blockimg[(int)MinoType::max];
	int WaitCnt;
	int WaitCntDef = 30;

	int NowBlock;
	int NextBlock;
	int HoldBlock;
	std::unique_ptr<Particle> paeticle;
	const VECTOR2 dir[8] = { { -1,-1 },{ 0,-1 },{ 1,-1 },{ 1,0 } ,{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 } };
	const VECTOR2 rotadir[8] = { { 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 } ,{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 } };
	std::shared_ptr<GameBoard> gb;
	int DrawGraph(VECTOR2 pos, int handle, int Trans);
};
