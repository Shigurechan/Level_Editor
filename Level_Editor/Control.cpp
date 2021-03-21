#include "Control.hpp"
#include "Entry.hpp"
#include "MapChip.hpp"
#include "Fps.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

//コンストラクタ
Control::Control(Entry* e)
{

	Owner = e;				//Entry クラス

	//マップチップ選択
	chipMenu = std::make_shared<Window>(Owner,Window_Scene::ChipSelect,glm::ivec2(100,100), glm::ivec2(200, 200));
	chipMenu->setTitle("マップチップを選択",GetColor(0,0,0));


	GridPos = glm::ivec2(13,9);	//グリッド座標
	Screen_GridPos = GridPos;	//スクリーン座標

	// ################ マップチップをロード　################ 
	std::string filename = "MapChip";	//バイナリファイルの格納ディレクトリ
	std::string path = fs::current_path().string();
	path = path + "\\" + filename;
	
	if (fs::exists(path) == false)
	{
		printf("Sprite_Dataフォルダが存在しないため新規作成しました。\n");
		fs::create_directory(path);
	}
	else
	{
		int num = 0;
		printf("マップチップをファイルをロード\n");
		for (fs::directory_iterator itr = fs::directory_iterator(path); itr != fs::directory_iterator(); itr++)
		{
			printf("%s\n", itr->path().filename().string().c_str());	//デバッグ
		

			SpriteData data;

			// 
			if (itr->path().filename().string() == "Block.png")
			{
				data.bin = (byte)MapObject::Block;
				data.name = itr->path().filename().string();
				data.sprite = Owner->LoadSprite(itr->path().string().c_str());

			}
			else if (itr->path().filename().string() == "Brick.png")
			{
				data.bin = (byte)MapObject::Brick;
				data.name = itr->path().filename().string();
				data.sprite = Owner->LoadSprite(itr->path().string().c_str());
			}
			else if (itr->path().filename().string() == "Shop.png")
			{
				data.bin = (byte)MapObject::Shop;
				data.name = itr->path().filename().string();
				data.sprite = Owner->LoadSprite(itr->path().string().c_str());
			}
			else if (itr->path().filename().string() == "Enemy.png")
			{
				data.bin = (byte)MapObject::Enemy;
				data.name = itr->path().filename().string();
				data.sprite = Owner->LoadSprite(itr->path().string().c_str());
			}
			else
			{

				printf("新しい未設定のマップチップを検出 %s\n", itr->path().filename().string().c_str());
			}

			SpriteList.push_back(data);	//マップチップ情報を設定

			//ファイルリスト
			chipMenu->AddList_Down(Window_Scene::None, data.name, num, GetColor(0, 0, 0),GetColor(255, 255, 255),0);
			num++;

		}
		printf("\n\n");
	}
	// ################ 　################ 

	//長押し
	HoldKey_X = false;
	HoldKey_Y = false;
	
	mVector = VECTOR_LEFT;	//方向




	//メニュー切り替え
	isMenu = false;	//メニュー

	isStart = false;			//スタート画面
	isFileSelect = false;		//ファイル切り替え
	isStageResize = false;		//ステージサイズをリサイズ
	isMapChipSelect = false;		//マップチップを切り替え
	isNewFile = false;			//新しいファイルを作成


}

//初期化
void Control::SetUp()
{
	
}

//スプライトデータを取得
std::vector<SpriteData> Control::getSpriteData()
{
	return SpriteList;
}

//向き
glm::ivec2 Control::getVector()
{
	return mVector;
}

//メニュー更新
void Control::MenuUpdate()
{
	if (isMapChipSelect == true)
	{
		chipMenu->Update();
		if (chipMenu->getChangeScene() != Window_Scene::Invalid)
		{
			sendData.sprite = SpriteList.at((int)chipMenu->getItem()).sprite;	//スプライト
			sendData.bin = SpriteList.at((int)chipMenu->getItem()).bin;			//バイナリ

			chipMenu->Reset();	//リセット
			isMapChipSelect = false;
		}
	}

	


}



//メニュー描画
void Control::MenuDraw()
{
	if (isMapChipSelect == true)
	{
		chipMenu->Draw();
	}
	
}





//更新
void Control::Update()
{
	int speed = CELL;
#define HOLD_TIME 30	//長押ししてから反応するまでの時間

	//メニュー画面を開く
	if (Owner->InputKey->getKeyDown(KEY_INPUT_C) == true) //マップチップを選択
	{
		isMapChipSelect = !isMapChipSelect;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_M) == true)	//ステージファイルを選択
	{
		isFileSelect = !isFileSelect;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_S) == true)	//サイズを変更
	{
		isStageResize = !isStageResize;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)	//保存
	{
		
		sendData.isSave = true;
	}
	else 
	{
		
	}





	//エディタ操作
	
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

		

	
	//スペースキーで書き込む
	if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
	{		
		sendData.isWriteCell = true;	//ステージに書き込む
		sendData.gridPos = GridPos;		//グリッド座標を設定
	} 
		

	//ステージの書き込みを消す
	if (Owner->InputKey->getKeyDown(KEY_INPUT_DELETE) == true)
	{
		sendData.isDelete = true;
		sendData.gridPos = GridPos;		//グリッド座標を設定

	}
		
	
	

	MenuUpdate();


	
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



//グリッド座標を設定
void Control::setGridPos(glm::ivec2 g)
{
	GridPos = g;
}

//描画
void Control::Draw()
{
	

	if (isMapChipSelect == false && isFileSelect == false && isStageResize == false)
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

		//printf("あああ\n");
		MenuDraw();	//メニュー描画
	}





}

//デストラクタ
Control::~Control()
{

}

