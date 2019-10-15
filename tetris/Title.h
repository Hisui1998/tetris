#pragma once
#include "SceneState.h"

// タイトルシーン
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
	int cnt;
};

