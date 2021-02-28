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
		printf("新規ファイルを作成\n");

		FILE* fp = NULL;	//ファイルポインタ
		fopen_s(&fp, Data.FileName, "wb"); //書き込み専用モード
		fclose(fp);	//ファイルを閉じる
	}
	else if (Data.EditMode == (byte)WRITE_Edit)
	{
		printf("ファイル編集\n");
		stage->ReadFile(Data);	//ファイルを読み込み

	}
	else if (Data.EditMode == (byte)WRITE_OVERRITE)
	{
		printf("上書き作成\n");
		stage->ReadFile(Data);	//ファイルを読み込み
	}
}


//更新
void Game_Scene::Update()
{


	stage->Update();
	control->Update();

	//グリッドの書き込む
	if ( control->isWrite_cell == true ){
		stage->setGrid(control->getChip());
	}

	//バイナリファイルにステージ情報を書き込むかどうか？
	if (control->isWrite_File == true)
	{
		stage->WriteFile(Data);
		control->isWrite_File = false;
	}

	stage->Scroll(control->getMove());	//画面スクロール






}


//エディットデータを取得
void Game_Scene::getEditData(EditData data)
{
	Data = data;
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
