#include "Game_Scene.hpp"
#include "Stage.hpp"
#include "Control.hpp"

#include <filesystem>

namespace fs = std::filesystem;

//コンストラクタ
Game_Scene::Game_Scene(Scene_Type t,Entry *e) : Scene_base(t,e)
{
	Owner = e;	//Entry クラス


	// #####　スプライトをロード #####

	std::vector<int> SpriteList;	//スプライトリスト

	//スプライト読み込み
	SpriteList.push_back(Owner->LoadSprite("Sprite_Data/Block.png"));
	SpriteList.push_back(Owner->LoadSprite("Sprite_Data/Brick.png"));
	SpriteList.push_back(Owner->LoadSprite("Sprite_Data/Shop.png"));

	// #####　コンポーネント #####
	stage = std::make_shared<Stage>(Owner,SpriteList);				//マップ描画
	control = std::make_shared<Control>(Owner,SpriteList);			//操作



}

//初期化
void Game_Scene::SetUp()
{
	//新規作成
	if (Data.EditMode == (byte)WRITE_NEW)
	{
		//printf("新規ファイルを作成\n");	
		stage->NewFile(Data);	//ファイルを新規作成
		control->setPos(Data.StageSize);	//初期カーソル座標
	}
	else if (Data.EditMode == (byte)WRITE_EDIT)
	{
		//printf("ファイル編集\n");
		stage->ReadFile(Data);	//ファイルを読み込み
		control->setPos(Data.StageSize);	//初期カーソル座標

	}
	else if (Data.EditMode == (byte)WRITE_OVERRITE)
	{
		//printf("上書き作成\n");
		stage->ReadFile(Data);	//ファイルを読み込み
		control->setPos(Data.StageSize);	//初期カーソル座標

	}
	else 
	{
		//printf("Error 未設定 Data.EditMode : %d\n",Data.EditMode);
	}
}


//更新
void Game_Scene::Update()
{


	stage->Update();
	control->Update();

	//グリッドの書き込む
	if ( control->isWrite_cell == true )
	{
		stage->setGrid(control->getChip(),control->getScreenGridPos());
	}

	//バイナリファイルにステージ情報を書き込むかどうか？
	if (control->isWrite_File == true)
	{
		stage->WriteFile(Data);
		control->isWrite_File = false;
	}

	
	stage->Scroll(control);	//画面スクロール
	





}


//エディットデータを取得
void Game_Scene::setEditData(EditData data)
{
	if (isEditScene == false) 
	{
		Data = data;
		SetUp();

		isEditScene = true;
	}

}


//描画
void Game_Scene::Draw()
{
	control->Draw();
	stage->Draw();


}

//デストラクタ
Game_Scene::~Game_Scene()
{

}
