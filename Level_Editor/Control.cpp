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

	printf("X %d\n", SCREEN_WIDTH / CELL);
	printf("Y %d\n",SCREEN_HEIGHT / CELL);


	
	// チップ選択
	Chip_Menu = std::make_shared<Window>(Owner, Window_Scene::ChipSelect, glm::ivec2(100, 100), glm::ivec2(300, 300));
	Chip_Menu->setTitle("マップチップを選択", GetColor(0, 0, 0));

	//ステージ選択
	Stage_Menu = std::make_shared<Window>(Owner, Window_Scene::StageSelect, glm::ivec2(100, 100), glm::ivec2(300, 300));
	Stage_Menu->setTitle("マップを選択", GetColor(0, 0, 0));

	ChipData.GridPos = glm::ivec2(0,0);


	GridPos = glm::ivec2(13,9);			//グリッド座標
	Screen_GridPos = GridPos;	//スクリーン座標

	// ################ マップチップをロード　################ 
	std::string filename = "\\Assets\\Sprite";	//バイナリファイルの格納ディレクトリ
	std::string path = fs::current_path().string();
	path = path + filename;
	
	if (fs::exists(path) == false)
	{
		printf("Sprite_Dataフォルダが存在しないため新規作成しました。\n");
		fs::create_directory(path);
	}
	else
	{
		int a = 0;
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
			Chip_Menu->AddList_Down(Window_Scene::None, data.name, a, GetColor(0, 0, 0), GetColor(255,255,255));	//メニュー
			a++;

		}
		printf("\n\n");
	}
	// ################ 　################ 


	// ################ ステージをロード　################ 
	filename = "\\Stage_Data";	//バイナリファイルの格納ディレクトリ
	path = fs::current_path().string();
	path = path + filename;
	if (fs::exists(path) == false)
	{
		printf("Stage_Dataフォルダが存在しないため新規作成しました。\n");
		fs::create_directory(path);
	}
	else
	{
		printf("バイナリファイルをロード\n");
		int a = 0;
		for (fs::directory_iterator itr = fs::directory_iterator(path); itr != fs::directory_iterator(); itr++)
		{
			printf("%s\n", itr->path().string().c_str());
			StageFileNameList.push_back(itr->path().string());
			Stage_Menu->AddList_Down(Window_Scene::None, itr->path().filename().string(), a, GetColor(0, 0, 0), GetColor(255, 255, 255));	//ウインドウ


			a++;
		}
		printf("\n\n");
	}
	// ################ 　################ 


	//長押し
	HoldKey_X = false;
	HoldKey_Y = false;
	
	isWrite_cell = false;	//書き込むかどうか？
	isSave = false;		//ファイルにセーブするかどうか？

	mVector = VECTOR_LEFT;

	ChipData.bin = SpriteList.at(0).bin;			//バイナリ
	ChipData.sprite = SpriteList.at(0).sprite;	//スプライト


	// メニュー画面
	isChipSelect = false;	//チップ選択
	isStageSelect = true;	//ステージ選択
	isChangeSize = false;	//サイズ選択
	isSave = false;			//セーブする

}

//初期化
void Control::SetUp()
{
	
}


//向き
glm::ivec2 Control::getVector()
{
	return mVector;
}

//メニュー更新
void Control::MenuUpdate() 
{
	//ステージ選択
	if (isStageSelect == true) 
	{
		Stage_Menu->Update();
		if (Stage_Menu->getChangeScene() != Window_Scene::Invalid)
		{
			Config.StageFileName = StageFileNameList.at(Stage_Menu->getItem());	//コンフィグデータにステージ名を設定		
			Stage_Menu->Reset();
			isStageSelect = false;
		}
	}
	else if (isChipSelect == true)
	{
		// チップ選択
		Chip_Menu->Update();

		if (Chip_Menu->getChangeScene() != Window_Scene::Invalid)
		{
			ChipData.bin = SpriteList.at(Chip_Menu->getItem()).bin;			//バイナリ
			ChipData.sprite = SpriteList.at(Chip_Menu->getItem()).sprite;	//スプライト
			//ChipData.GridPos = GridPos;										//座標

			Chip_Menu->Reset();
			isChipSelect = false;
		}
	}








}

//コンフィグデータを取得
ConfigData Control::getConfig()
{
	return Config;
}


//マップチップを取得
std::vector<SpriteData> Control::getMapChip()
{
	return SpriteList;
}



//メニュー描画
void Control::MenuDraw()
{
	//ステージ選択
	if (isStageSelect == true) 
	{
		Stage_Menu->Draw();
	}
	else if (isChipSelect == true)
	{
		// チップ選択
		Chip_Menu->Draw();
	}



}





//更新
void Control::Update()
{
	int speed = CELL;
#define HOLD_TIME 30	//長押ししてから反応するまでの時間

	//メニュー画面を開く
	if (Owner->InputKey->getKeyDown(KEY_INPUT_C) == true) 
	{
		isChipSelect = !isChipSelect;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_M) == true)
	{
		isStageSelect = !isStageSelect;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_S) == true)
	{
		isChangeSize = !isChangeSize;
	}

	//P キーで保存
	if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)
	{
		isSave = true;
	}
	else {
		isSave = false;
	}





	//エディタ操作
	if (isChipSelect == false && isChangeSize == false && isStageSelect == false)
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



	
		//スペースキーで書き込む
		if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
		{
			ChipData.GridPos = GridPos;	//グリッド座標

			isWrite_cell = true;	//ステージに書き込む
		}
		else {
			isWrite_cell = false;	//ステージ書き込まない
		}

		//ステージの書き込みを消す
		if (Owner->InputKey->getKeyDown(KEY_INPUT_DELETE) == true)
		{
			
			isWrite_cell = true;	//ステージに書き込む
		}

	}
	else
	{
		MenuUpdate();
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

//書き込みデータを取得
WriteData Control::getWriteData()
{
	return ChipData;
}


//グリッド座標を設定
void Control::setGridPos(glm::ivec2 g)
{
	GridPos = g;
}

//描画
void Control::Draw()
{
	

	if (isChipSelect == false && isChangeSize == false && isStageSelect == false)
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


	//セーブ表示
	if (isSave == true)
	{
		DrawFormatString(0,0, GetColor(255, 255, 255), "SAVED"); 
	}




}

//デストラクタ
Control::~Control()
{

}

