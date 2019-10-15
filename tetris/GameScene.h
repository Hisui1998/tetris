#pragma once
#include "SceneState.h"
class GameBoard;
class Player;

// ゲームシーンクラス
class GameScene :
	public SceneState
{
public:
	GameScene();
	~GameScene();

	int Init();// 初期化
	Scene UpDate(Scene & _this);// 更新
private:
	std::shared_ptr<GameBoard> gameboard;// ゲームボードへのポインタ
	std::shared_ptr<Player> player;// プレイヤーへのポインタ

	// その他変数
	VECTOR2 boardSize;
	bool isResult;
	int BGM_mem;
};

