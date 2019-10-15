#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "Particle.h"
#include "GameScene.h"
class GameBoard;
class Block;

// ミノの種類
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

// キーの名前
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

// プレイヤークラス
class Player
{
public:
	Player(std::weak_ptr<GameBoard>);
	~Player();

	// 更新処理
	Scene UpDate(Scene & _this);

	// 描画用
	void Draw();

	// 落ちるまでのウェイトがかかる部分
	void SetWaitCnt(int i) { WaitCntDef += i; };
private:
	// キー処理の更新
	void KeyUpDate();

	// 移動処理
	void Move();

	// 回転処理
	void Rotation();

	// リセット関数（ミノの入れ替え）
	void ReSet();

	// ミノのランダムセレクト
	std::vector<std::shared_ptr<Block>> MinoSelect(int isRand = -1);

	// 各ミノのブロック配列
	std::vector<std::shared_ptr<Block>> Mino;
	std::vector<std::shared_ptr<Block>> NextMino;
	std::vector<std::shared_ptr<Block>> HoldMino;

	// ミノの種類
	int NowBlock;
	int NextBlock;
	int HoldBlock;

	// キーの入力情報を確保しておく変数
	char Key[(int)Button::max],OldKey[(int)Button::max];

	// 画像情報
	int blockimg[(int)MinoType::max];

	// ウェイト用
	int WaitCnt;
	int WaitCntDef = 30;

	// 読み込んだSEを格納する変数
	int SE_mem;

	// ホールドキーを使用している状態かどうかを見るフラグ
	bool HoldUse;

	// 回転用変数
	const VECTOR2 dir[8] = { { -1,-1 },{ 0,-1 },{ 1,-1 },{ 1,0 } ,{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 } };
	const VECTOR2 rotadir[8] = { { 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 } ,{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 } };
	
	// ゲームボードへのポインタ
	std::shared_ptr<GameBoard> gb;

	// DrawGraphでVector2を使用可能にするため
	int DrawGraph(VECTOR2 pos, int handle, int Trans);
};
