#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include "MapChip.hpp"
#include <Dxlib.h>
#include <array>

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
	Stage();	//コンストラクタ
	~Stage();	//デストラクタ

	void Update();		//計算
	void Draw();		//描画

	void setGrid(MapChip chip);	//グリッドに書き込む
	//void setObject();	//
private:


	std::shared_ptr<std::array<std::array<MapChip, STAGE_GRID_X>,STAGE_GRID_Y>> mStage;	//ステージ
	
};


#endif
