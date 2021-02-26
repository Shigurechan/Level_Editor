#include "StartMenu.hpp"
#include "Window.hpp"

#include <filesystem>
#include <iostream>
#include <string>


//コンスタラクタ
StartMenu::StartMenu(Scene_Type t, Entry* e) : Scene_base(t,e)
{
	/*
	std::string path = std::filesystem::current_path().string();

	for (std::filesystem::directory_iterator file = std::filesystem::directory_iterator(path).begin();)
		std::cout << file->path() << std::endl;
	*/

	type = Window_Scene::Main;
	menu = std::make_shared<Window>(e,Window_Scene::Main,glm::ivec2(100,100),glm::ivec2(200,200));
	menu->setTitle("ファイルメニュー",GetColor(0,0,0));
	menu->AddList_Down(Window_Scene::New_File, "新規", 0, GetColor(0, 0, 0));
	menu->AddList_Down(Window_Scene::Edit_File, "編集", 1, GetColor(0, 0, 0));




}

//更新
void StartMenu::Update()
{
	switch (type)
	{
		case Window_Scene::Main:
		{
			menu->Update();
			if (menu->getChangeScene() != Window_Scene::Invalid)
			{
				type = menu->getChangeScene();
				menu->Reset();
			}
		}break;


		case Window_Scene::New_File:
		{
			
		}break;








	}








}

//描画
void StartMenu::Draw()
{
	switch (type)
	{
	case Window_Scene::Main:
	{
		menu->Draw();
	}break;


	}

}




//デストラクタ
StartMenu::~StartMenu()
{

}

