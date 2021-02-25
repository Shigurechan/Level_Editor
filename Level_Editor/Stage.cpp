#include "Stage.hpp"

//コンストラクタ
Stage::Stage()
{
	
	//グリッドを初期化
	for (int y = 0; y < STAGE_GRID_Y; y++)
	{
		for (int x = 0; x < STAGE_GRID_X; x++)
		{
			mGame_Stage[y][x] = (byte)0;
		}
	}
	

}

//更新
void Stage::Update()
{

}

//描画
void Stage::Draw()
{


	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		DrawLine(0,y * CELL, STAGE_WIDTH, y * CELL ,GetColor(0,255,0));
	}

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		DrawLine(x * CELL, 0, x * CELL, STAGE_HEIGHT, GetColor(0, 255, 0));
	}




}


//デストラクタ
Stage::~Stage()
{

}
