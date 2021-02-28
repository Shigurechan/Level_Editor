#include "Control.hpp"
#include "Entry.hpp"
#include "MapChip.hpp"
#include "Fps.hpp"

//コンストラクタ
Control::Control(Entry* e, std::vector<int> sprite)
{
	printf("X: %d\n", (SCREEN_WIDTH / CELL) / 2 * CELL);


	Owner = e; //Entry クラス
	SpriteList = sprite;	//スプライトリスト

	CursorPos = glm::ivec2((SCREEN_WIDTH / CELL) / 2 * CELL, (SCREEN_HEIGHT / CELL) / 2 * CELL);	//カーソル座標
	GridPos = glm::ivec2(CursorPos.x / CELL, CursorPos.y / CELL);		//グリッドの座標

	anim = std::make_shared<Animation>(2);	//カーソル点滅アニメーション

	//長押し
	HoldKey_X = false;
	HoldKey_Y = false;

	isWrite_cell = false;	//書き込むかどうか？
	isWrite_File = false;	//バイナリファイルにステージ情報を書き込むかどうか？

	//書き込み情報を設定
	chip.setBinary(0x01);				//バイナリ
	chip.setSprite(SpriteList.at(0));	//スプライト
	chip.setPosition(GridPos);			//グリッド座標



	
}

//更新
void Control::Update()
{
	int speed = CELL;
#define HOLD_TIME 30	//長押ししてから反応するまでの時間



	//左右
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > 0)
	{
		//長押し
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
	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
	{
		//長押し
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
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > 0)
	{
		//長押し
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
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
	{
		//長押し
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
	else
	{
		isWrite_File = false;
	}


	//ファンクションキーで切り替え
	if (Owner->InputKey->getKeyDown(KEY_INPUT_F1) == true)
	{
		chip.setBinary(0x01);				//バイナリ
		chip.setSprite(SpriteList.at(0));	//スプライト
		chip.setPosition(GridPos);			//グリッド座標
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_F2) == true)
	{
		chip.setBinary(0x02);				//バイナリ
		chip.setSprite(SpriteList.at(1));	//スプライト
		chip.setPosition(GridPos);			//グリッド座標
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_F3) == true)
	{
		chip.setBinary(0x03);				//バイナリ
		chip.setSprite(SpriteList.at(2));	//スプライト
		chip.setPosition(GridPos);			//グリッド座標
	}


	if (Owner->InputKey->getKeyDown(KEY_INPUT_F1) == true)
	{
		chip.setBinary(0x01);				//バイナリ
		chip.setSprite(SpriteList.at(0));	//スプライト
		chip.setPosition(GridPos);			//グリッド座標
	}


	//スペースキーで書き込む
	if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
	{
		chip.setPosition(GridPos);			//グリッド座標

		isWrite_cell = true;	//ステージに書き込む
	}
	else {
		isWrite_cell = false;	//ステージ書き込まない
	}




	//ステージの書き込みを消す
	if (Owner->InputKey->getKeyDown(KEY_INPUT_DELETE) == true)
	{
		chip.setBinary(0x00);				//バイナリ
		chip.setSprite(0);					//スプライト		
		chip.setPosition(GridPos);			//グリッド座標

		isWrite_cell = true;	//ステージに書き込む
	}
	
}

//マップをスクロールする向き
glm::ivec2 Control::getMove()
{
	return ScrollMove;
}


MapChip Control::getChip()
{
	return chip;
}


//描画
void Control::Draw()
{
	//矩形描画
	int c = anim->getClip_loop(5);
	if (c == 1) {
		DrawBox(CursorPos.x + 1, CursorPos.y + 1, CursorPos.x + CELL, CursorPos.y + CELL, GetColor(0, 255, 0), true);
	
	}
}

//デストラクタ
Control::~Control()
{

}

