#pragma once
#include <memory>
#include "Particle.h"

constexpr int BlockSize = 32;
constexpr int LineSize = 10;
const VECTOR2 BoardSize = VECTOR2(10, 20);
const VECTOR2 BoardOffset = VECTOR2(BlockSize * 2, BlockSize * 3);
const VECTOR2 NextOffset = VECTOR2(BlockSize * 14, BlockSize * 3);
const VECTOR2 HoldOffset = VECTOR2(BlockSize * 14, BlockSize * 11);

// ミノに含まれる情報
struct MinoData {
	bool flag = false;
	bool deflag = false;
	int color = 0;
};

// ゲームボードクラス(実際にミノが落ちてきたり消えたりする場所)
class GameBoard
{
public:
	GameBoard();
	~GameBoard();
	
	void Draw();// 描画
	void UpDate();// 更新

	// 引数でもらった座標にブロックが置けるかどうか(ブロックの有無)を返す関数
	bool PutCheck(VECTOR2 pos);

	// データを書き込む関数
	void WriteData(VECTOR2 pos, int color);

	// 落ちるまでのカウントを取得する関数
	int GetDownCnt(){ return DownWait; };

private:
	// 初期化
	void Init();

	// ライン処理
	bool LineCheck();// 一列ブロックがそろっているかどうかのチェック
	bool LineClean();// 一列にそろったブロックを消す関数

	// ボード本体のデータ配列
	MinoData Board[20][10];

	// ブロックの画像データ格納用
	int blockimg[8];

	// その他変数
	int Create;
	int DownWait,DrawWait;
	int Score;
};

