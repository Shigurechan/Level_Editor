#include "Game_Scene.hpp"
#include "Stage.hpp"
#include "Control.hpp"


//コンストラクタ
Game_Scene::Game_Scene(Scene_Type t,Entry *e) : Scene_base(t,e)
{
	Owner = e;	//Entry クラス


	// #####　スプライトをロード #####

	//int Player_Handle = Owner->LoadSprite("Assets/Player/Player_0.png");	//プレイヤー
	//int Enemy_Handle = Owner->LoadSprite("Assets/Enemy.png");				//エネミー	
	
	//int Block_Handle = Owner->LoadSprite("Assets/Block.png");	//ブロック	
	//int Brick_Handle = Owner->LoadSprite("Assets/Brick.png");	//レンガ
	//int Shop_Handle = Owner->LoadSprite("Assets/Shop.png");		//ショップ

	// #####　コンポーネント #####
	stage = std::make_shared<Stage>();		//マップ描画
	control = std::make_shared<Control>(Owner);	//操作



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
