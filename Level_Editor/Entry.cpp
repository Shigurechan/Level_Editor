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

	type = Scene_Type::Title;	//最初のシーン
}

//スプライトをロード
int Entry::LoadSprite(const char* FileName)
{
	int a = LoadGraph(FileName);

	if (a == -1)
	{
		printf("ファイルが存在しません。%s \n",FileName);
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

	switch (type)
	{


		//タイトル
	case Scene_Type::Title:
	{
		start->Update();
		type = start->getSceneType();

		if (start->changeScene == true)
		{
			data = start->getData();
		}


	}break;




		//メインゲーム
	case Scene_Type::Game:
	{
		//一回だけの場合
		if (start->changeScene == true)
		{
			game->getEditData(data);
			start->changeScene = false;
			game->SetUp();
		}


		game->Update();
		type = game->getSceneType();
	}break;




	};
}

//描画
void Entry::Draw()
{
	switch (type)
	{

	//タイトル
	case Scene_Type::Title:
	{
		start->Draw();
		type = start->getSceneType();
	}break;


	//メインゲーム
	case Scene_Type::Game:
	{
		game->Draw();
		type = game->getSceneType();
	}break;




	};
}

//デストラクタ
Entry::~Entry()
{
	
}

