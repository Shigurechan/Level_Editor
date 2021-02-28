#ifndef ___CONTROL_HPP_
#define ___CONTROL_HPP_


#include <Dxlib.h>
#include "MapChip.hpp"
#include "Animation.hpp"

#include "glm/glm.hpp"
#include <vector>
#include <iostream>

class Entry;

/*####################################################
* コントロール
*
* 説明
* マウスとキーボードによる操作　関係のクラス
######################################################*/

class Control
{
public:
	Control(Entry* e,std::vector<int> sprite);	//コンストラクタ
	~Control();			//デストラクタ



	void Update();	//更新

	void Draw();	//描画

	glm::ivec2 getMove();
	MapChip getChip();	//マップチップ

	bool isWrite_cell;	//書き込むかどうか？
	bool isWrite_File;	//ステージ情報をバイナリファイルに書き込むかどうか？

private:
	glm::ivec2 CursorPos;	//カーソルの場所
	glm::ivec2 GridPos;		//グリッドの場所
	glm::ivec2 ScrollMove;	//スクロールする向き


	MapChip chip;	//書き込む情報
	std::vector<int> SpriteList;	//スプライトリスト
	std::shared_ptr<Animation> anim;

	//長押し
	bool HoldKey_X;
	bool HoldKey_Y;


	Entry* Owner;			//Entry クラス
};


#endif