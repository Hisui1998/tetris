#pragma once
#include "DxLib.h"
#include "VECTOR2.h"
#include "GameBoard.h"
#include <array>

class SceneState;

using  Scene = std::unique_ptr<SceneState>;

// �V�[���̉��z�N���X
class SceneState
{
public:
	virtual ~SceneState();
	virtual int Init()=0;
	virtual Scene UpDate(Scene & _this) = 0;

	// �L�[���͗p
	unsigned char Key[2];
	unsigned char OldKey[2];
};

