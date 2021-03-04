#include "Entry.hpp"
#include "Game_Scene.hpp"
#include "StartMenu.hpp"

//コンストラクタ
Entry::Entry()
{
	//printf("SCRREN_WIDTH : %d\n", SCREEN_WIDTH);
	//printf("SCRREN_HEIGHT : %d\n",SCREEN_HEIGHT);

	InputKey = std::make_shared<Input>();	//キー入力

	game = std::make_shared<Game_Scene>(Scene_Type::Game, this);
	start = std::make_shared<StartMenu>(Scene_Type::Title, this);

	Scene = Scene_Type::Title;	//最初のシーン
}

//スプライトをロード
int Entry::LoadSprite(const char* FileName)
{
	int a = LoadGraph(FileName);

	if (a == -1)
	{
		printf("ファイルが存在しません。Path: %s \n",FileName);
		return -1;
	}
	else {
		return a;
	}
}





//計算
void Entry::Update()
{
	InputKey->Update();

	switch (Scene)	
	{

		//タイトル
	case Scene_Type::Title:
	{
		start->Update();				//更新
		Scene = start->getSceneType();	//シーン推移
		mData = start->getEditData();	//エディットデータを取得
	}break;

		//メインゲーム
	case Scene_Type::Game:
	{
		game->Update();					//更新
		game->setEditData(mData);		//エディットデータを設定
		Scene = game->getSceneType();	//シーン推移
	}break;




	};
}

//描画
void Entry::Draw()
{
	switch (Scene)
	{

	//タイトル
	case Scene_Type::Title:
	{
		start->Draw();
		Scene = start->getSceneType();
	}break;


	//メインゲーム
	case Scene_Type::Game:
	{
		game->Draw();
		Scene = game->getSceneType();
	}break;




	};
}

//デストラクタ
Entry::~Entry()
{
	
}

