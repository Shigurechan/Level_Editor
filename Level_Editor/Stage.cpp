#include "Stage.hpp"
#include "Control.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

//コンストラクタ
Stage::Stage(Entry* e)
{	
	Owner = e;	//Entry クラス

	mStage = std::make_shared<std::vector<std::vector<MapChip>>>();	//ステージ配列		

	mSize = glm::ivec2(100, 100);

	for (int y = 0; y < mSize.y; y++)
	{
		std::vector<MapChip> tmp;
		for (int x = 0; x < mSize.x; x++)
		{
			tmp.push_back(MapChip());
			tmp.back().setPosition(glm::ivec2(x * CELL, y * CELL));	//座標を設定

		}
		mStage->push_back(tmp);
	}

}

void Stage::setMapChip(std::vector<SpriteData> data)
{
	SpriteList = data;
}

//ステージに書き込むかどうか？
void Stage::WriteGrid(int sprite,byte bin,glm::ivec2 gridPos)
{
	//printf("%d\n",(int)bin);
	if ( (gridPos.x >= 0 && gridPos.x < mSize.x) && (gridPos.y >= 0 && gridPos.y < mSize.y) )
	{
		//printf("あああ\n");
		mStage->at(gridPos.y).at(gridPos.x).setBinary(bin);
		mStage->at(gridPos.y).at(gridPos.x).setSprite(sprite);
	}	
}

//　コントロール
void Stage::setControl(std::shared_ptr<Control> control)
{
	if (control->sendData.isFileSelect == true)	//ファイルを読み込む
	{
		ReadFile(control->sendData.stageFileName);
		control->sendData.isFileSelect = false;
	}
	else if (control->sendData.isWriteCell == true)	//ステージに書き込む
	{
		WriteGrid(control->sendData.sprite, control->sendData.bin, control->sendData.gridPos);
		control->sendData.isWriteCell = false;
	}
	else if (control->sendData.isDelete == true)	//セルを削除
	{
		WriteGrid(0, 0x00, control->sendData.gridPos);
		control->sendData.isDelete = false;
	}
	else if (control->sendData.isSave == true)	//保存
	{
		if (control->sendData.isNewFile == true)
		{
			New_File(control->sendData.stageFileName);	//ファイル作成
			WriteFile(control->sendData.stageFileName);	//ファイル書き込み
			control->sendData.isSave = false;
		}
		else
		{
			WriteFile(control->sendData.stageFileName);
			control->sendData.isSave = false;
		}
	}
	






}



//バイナリファイルにステージを書き込む
void Stage::WriteFile(std::string file)
{
	FILE* fp = NULL;	//ファイルポインタ
	fopen_s(&fp, file.c_str(), "wb");	//書き込み専用でバイナリファイルを開く

	if (fp != NULL) 
	{
		//先頭８バイトはステージのサイズ
		fwrite(&mSize.x, sizeof(int), 1, fp);	//Xサイズ
		fwrite(&mSize.y, sizeof(int), 1, fp);	//Yサイズ

		//ステージに書き込む
		for (int y = 0; y < mSize.y; y++)
		{
			for (int x = 0; x < mSize.x; x++)
			{
				byte b = mStage->at(y).at(x).getBinary();
		//		printf("%d\n",(int)b);
				fwrite(&b, sizeof(byte), 1, fp);	//バイナリファイルに書き込む
			}
		}

		fclose(fp);		//ファイルクローズ

	}
	else 
	{
		printf("ファイルに書き込めません\n");
	}
}


//バイナリファイルをステージに読み込む
void Stage::ReadFile(std::string file)
{

	//printf("ファイル読み込み \n");

	FILE* fp = NULL;
	
	mStage->clear();
	fopen_s(&fp, file.c_str(), "rb");	//読み込みモードでバイナリファイルを開く
	if (fp != NULL)
	{

		printf("ファイル読み込み    \n");

		//先頭８バイトはステージのサイズ
		fread(&mSize.x, sizeof(int), 1, fp);
		fread(&mSize.y, sizeof(int), 1, fp);

//		printf("mSize.x: %d\n", mSize.x);
//		printf("mSize.y: %d\n", mSize.y);


		//ステージの境界線フレームを設定	
		frame_up.start = glm::ivec2(-CELL,-CELL);
		frame_up.end = glm::ivec2(mSize.x * CELL, 0);
				
		frame_left.start = glm::ivec2(-CELL, -CELL);
		frame_left.end = glm::ivec2(0, mSize.y * CELL);
			
		frame_right.start = glm::ivec2(mSize.x * CELL, -CELL);
		frame_right.end = glm::ivec2((mSize.x * CELL) + CELL, mSize.y * CELL);

		frame_down.start = glm::ivec2(0, mSize.y * CELL);
		frame_down.end = glm::ivec2(mSize.x * CELL, (mSize.y * CELL) + CELL);


		std::vector<MapChip> map;
		for (int y = 0; y < mSize.y; y++)
		{
			map.clear();	//要素を空にする
			for (int x = 0; x < mSize.x; x++)
			{
				map.push_back(MapChip());	//要素を追加

				byte b = 0;
				fread(&b, sizeof(byte), 1, fp);							//バイナリファイルから１バイト読み込み
				map.back().setBinary(b);								//バイナリを設定
				map.back().setPosition(glm::ivec2(x * CELL, y * CELL));	//座標を設定

				//オブジェクトが無い場合
				if (b == 0x00) 
				{
					map.back().setSprite(0);	//スプライトなし
				}
				else if (b > 0x00)
				{
					//オブジェクトがある場合
					map.back().setSprite(SpriteList.at(b - 1).sprite);	//スプライトを設定
				}
			}
			mStage->push_back(map);	//ステージに書き込む
		}

		fclose(fp);	//ファイルを閉じる。
	}
	else 
	{
		printf("ファイルを読めません。\n`");
	}


}

