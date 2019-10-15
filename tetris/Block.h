#pragma once
#include "VECTOR2.h"

// ブロック個々のクラス
class Block
{
public:
	Block(VECTOR2 pos);
	~Block();

	void AddPos(VECTOR2 pos);// 現在の座標に加算する
	void SetPos(VECTOR2 pos);// 座標を再設定する
	VECTOR2 GetPos();// 座標を取得する
private:
	VECTOR2 pos;// 座標
};

