#pragma once
#include "SceneState.h"
#include <vector>

// 画像生成、描画用の構造体
struct ImgInfo
{
	int buff;// イメージデータ
	VECTOR2 pos;// 座標
	VECTOR2 vec;// 速度
};

// リザルトシーンクラス
class ResultScene :
	public SceneState
{
public:
	ResultScene(std::shared_ptr<GameBoard>);
	~ResultScene();

	int Init();
	Scene UpDate(Scene & _this);
private:
	// ブロックを灰色のブロックに変えていく関数
	void ChangeBlock(bool isEnd);

	// その他変数
	std::shared_ptr<GameBoard> gb;
	int Cnt,y,buffnum,frame;
	char lrKey[2][2];
	bool isEnd,isContinue;
	std::vector<ImgInfo> imgvec;
};
