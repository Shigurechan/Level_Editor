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

	type = Window_Scene::Main;	//最初のシーン
	changeScene = false;	//シーンを切り替える
	KeyHandle = MakeKeyInput(100, false, true, false);	//キー入力ハンドルを作成
	if (KeyHandle == -1) { printf("Error MakeKeyInput()\n"); }


	//メインメニュー
	menu = std::make_shared<Window>(e,Window_Scene::Main,glm::ivec2(100,100),glm::ivec2(200,200));
	menu->setTitle("ファイルメニュー",GetColor(0,0,0));
	menu->AddList_Down(Window_Scene::New_File, "新規", 0, GetColor(0, 0, 0));
	menu->AddList_Down(Window_Scene::Edit_File, "編集", 1, GetColor(0, 0, 0));

	//新規作成
	NewFile_menu = std::make_shared<Window>(e, Window_Scene::New_File, glm::ivec2(100, 100), glm::ivec2(300, 200));
	NewFile_menu->setTitle("  ファイル名入力してください", GetColor(0,0,0));

	//編集する時のファイル名入力
	EditFile_menu = std::make_shared<Window>(e, Window_Scene::Edit_File, glm::ivec2(100, 100), glm::ivec2(300, 200));
	EditFile_menu->setTitle("  ファイル名入力してください", GetColor(0, 0, 0));


	//ファイルが存在するかどうか？　存在する時の上書き確認
	CheckFile_menu = std::make_shared<Window>(e, Window_Scene::OverWrite_Check, glm::ivec2(200, 200), glm::ivec2(300, 300));
	CheckFile_menu->setTitle("ファイルが存在します上書きしますか？", GetColor(0, 0, 0));
	CheckFile_menu->AddList_Down(Window_Scene::WriteFile_OverWrite, "YES", 1, GetColor(0, 0, 0));
	CheckFile_menu->AddList_Down(Window_Scene::New_File, "NO", 0, GetColor(0, 0, 0));

}

//更新
void StartMenu::Update()
{

	

	switch (type)
	{
		//メインメニュー
	case Window_Scene::Main:
	{
//		printf("Main\n");

		menu->Update();	//更新
		if (menu->getChangeScene() != Window_Scene::Invalid)
		{
			//キー入力をアクティブにする。		
			SetActiveKeyInput(KeyHandle);//文字列入力を有効化
			
			type = menu->getChangeScene();//シーン切り替え
			menu->Reset();//ウインドを再初期化
		}
	}break;


		//新規作成
	case Window_Scene::New_File:
	{
		//printf("New File\n");
		GetKeyInputString(FileName, KeyHandle);	//入力文字列を取得
				
		//エンターキーで決定
		if (Owner->InputKey->getKeyDown(KEY_INPUT_RETURN) == true)
		{

			//ファイルがあるかどうか？
			if (CheckFile(FileName) == true) {
				//存在する場合
				type = Window_Scene::OverWrite_Check;	//上書き確認シーンに移動
			}
			else {
				//ない場合(新規作成)
				type = Window_Scene::Write_NewFile;	//新規作成
				Mode = (byte)WRITE_NEW;	//エディットモード　新規作成

			}
		}
		else if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
		{
			// 戻る場合
			type = Window_Scene::Main;	//メインメニューに戻る

			memset(FileName, '\0', sizeof(FileName));			//名前の文字列を再初期化
			InitKeyInput();										//入力データを削除
			KeyHandle = MakeKeyInput(100, false, true, false);	//キー入力ハンドルを作成
			SetActiveKeyInput(KeyHandle);						//入力をアクティブ
		}
	}break;


	//ファイルを編集
	case Window_Scene::Edit_File:
	{
		//printf("New File\n");
		GetKeyInputString(FileName, KeyHandle);	//入力文字列を取得

		//エンターキーで決定
		if (Owner->InputKey->getKeyDown(KEY_INPUT_RETURN) == true)
		{
			type = Window_Scene::Write_EditFile;
			Mode = WRITE_Edit;	//エディットモード上書き

		}
		else if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
		{
			// 戻る場合
			type = Window_Scene::Main;	//メインメニューに戻る

			memset(FileName, '\0', sizeof(FileName));			//名前の文字列を再初期化
			InitKeyInput();										//入力データを削除
			KeyHandle = MakeKeyInput(100, false, true, false);	//キー入力ハンドルを作成
			SetActiveKeyInput(KeyHandle);						//入力をアクティブ
		}
	}break;


		//上書き確認
	case Window_Scene::OverWrite_Check:
	{
		//		printf("Main\n");

		CheckFile_menu->Update();
		if (CheckFile_menu->getChangeScene() != Window_Scene::Invalid)
		{
			type = CheckFile_menu->getChangeScene();	//シーン切り替え

			//ファイル名入力画面に戻る時
			if (type == Window_Scene::New_File)
			{
				memset(FileName, '\0', sizeof(FileName));			//名前の文字列を再初期化
				InitKeyInput();										//入力データを削除
				KeyHandle = MakeKeyInput(100, false, true, false);	//キー入力ハンドルを作成
				SetActiveKeyInput(KeyHandle);						//入力をアクティブ


			}

			Mode = WRITE_OVERRITE;	//エディットモード上書き

			CheckFile_menu->Reset();	//ウインドウを最初期化
		}
	}break;


	//　*** ファイルを上書きしてエディット画面に移行 *** 
	case Window_Scene::WriteFile_OverWrite:
	{
		printf("上書き\n");	
		memcpy(data.FileName, FileName, sizeof(data.FileName));
		data.EditMode = Mode;
		changeScene = true;

		Type = Scene_Type::Game;
	}break;


	//　*** 新規ファイル作成してエディット画面に移行 *** 
	case Window_Scene::Write_NewFile:
	{
		//printf("新規ファイルを作成\n");
		memcpy(data.FileName, FileName, sizeof(data.FileName));
		data.EditMode = Mode;
		changeScene = true;
		Type = Scene_Type::Game;

	}break;

	
	//　*** ファイルを編集してエディット画面に移行 *** 
	case Window_Scene::Write_EditFile:
	{
		//printf("ファイルを編集\n");
		memcpy(data.FileName, FileName, sizeof(data.FileName));	//
		data.EditMode = Mode;									//
		changeScene = true;										//
		Type = Scene_Type::Game;								//

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
		menu->Draw();
	}break;

		//新規作成
	case Window_Scene::New_File:
	{
		NewFile_menu->Draw();
		DrawFormatString(NewFile_menu->getPosition().x + 20, NewFile_menu->getPosition().y + 50, GetColor(0, 100, 0), "FileName: %s", FileName);
	}break;

		//上書き確認
	case Window_Scene::OverWrite_Check:
	{
		CheckFile_menu->Draw();	
	}break;

	//上書き確認
	case Window_Scene::Edit_File:
	{
		EditFile_menu->Draw();
		DrawFormatString(EditFile_menu->getPosition().x + 20, EditFile_menu->getPosition().y + 50, GetColor(0, 100, 0), "FileName: %s", FileName);

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

