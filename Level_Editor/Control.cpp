#include "Control.hpp"
#include "Entry.hpp"
#include "MapChip.hpp"

//コンストラクタ
Control::Control(Entry* e)
{
	Owner = e; //Entry クラス
	CursorPos = glm::ivec2(0, 0);	//カーソル座標
	GridPos = CursorPos;			//グリッドの座標

	//長押し
	HoldKey_X = false;
	HoldKey_Y = false;

	isWrite_cell = false;	//書き込むかどうか？
	isWrite_File = false;	//バイナリファイルにステージ情報を書き込むかどうか？



	Block_Handle = Owner->LoadSprite("Assets/Block.png");	//ブロック	
}

//更新
void Control::Update()
{
	int speed = CELL;	
#define HOLD_TIME 30	//長押ししてから反応するまでの時間



	//左右
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > 0)
	{
		if (HoldKey_X == false) {
			CursorPos.x += -speed;
			GridPos.x += -1;
			HoldKey_X = true;
		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > HOLD_TIME)
			{
				HoldKey_X = false;
			}
		}
	}else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
	{
		if (HoldKey_X == false) {
			CursorPos.x += speed;
			GridPos.x += 1;

			HoldKey_X = true;
		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > HOLD_TIME)
			{
				HoldKey_X = false;
			}
		}
	}
	else {
		HoldKey_X = false;
	}


	//上下
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP)  > 0)
	{
		if (HoldKey_Y == false) {
			CursorPos.y += -speed;
			GridPos.y += -1;

			HoldKey_Y = true;
		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > HOLD_TIME)
			{
				HoldKey_Y = false;
			}
		}
	}
	else if(Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
	{
		if (HoldKey_Y == false) {
			CursorPos.y += speed;
			GridPos.y += 1;

			HoldKey_Y = true;
		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > HOLD_TIME)
			{
				HoldKey_Y = false;
			}
		}
	}
	else {
		HoldKey_Y = false;

	}

	// モード切り替え
	if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)
	{
		printf("保存\n");

		isWrite_File = true;	//ファイルを保存


	}





	//スペースで書き込む
	if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
	{
		chip.setBinary(0x01);			//バイナリ
		chip.setSprite(Block_Handle);	//スプライト
		chip.setPosition(GridPos);		//グリッド座標

		isWrite_cell = true;	//グリッドに書き込む
	}
	else {
		isWrite_cell = false;
	}






}


MapChip Control::getChip()
{
	return chip;
}


//描画
void Control::Draw()
{
	//矩形描画
	DrawBox(CursorPos.x + 1, CursorPos.y + 1, CursorPos.x + CELL, CursorPos.y + CELL, GetColor(0,0,120),true);
}

//デストラクタ
Control::~Control()
{

}

