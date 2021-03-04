#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include "MapChip.hpp"
#include <Dxlib.h>
#include <array>
#include <vector>
#include <iostream>

/*####################################################
* エディットするステージを描画
*
* 説明
* 
* 
######################################################*/

class Control;	//操作

class Stage
{
public:
	Stage(Entry *e,std::vector<int> spriteList);	//コンストラクタ
	~Stage();	//デストラクタ

	void Update();		//計算
	void Draw();		//描画

	void setGrid(MapChip chip, glm::ivec2 screen_grid);		//グリッドに書き込む
	void WriteFile(EditData data);	//バイナリファイルにステージを書き込む
	void ReadFile(EditData data);	//バイナリファイルを読み込む
	void NewFile(EditData data);	//新規ファイルを作成

	void Scroll(std::shared_ptr<Control> control);	//スクロールする向き
private:

	glm::ivec2 mSize;	//サイズ
	std::shared_ptr<std::vector<std::vector<MapChip>>> mStage;	//ステージ
	std::vector<int> SpriteList;	//スプライトリスト
	Entry* Owner;
	
};


#endif
