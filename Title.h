#pragma once
#include "SceneState.h"

class Title :
	public SceneState
{
public:
	Title();
	~Title();

	int Init();
	Scene UpDate(Scene & _this);
private:
	int Titleimg;
};

