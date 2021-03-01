#include "StartMenu.hpp"
#include "Window.hpp"

#include <Dxlib.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>


//コンスタラクタ
StartMenu::StartMenu(Scene_Type t, Entry* e) : Scene_base(t,e)
{
#define BACK_COLOR GetColor(255,255,255)

	type = Window_Scene::Main;	//最初のシーン
	changeScene = false;	//シーンを切り替える
		
	//メインメニュー
	Main_menu = std::make_shared<Window>(e,Window_Scene::Main,glm::ivec2(100,100),glm::ivec2(200,200));
	Main_menu->setTitle("ファイルメニュー",GetColor(0,0,0));
	Main_menu->AddList_Down(Window_Scene::New_File, "新規", 1, GetColor(0, 0, 0), BACK_COLOR);
	Main_menu->AddList_Down(Window_Scene::Edit_File, "編集", 2, GetColor(0, 0, 0), BACK_COLOR);
		
	//新規作成
	NewFile_menu = std::make_shared<Window>(e, Window_Scene::New_File, glm::ivec2(200, 200), glm::ivec2(300, 200));
	NewFile_menu->setTitle("  ファイル名入力してください", GetColor(0, 0, 0));
	NewFile_menu->AddList_Down(Window_Scene::None, "FileName: ", 2, GetColor(0, 0, 0), BACK_COLOR,INPUT_CHARACTER);
	
	//編集
	EditFile_menu = std::make_shared<Window>(e, Window_Scene::Edit_File, glm::ivec2(200, 200), glm::ivec2(300, 200));
	EditFile_menu->setTitle("  ファイル名入力してください", GetColor(0, 0, 0));

	//存在する時の上書き確認
	CheckFile_menu = std::make_shared<Window>(e, Window_Scene::OverWrite_Check, glm::ivec2(300, 300), glm::ivec2(400, 300));
	CheckFile_menu->setTitle("ファイルが存在します上書きしますか？", GetColor(0, 0, 0));
	CheckFile_menu->AddList_Down(Window_Scene::WriteFile_OverWrite, "YES", 3, GetColor(0, 0, 0), BACK_COLOR);
	CheckFile_menu->AddList_Down(Window_Scene::New_File, "NO", 4, GetColor(0, 0, 0), BACK_COLOR);

	//ステージのサイズを指定する
	SizeSet_NewFile_menu = std::make_shared<Window>(e, Window_Scene::SizeSet, glm::ivec2(400, 400), glm::ivec2(500, 400));
	SizeSet_NewFile_menu->setTitle("ステージのサイズを指定",GetColor(0,0,0));							//タイトル
	SizeSet_NewFile_menu->AddList_Down(Window_Scene::Invalid, "X: ", 5, GetColor(0, 0, 0), BACK_COLOR);	//X座標を指定
	SizeSet_NewFile_menu->AddList_Down(Window_Scene::Invalid, "Y: ", 6, GetColor(0, 0, 0), BACK_COLOR);	//Y座標を指定
	SizeSet_NewFile_menu->AddList_Down(Window_Scene::Write_NewFile, "決定: ", 7, GetColor(0, 0, 0), BACK_COLOR);	//決定ボタン



}

//更新
void StartMenu::Update()
{
	switch (type)
	{
		//メインメニュー
	case Window_Scene::Main:
	{
		Main_menu->Update();

		if (Main_menu->getChangeScene() != Window_Scene::Invalid)
		{
			type = Main_menu->getChangeScene();
			Main_menu->Reset();
		}
	}break;

	//新規作成
	case Window_Scene::New_File:
	{
		NewFile_menu->Update();

		if (NewFile_menu->getChangeScene() != Window_Scene::Invalid)
		{
			std::vector<char*> tmp;
			tmp = NewFile_menu->getInputKeyData();

			//ファイルが存在するかどうか？
			if (CheckFile(tmp.at(0)) == true)
			{
				// ファイルが存在する場合
				type = Window_Scene::OverWrite_Check;
				NewFile_menu->Reset();

			}
			else
			{
				// ファイルがない場合
				type = Window_Scene::SizeSet_NewFile;
				NewFile_menu->Reset();
			}
		}
	}break;

	









	}

}

//描画
void StartMenu::Draw()
{
	switch (type)
	{

		//メインメニュー
	case Window_Scene::Main:
	{
		Main_menu->Draw();
	}break;

		//新規作成
	case Window_Scene::New_File:
	{
		NewFile_menu->Draw();
	}break;


	//新規作成
	case Window_Scene::SizeSet_NewFile:
	{
	
	}break;


	}

}


//ファイルが存在するかどうか？
bool StartMenu::CheckFile(const char* FileName){
	std::ifstream ifs(FileName);
	if (ifs.is_open() == false)
	{
		//printf("ファイルがありません。\n");
		return false;
	}
	else {
		//printf("ファイルが存在します。\n");
		return true;
	}
}


EditData StartMenu::getData()
{
	return data;
}

//デストラクタ
StartMenu::~StartMenu()
{

}

