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
	stage->SetUp();
	stage->setMapChip(control->getSpriteData());	//スプライトデータを読み込み
	//printf("さああ\n");

	Type = Scene_Type::Edit;
}


//更新
void Edit_Scene::Update()
{



	stage->setControl(control);
	

	control->Update();	//更新
	stage->Update();	//更新

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
