#include "Control.hpp"
#include "Entry.hpp"
#include "MapChip.hpp"
#include "Fps.hpp"

//コンストラクタ
Control::Control(Entry* e, std::vector<int> sprite)
{
	Owner = e;	//Entry クラス
	SpriteList = sprite;	//スプライトリスト

	
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

	mVector = VECTOR_LEFT;


	printf("X: %d\n", SCREEN_WIDTH / CELL);
	printf("Y: %d\n",SCREEN_HEIGHT / CELL);

	
}

//座標を指定
void Control::setPos(glm::ivec2 size)
{
	GridPos = glm::ivec2(15, 10);		//グリッドの座標
	Screen_GridPos = glm::ivec2(15, 10);	//スクリーンのグリッド座標

}

//向き
glm::ivec2 Control::getVector()
{
	return mVector;
}

//更新
void Control::Update()
{
	int speed = CELL;
#define HOLD_TIME 30	//長押ししてから反応するまでの時間



	//Left Right
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > 0)
	{
		//長押し
		if (HoldKey_X == false) 
		{
			GridPos.x += -1;		//ステージ座標
			Screen_GridPos.x += -1;	//スクリーン座標
			HoldKey_X = true;		//長押し
			mVector = VECTOR_LEFT;	//方向
		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > HOLD_TIME)
			{
				HoldKey_X = false;	//長押し
			}
		}
	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
	{
		//長押し
		if (HoldKey_X == false) 
		{
			GridPos.x += 1;			//ステージ座標
			Screen_GridPos.x += 1;	//スクリーン座標
			HoldKey_X = true;		//長押し
			mVector = VECTOR_RIGHT;	//方向

		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > HOLD_TIME)
			{
				HoldKey_X = false;	//長押し
			}
		}
	}
	else {
		HoldKey_X = false;	//長押し

		mVector = glm::ivec2(0,0);	//方向なし
	}


	//Up Down
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > 0)
	{
		//長押し
		if (HoldKey_Y == false) 
		{			
			GridPos.y += -1;		//ステージ座標
			Screen_GridPos.y += -1;	//スクリーン座標
			HoldKey_Y = true;		//長押し
			mVector = VECTOR_UP;	//方向

		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > HOLD_TIME)
			{
				HoldKey_Y = false;	//長押し
			}
		}
	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
	{
		//長押し
		if (HoldKey_Y == false) 
		{
			GridPos.y += 1;			//ステージ座標
			Screen_GridPos.y += 1;	//スクリーン座標
			HoldKey_Y = true;		//長押し
			mVector = VECTOR_DOWN;	//方向

		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > HOLD_TIME)
			{
				HoldKey_Y = false;	//長押し
			}
		}
	}
	else {
		HoldKey_Y = false;	//長押し

	}



	//保存　P　キー
	if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)
	{
		printf("保存\n");

		isWrite_File = true;	//ファイルを保存
	}
	else
	{
		isWrite_File = false;
	}


	//設置オブジェクトをファンクションキーで切り替え
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

//現在のグリット座標
glm::ivec2 Control::getGridPos()
{
	return GridPos;
}

//スクリーンのグリッド座標を取得
glm::ivec2 Control::getScreenGridPos()
{
	return Screen_GridPos;
}


//スクリーンのグリッド座標を設定
void Control::setScreenGridPos(glm::ivec2 p)
{
	Screen_GridPos = p;
}


//マップチップを取得
MapChip Control::getChip()
{
	return chip;
}

//グリッド座標を設定
void Control::setGridPos(glm::ivec2 g)
{
	GridPos = g;
}

//描画
void Control::Draw()
{
	//矩形描画
	int c = anim->getClip_loop(5);
	if (c == 1) 
	{
		//DrawBox(GridPos.x * CELL, GridPos.y * CELL, (GridPos.x * CELL) + CELL, (GridPos.y * CELL) + CELL, GetColor(0, 255, 0), true);
		DrawBox(Screen_GridPos.x * CELL, Screen_GridPos.y * CELL, (Screen_GridPos.x * CELL) + CELL, (Screen_GridPos.y * CELL) + CELL, GetColor(0, 255, 0), true);
	}


	DrawFormatString(400, 0, GetColor(255, 255, 255), "GridPos: %d , %d ", GridPos.x, GridPos.y);
	DrawFormatString(400, 32, GetColor(255, 255, 255), "Screen_GridPos: %d , %d ", Screen_GridPos.x, Screen_GridPos.y);


}

//デストラクタ
Control::~Control()
{

}

