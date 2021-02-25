#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include <Dxlib.h>

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

	void Update();	//計算
	void Draw();	//描画

private:


	byte mGame_Stage[ STAGE_GRID_Y ][ STAGE_GRID_X ];	//ステージ
};


#endif
