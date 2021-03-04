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

	mNowScene = Window_Scene::Main;	//最初のシーン
	changeScene = false;	//シーンを切り替える
		
	//メインメニュー
	Main_menu = std::make_shared<Window>(e,Window_Scene::Main,glm::ivec2(100,100),glm::ivec2(200,200));
	Main_menu->setTitle("ファイルメニュー",GetColor(0,0,0));
	Main_menu->AddList_Down(Window_Scene::New_File, "新規", 1, GetColor(0, 0, 0), BACK_COLOR);
	Main_menu->AddList_Down(Window_Scene::Edit_File, "編集", 2, GetColor(0, 0, 0), BACK_COLOR);
		
	//新規作成
	NewFile_menu = std::make_shared<Window>(e, Window_Scene::New_File, glm::ivec2(200, 200), glm::ivec2(300, 200));
	NewFile_menu->setTitle("ファイル名入力してください", GetColor(0, 0, 0));
	NewFile_menu->AddList_Down(Window_Scene::Yes, "FileName: ", 2, GetColor(0, 0, 0), BACK_COLOR,INPUT_CHARACTER);
	
	//編集
	EditFile_menu = std::make_shared<Window>(e, Window_Scene::Edit_File, glm::ivec2(200, 200), glm::ivec2(300, 200));
	EditFile_menu->setTitle("ファイル名入力してください", GetColor(0, 0, 0));
	EditFile_menu->AddList_Down(Window_Scene::Yes, "FileName ", 3, GetColor(0, 0, 0), BACK_COLOR,INPUT_CHARACTER);

	//上書き
	CheckFile_menu = std::make_shared<Window>(e, Window_Scene::OverWrite_Check, glm::ivec2(300, 300), glm::ivec2(400, 300));
	CheckFile_menu->setTitle("ファイルが存在します上書きしますか？", GetColor(0, 0, 0));
	CheckFile_menu->AddList_Down(Window_Scene::Yes, "YES", 3, GetColor(0, 0, 0), BACK_COLOR);
	CheckFile_menu->AddList_Down(Window_Scene::No, "NO", 4, GetColor(0, 0, 0), BACK_COLOR);

	//ステージのサイズを指定する
	SizeSet_menu = std::make_shared<Window>(e, Window_Scene::SizeSet, glm::ivec2(400, 400), glm::ivec2(500, 400));
	SizeSet_menu->setTitle("ステージのサイズを指定",GetColor(0,0,0));							//タイトル
	SizeSet_menu->AddList_Down(Window_Scene::Invalid, "X: ", 5, GetColor(0, 0, 0), BACK_COLOR,INPUT_NUMBER);	//X座標を指定
	SizeSet_menu->AddList_Down(Window_Scene::Invalid, "Y: ", 6, GetColor(0, 0, 0), BACK_COLOR,INPUT_NUMBER);	//Y座標を指定
	SizeSet_menu->AddList_Down(Window_Scene::Yes, "決定: ", 7, GetColor(0, 0, 0), BACK_COLOR);	//決定ボタン
	SizeSet_menu->AddList_Down(Window_Scene::No, "戻る", 7, GetColor(0, 0, 0), BACK_COLOR);	//決定ボタン
	
	//サイズ指定エラー
	SizeSetError_menu = std::make_shared<Window>(e, Window_Scene::SizeSetError, glm::ivec2(500, 500), glm::ivec2(600, 500));
	SizeSetError_menu->setTitle("サイズ指定が不正です。", GetColor(0, 0, 0));
	SizeSetError_menu->AddList_Down(Window_Scene::Yes, "戻る", 7, GetColor(0, 0, 0), BACK_COLOR);

	//ファイルが存在しない場合のエラー
	CheckFileError_menu = std::make_shared<Window>(e, Window_Scene::CheckFileError, glm::ivec2(500, 500), glm::ivec2(600, 500));
	CheckFileError_menu->setTitle("ファイルが存在しません。",GetColor(0, 0, 0));
	CheckFileError_menu->AddList_Down(Window_Scene::Yes, "戻る", 7, GetColor(0, 0, 0), BACK_COLOR);



}