//新しいバイナリファイルを作成するだけ
void Stage::CreateNewFile(std::string name)
{
	FILE* fp = NULL;

	printf("FileName: %s\n", name.c_str());
	fopen_s(&fp, name.c_str(), "w+");

	if (fp == NULL) 
	{
		printf("作成失敗\n");
	}
	else 
	{
		printf("ファイル作成\n");
		fclose(fp);
	}


}

//新規作成
void Stage::New_File(std::string name)
{
	CreateNewFile(name);	//ファイルを作成


	//printf("X: %d\n", mSize.x);
	//printf("Y: %d\n", mSize.y);

	
	FILE* fp = NULL;	//ファイルポインタ
	fopen_s(&fp, name.c_str(), "wb");	//書き込み専用でバイナリファイルを開く

	int xx = 100;
	int yy = 100;

	if (fp != NULL) 
	{
		//先頭８バイトはステージのサイズ
		fwrite(&xx, sizeof(int), 1, fp);	//Xサイズ
		fwrite(&yy, sizeof(int), 1, fp);	//Yサイズ

		//ステージに書き込む
		for (int y = 0; y < yy; y++)
		{
			for (int x = 0; x < xx; x++)
			{
				byte b = 0x00;
				fwrite(&b, sizeof(byte), 1, fp);	//バイナリファイルに書き込む
			}
		}

		fclose(fp);		//ファイルクローズ
	}
	else 
	{
		//printf("");
	}
	
}





//初期化
void Stage::SetUp()
{

}



//スクロール
void Stage::Scroll(std::shared_ptr<Control> control)
{

}


//更新
void Stage::Update()
{
	
	for (int y = 0; y < mStage->size(); y++)
	{
		for (int x = 0; x < mStage->at(y).size(); x++)
		{
			mStage->at(y).at(x).Update();
		}
	}

}

//描画
void Stage::Draw()
{
//	DrawFormatString(0,0,GetColor(0,0,0),"Size X : %d",mStage->size());




	if (mStage->size() > 0) 
	{

		DrawBox(frame_up.start.x, frame_up.start.y, frame_up.end.x, frame_up.end.y, GetColor(0, 255, 0), true);
		DrawBox(frame_left.start.x, frame_left.start.y, frame_left.end.x, frame_left.end.y, GetColor(0, 255, 0), true);
		DrawBox(frame_right.start.x, frame_right.start.y, frame_right.end.x, frame_right.end.y, GetColor(0, 255, 0), true);
		DrawBox(frame_down.start.x, frame_down.start.y, frame_down.end.x, frame_down.end.y, GetColor(0, 255, 0), true);


//		DrawBox(0,0, CELL,CELL, GetColor(0, 255, 0), true);


		//グリッド描画
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			if (y * CELL == SCREEN_HEIGHT) {
				DrawLine(0, (y * CELL) - 1, STAGE_WIDTH, (y * CELL) - 1, GetColor(0, 255, 0));
			}
			else {
				DrawLine(0, y * CELL, STAGE_WIDTH, y * CELL, GetColor(0, 255, 0));

			}
		}

		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			if (x * CELL == SCREEN_WIDTH)
			{
				DrawLine((x * CELL) - 1, 0, (x * CELL) - 1, STAGE_HEIGHT, GetColor(0, 255, 0));

			}
			else {
				DrawLine(x * CELL, 0, x * CELL, STAGE_HEIGHT, GetColor(0, 255, 0));
			}
		}

		//セル描画
		for (int y = 0; y < mSize.y; y++)
		{
			for (int x = 0; x < mSize.x; x++)
			{
				mStage->at(y).at(x).Draw();
			}
		}



		

	}

}


//デストラクタ
Stage::~Stage()
{

}
