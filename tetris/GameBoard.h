#pragma once
#include <memory>
#include "Particle.h"

constexpr int BlockSize = 32;
const VECTOR2 BoardSize = VECTOR2(10, 20);
const VECTOR2 offset = VECTOR2(BlockSize * 2, BlockSize * 3);

struct MinoData {
	bool flag = false;
	bool deflag = false;
	int color = 0;
};

class GameBoard
{
public:
	GameBoard();
	~GameBoard();
	void Draw();
	void UpDate();

	bool PutCheck(VECTOR2 pos);
	void WriteData(VECTOR2 pos, int color);
	int GetDownCnt(){ return DownWait; };

private:
	void Init();
	bool LineCheck();
	bool LineClean();
	MinoData Board[20][10];

	std::unique_ptr<Particle> particle;
	int blockimg[8];
	int DownWait;
};