//更新
void StartMenu::Update()
{
	switch (mNowScene)
	{

		//メインメニュー
	case Window_Scene::Main:
	{
		Main_menu->Update(); //更新
	
		if (Main_menu->getChangeScene() != Window_Scene::Invalid) 
		{
			//新規作成
			if (Main_menu->getChangeScene() == Window_Scene::New_File)
			{
				mNowScene = Window_Scene::New_File; //新規作成ウインドウに移行
			}
			else if (Main_menu->getChangeScene() == Window_Scene::Edit_File)
			{
				//エディット
				mNowScene = Window_Scene::Edit_File; //編集ウインドウに移行
			}
			Main_menu->Reset();	//ウインドウをリセット
		}
	}break;
	
		//編集
	case Window_Scene::Edit_File:
	{
		EditFile_menu->Update(); //更新

		if (EditFile_menu->getChangeScene() != Window_Scene::Invalid)
		{
			std::vector<char*> tmp = EditFile_menu->getInputKeyData();	//キー入力を取得

			//決定
			if (EditFile_menu->getChangeScene() == Window_Scene::Yes)
			{
				if (CheckFile(tmp.at(0)) == true) 
				{
					//ファイルが存在する時

					memcpy(data.FileName, tmp.at(0), sizeof(data.FileName));	//ファイル名を設定	
					Type = Scene_Type::Game;								//Game シーンに移動
					data.EditMode = WRITE_EDIT;								//エディットモード

	
				}
				else {
					//ファイルが存在しない時
					memcpy(FileName, tmp.at(0), sizeof(FileName));	//ファイル名をコピー
					mNowScene = Window_Scene::CheckFileError; //ファイルがありませんエラーシーンに推移
				}
			}
			
			EditFile_menu->Reset();	//ウインドウをリセット
		}
	}break;

		//ファイルが存在しない時
	case Window_Scene::CheckFileError:
	{
		CheckFileError_menu->Update(); //更新

		if (CheckFileError_menu->getChangeScene() != Window_Scene::Invalid)
		{		
			//決定
			if (CheckFileError_menu->getChangeScene() == Window_Scene::Yes)
			{
				mNowScene = Window_Scene::Edit_File; //編集ファイル名入力ウインドウに戻る
			}
			CheckFileError_menu->Reset();	//ウインドウをリセット
		}
	}break;

		//新規作成
	case Window_Scene::New_File:
	{
		NewFile_menu->Update();	//更新

		if (NewFile_menu->getChangeScene() != Window_Scene::Invalid) 
		{
			//決定の時
			if (NewFile_menu->getChangeScene() == Window_Scene::Yes)
			{
				std::vector<char*> tmp = NewFile_menu->getInputKeyData();	//入力データを取得

				//ファイル名が存在するかどうか？
				if (CheckFile(tmp.at(0)) == true)
				{
					//存在する場合

					memcpy(FileName, tmp.at(0), sizeof(FileName));	//ファイル名を取得
					mNowScene = Window_Scene::Check;				//上書き確認ウインドウに移行

				}
				else {
					//存在しない場合

					memcpy(FileName, tmp.at(0), sizeof(data.FileName));	//ファイル名を取得
					mNowScene = Window_Scene::SizeSet; //サイズ設定ウインドウに移行

				}
			}

			NewFile_menu->Reset(); //ウインドウをリセット
		}
	}break;

		//サイズ指定
	case Window_Scene::SizeSet:
	{
		SizeSet_menu->Update();	//更新

		if (SizeSet_menu->getChangeScene() != Window_Scene::Invalid) {

			//決定
			if (SizeSet_menu->getChangeScene() == Window_Scene::Yes)
			{
				std::vector<char*> tmp = SizeSet_menu->getInputKeyData();	//入力データーを取得

				//サイズを設定
				data.StageSize.x = atoi(tmp.at(0));	//X
				data.StageSize.y = atoi(tmp.at(1));	//Y

				// ステージサイズが不正かどうか？
				if (data.StageSize.y > 0 && data.StageSize.x > 0)
				{
					memcpy(data.FileName, FileName, sizeof(data.FileName));	//ファイル名を設定	
					Type = Scene_Type::Game;								//Game シーンに移動
					data.EditMode = WRITE_NEW;								//エディットモード
				}
				else {
					//不正の時

					mNowScene = Window_Scene::SizeSetError;	//サイズ指定エラー画面に推移
				}
			}
			else if (SizeSet_menu->getChangeScene() == Window_Scene::No) {

				//戻る
				mNowScene = Window_Scene::New_File;	//新規作成画面に推移
			}

			SizeSet_menu->Reset(); //ウインドウをリセット
		}

	}break;

	//サイズ指定エラー
	case Window_Scene::SizeSetError:
	{
		SizeSetError_menu->Update();	//更新

		//戻る
		if (SizeSetError_menu->getChangeScene() != Window_Scene::Invalid)
		{
			mNowScene = Window_Scene::SizeSet; //サイズ指定ウインドウに移行

			SizeSetError_menu->Reset();	//ウインドウをリセット
		}

	}break;



	//上書き確認
	case Window_Scene::Check:
	{
		CheckFile_menu->Update();	//更新

		if (CheckFile_menu->getChangeScene() != Window_Scene::Invalid)
		{
			//決定
			if (CheckFile_menu->getChangeScene() == Window_Scene::Yes)
			{
				memcpy(data.FileName, FileName, sizeof(data.FileName));	//ファイル名を設定	
				Type = Scene_Type::Game;								//Game シーンに移動
				data.EditMode = WRITE_OVERRITE;							//エディットモード

			}else if (CheckFile_menu->getChangeScene() == Window_Scene::No)
			{
				//戻る
				mNowScene = Window_Scene::New_File;	//新規ファイル入力画面に戻る。
			}
			CheckFile_menu->Reset();	//ウインドウをリセット
		}

	}break;






	}

}

//描画
void StartMenu::Draw()
{
	switch (mNowScene) 
	{
		//メインメニュー
	case Window_Scene::Main:
	{
		Main_menu->Draw();
	}break;

	//メインメニュー
	case Window_Scene::New_File:
	{
		NewFile_menu->Draw();
	}break;

	//サイズ指定
	case Window_Scene::SizeSet:
	{
		SizeSet_menu->Draw();
	}break;
	
	//サイズ指定エラー
	case Window_Scene::SizeSetError:
	{
		SizeSetError_menu->Draw();
	}break;

	//上書きチェック確認
	case Window_Scene::Check:
	{
		CheckFile_menu->Draw();
	}break;

	//編集
	case Window_Scene::Edit_File:
	{
		EditFile_menu->Draw();
	}break;

	//編集
	case Window_Scene::CheckFileError:
	{
		CheckFileError_menu->Draw();
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


EditData StartMenu::getEditData()
{
	return data;
}

//デストラクタ
StartMenu::~StartMenu()
{

}

