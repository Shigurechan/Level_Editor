#include "Game_Scene.hpp"
#include "Stage.hpp"
#include "Control.hpp"

#include <filesystem>
#include <map>

namespace fs = std::filesystem;

//コンストラクタ
Game_Scene::Game_Scene(Scene_Type t, Entry* e) : Scene_base(t, e)
{
	Owner = e;	//Entry クラス


	// #####　スプライトをロード #####
	std::vector<SpriteData> SpriteList;	//スプライトリスト
	
	//読み込みファイルパスを設定
	std::string filename = "/Sprite_Data/";
	std::string path = fs::current_path().string();
	//path = filename;
	path = path + filename;
	
	//スプライト読み込み
	
	for (fs::directory_iterator itr = fs::directory_iterator(path); itr != fs::directory_iterator(); itr++)
	{
		printf("%s\n",itr->path().string().c_str());

		SpriteData data;	//スプライトデータ

		data.sprite = Owner->LoadSprite(itr->path().string().c_str());	//スプライトを設定

		std::string name = itr->path().filename().string();	//ファイル名を取得
		data.name = name;	//ファイル名を設定

		if (data.name == "Block.png")
		{
			data.bin = 0x01;
		}
		else if (data.name == "Brick.png")
		{
			data.bin = 0x02;
		}
		else if (data.name == "Shop.png")
		{
			data.bin = 0x03;
		}
		else {
			printf("バイナリ情報未設定: %s\n",data.name.c_str());
		}

		SpriteList.push_back(data);	//スプライト		
	}
	
	









	// #####　コンポーネント #####
	stage = std::make_shared<Stage>(Owner,SpriteList);				//マップ描画
	control = std::make_shared<Control>(Owner,SpriteList);	//操作
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
	stage->Draw();
	control->Draw();


}

//デストラクタ
Game_Scene::~Game_Scene()
{

}
