#ifndef ___CONTROL_HPP_
#define ___CONTROL_HPP_


#include <Dxlib.h>
#include "MapChip.hpp"
#include "glm/glm.hpp"

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
	Control(Entry* e);	//コンストラクタ
	~Control();			//デストラクタ



	void Update();	//更新

	void Draw();	//描画


	MapChip getChip();	//マップチップ

	bool isWrite_cell;	//書き込むかどうか？
	bool isWrite_File;	//ステージ情報をバイナリファイルに書き込むかどうか？

private:
	Entry* Owner;	//Entry クラス
	glm::ivec2 CursorPos;	//カーソルの場所
	glm::ivec2 GridPos;	//グリッドの場所

	MapChip chip;


	//長押し
	bool HoldKey_X;
	bool HoldKey_Y;



	//テスト
	int Block_Handle;






};


#endif