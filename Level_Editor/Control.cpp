#include "Control.hpp"
#include "Entry.hpp"
#include "MapChip.hpp"
#include "Fps.hpp"

//コンストラクタ
Control::Control(Entry* e, std::vector<SpriteData> sprite)
{
	Owner = e;				//Entry クラス

	SpriteList = sprite;	//スプライトリスト
	
	anim = std::make_shared<Animation>(2);	//カーソル点滅アニメーション

	menu = std::make_shared<Window>(Owner,Window_Scene::Main,glm::ivec2(100,100),glm::ivec2(300,300));
	menu->setTitle("スプライト選択", GetColor(0, 0, 0));
	for (int i = 0; i < SpriteList.size(); i++)
	{
		menu->AddList_Down(Window_Scene::Yes,SpriteList.at(i).name, i,GetColor(0,0,0), GetColor(255, 255, 255));
	}






	//長押し
	HoldKey_X = false;
	HoldKey_Y = false;
	
	isWrite_cell = false;	//書き込むかどうか？
	isWrite_File = false;	//バイナリファイルにステージ情報を書き込むかどうか？

	//書き込み情報を設定
	chip.setBinary(SpriteList.at(0).bin);		//バイナリ
	chip.setSprite(SpriteList.at(0).sprite);	//スプライト
	chip.setPosition(GridPos);					//グリッド座標

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
void Control::MenuUpdate() 
{
	menu->Update();

	if (menu->getChangeScene() == Window_Scene::Yes) 
	{
		byte c = menu->getItem();
		SpriteData data = SpriteList.at(c);
		chip.setBinary(data.bin);
		chip.setSprite(data.sprite);
		

		menu->Reset();	//ウインドウをリセット
		isMenu = false;	//エディターに戻る
	}


}

//描画
void Control::MenuDraw()
{
	menu->Draw();

}


//更新
void Control::Update()
{
	int speed = CELL;
#define HOLD_TIME 30	//長押ししてから反応するまでの時間

	//メニュー画面を開く M キー
	if (Owner->InputKey->getKeyDown(KEY_INPUT_M) == true) {
		isMenu = !isMenu;
	}

	if (isMenu == false)
	{
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

			mVector = glm::ivec2(0, 0);	//方向なし
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
	else if (isMenu == true)
	{
	//メニュー画面時
//	printf("メニュー画面\n");
	MenuUpdate();	//メニュー画面
		



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
	

	if (isMenu == false) 
	{
		//矩形描画
		if (Fps::getFrame() % 15 == 0)
		{
			//DrawBox(GridPos.x * CELL, GridPos.y * CELL, (GridPos.x * CELL) + CELL, (GridPos.y * CELL) + CELL, GetColor(0, 255, 0), true);
			DrawBox(Screen_GridPos.x * CELL, Screen_GridPos.y * CELL, (Screen_GridPos.x * CELL) + CELL, (Screen_GridPos.y * CELL) + CELL, GetColor(0, 255, 0), true);

		}

		DrawFormatString(400, 0, GetColor(255, 255, 255), "GridPos: %d , %d ", GridPos.x, GridPos.y);
		DrawFormatString(400, 32, GetColor(255, 255, 255), "Screen_GridPos: %d , %d ", Screen_GridPos.x, Screen_GridPos.y);

	}
	else {

		MenuDraw();
	}

}

//デストラクタ
Control::~Control()
{

}

