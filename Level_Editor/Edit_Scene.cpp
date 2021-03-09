#include "Edit_Scene.hpp"
#include "Stage.hpp"
#include "Control.hpp"

#include <filesystem>
#include <map>

namespace fs = std::filesystem;

//コンストラクタ
Edit_Scene::Edit_Scene(Scene_Type t, Entry* e) : Scene_base(t, e)
{
	Owner = e;	//Entry クラス




	// #####　コンポーネント #####
	stage = std::make_shared<Stage>(Owner);				//マップ描画
	control = std::make_shared<Control>(Owner);	//操作
}

//初期化
void Edit_Scene::SetUp()
{
	stage->setMapChip(control->getMapChip());
}


//更新
void Edit_Scene::Update()
{



	stage->Update();	//更新
	control->Update();	//更新

	stage->setStage(control->getConfig());								//設定ファイルを書き込む
	stage->WriteGrid(control->getWriteData(),control->isWrite_cell);	//ステージに書き込む
	stage->setSaveFile(control->isSave);								//ファイルをセーブ
	stage->Scroll(control);												//画面スクロール



}




//描画
void Edit_Scene::Draw()
{
	stage->Draw();
	control->Draw();


}

//デストラクタ
Edit_Scene::~Edit_Scene()
{

}
