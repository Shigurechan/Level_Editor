#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include "MapChip.hpp"
#include <Dxlib.h>
#include <array>
#include <vector>

/*####################################################
* エディットするステージを描画
*
* 説明
* 
* 
######################################################*/

class Stage
{
public:
	Stage(Entry *e,std::vector<int> spriteList);	//コンストラクタ
	~Stage();	//デストラクタ

	void Update();		//計算
	void Draw();		//描画

	void setGrid(MapChip chip);		//グリッドに書き込む
	void WriteFile(EditData data);	//バイナリファイルにステージを書き込む
	void ReadFile(EditData data);	//バイナリファイルを読み込む

	void Scroll(glm::ivec2 m);	//スクロールする向き
private:


	std::shared_ptr<std::array<std::array<MapChip, STAGE_GRID_X>,STAGE_GRID_Y>> mStage;	//ステージ
	std::vector<int> SpriteList;	//スプライトリスト
	Entry* Owner;
	
};


#endif
