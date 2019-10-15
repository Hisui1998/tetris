#pragma once
#include "DxLib.h"
#include "VECTOR2.h"
#include "GameBoard.h"
#include <array>

class SceneState;

using  Scene = std::unique_ptr<SceneState>;

// シーンの仮想クラス
class SceneState
{
public:
	virtual ~SceneState();
	virtual int Init()=0;
	virtual Scene UpDate(Scene & _this) = 0;

	// キー入力用
	unsigned char Key[2];
	unsigned char OldKey[2];
};

