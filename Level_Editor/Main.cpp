#include "DxLib.h"
#include <iostream>

#include "Fps.hpp"
#include "Input.hpp"
#include "Entry.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);
	
	ChangeWindowMode(TRUE);// ウインドウモードで起動	
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);//	画面サイズ


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)		
	{
		return -1;			
	}



	std::shared_ptr<Entry> scene = std::make_shared<Entry>();	//シーンクラス
	std::shared_ptr<Fps> fps = std::make_shared<Fps>();			//フレームレート
	std::shared_ptr<Input> input = std::make_shared<Input>();	//キー入力




	while (true)
	{
		fps->Update();					//FPS更新		
		SetDrawScreen(DX_SCREEN_BACK);	//バックバッファーに描画先を指定
		input->Update();				//キー入力を更新





		scene->Update();	//計算
		scene->Draw();		//描画



		//ESCキーで終了
		if (input->getKeyDown(KEY_INPUT_ESCAPE) == true)
		{
			break;
		}


		ScreenFlip();		//スワップバッファ
		ClearDrawScreen();	//画面をクリア
		ProcessMessage();	//メッセージ処理
		fps->Wait();		//FPS待機

	}
	
	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}