#include "Stage.hpp"
#include "Control.hpp"
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

//コンストラクタ
Stage::Stage(Entry* e)
{	
	Owner = e;	//Entry クラス

	Config.StageFileName = "\0";
	Config.StageSize = glm::ivec2(0,0);


	mStage = std::make_shared <std::vector<std::vector<MapChip>>>();	//ステージ配列		
}


void Stage::setMapChip(std::vector<SpriteData> data)
{
	SpriteList = data;
}

//ステージに書き込むかどうか？
void Stage::WriteGrid(WriteData data, bool flag)
{
	if (flag == true)
	{
		mStage->at(data.GridPos.y).at(data.GridPos.x).setBinary(data.bin);
		mStage->at(data.GridPos.y).at(data.GridPos.x).setSprite(data.sprite);

	}
}


//読み込みバイナリファイル名
void Stage::setStage(ConfigData config)
{
	if (Config.StageFileName != config.StageFileName)
	{
//		printf("あああ\n");
		mStage->clear();
		Config.StageFileName = config.StageFileName;
		ReadFile(Config.StageFileName);
	}

}

//バイナリファイルに書き込む
void Stage::setSaveFile(bool isSave)
{
	if (isSave == true)
	{
		WriteFile(Config.StageFileName);
	}
}


//バイナリファイルにステージを書き込む
void Stage::WriteFile(std::string file)
{
	FILE* fp = NULL;	//ファイルポインタ
	fopen_s(&fp, file.c_str(), "wb");	//書き込み専用でバイナリファイルを開く
	
	//先頭８バイトはステージのサイズ
	fwrite(&mSize.x, sizeof(int), 1, fp);	//Xサイズ
	fwrite(&mSize.y, sizeof(int), 1, fp);	//Yサイズ

	//ステージを生成
	for (int y = 0; y < mSize.y; y++)
	{
		for (int x = 0; x < mSize.x; x++)
		{
			byte b = mStage->at(y).at(x).getBinary();
			fwrite(&b, sizeof(byte), 1, fp);	//バイナリファイルに書き込む
		}
	}

	fclose(fp);		//ファイルクローズ
}


//バイナリファイルをステージに読み込む
void Stage::ReadFile(std::string file)
{
	//printf("ファイル読み込み: %s\n", data.FileName.c_str());

	FILE* fp = NULL;
	
		//printf("FileName: %s\n", data.FileName.c_str());
		fopen_s(&fp, file.c_str(), "rb");	//読み込みモードでバイナリファイルを開く
		if (fp != NULL)
		{

		//	printf("ファイル読み込み aaa   \n");

			//先頭８バイトはステージのサイズ
			fread(&mSize.x, sizeof(int), 1, fp);
			fread(&mSize.y, sizeof(int), 1, fp);

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
					if (b == 0x00) {
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
		else {
			printf("ファイルを読めません。");
		}
}



//スクロール
void Stage::Scroll(std::shared_ptr<Control> control)
{

#define OFFSET_RIGHT 21 
#define OFFSET_LEFT 4

#define OFFSET_DOWN 15 
#define OFFSET_UP 4



	//Right
	if ((control->getVector() == VECTOR_RIGHT) && ( control->getScreenGridPos().x > OFFSET_RIGHT))
	{
		//printf("Right\n");

		glm::ivec2 pos = control->getScreenGridPos();
		pos.x -= 1;
		control->setScreenGridPos(pos);

		for (int y = 0; y < mStage->size(); y++)
		{
			for (int x = 0; x < mStage->at(y).size(); x++)
			{
				glm::ivec2 p = mStage->at(y).at(x).getPosition();
				p.x -= CELL;
				mStage->at(y).at(x).setPosition(p);
			}
		}
	}

	//Left
	if ((control->getVector() == VECTOR_LEFT) && (control->getScreenGridPos().x < OFFSET_LEFT))
	{
		//printf("Left\n");

		glm::ivec2 pos = control->getScreenGridPos();
		pos.x += 1;
		control->setScreenGridPos(pos);


		for (int y = 0; y < mStage->size(); y++)
		{
			for (int x = 0; x < mStage->at(y).size(); x++)
			{
				glm::ivec2 p = mStage->at(y).at(x).getPosition();
				p.x += CELL;
				mStage->at(y).at(x).setPosition(p);
			}
		}
	}



	//Down
	if ((control->getVector() == VECTOR_DOWN) && (control->getScreenGridPos().y > OFFSET_DOWN))
	{
		//printf("Left\n");

		glm::ivec2 pos = control->getScreenGridPos();
		pos.y -= 1;
		control->setScreenGridPos(pos);

		for (int y = 0; y < mStage->size(); y++)
		{
			for (int x = 0; x < mStage->at(y).size(); x++)
			{
				glm::ivec2 p = mStage->at(y).at(x).getPosition();
				p.y -= CELL;
				mStage->at(y).at(x).setPosition(p);
			}
		}
	}

	//UP
	if ((control->getVector() == VECTOR_UP) && (control->getScreenGridPos().y < OFFSET_UP))
	{
		//printf("Left\n");

		glm::ivec2 pos = control->getScreenGridPos();
		pos.y += 1;
		control->setScreenGridPos(pos);

		for (int y = 0; y < mStage->size(); y++)
		{
			for (int x = 0; x < mStage->at(y).size(); x++)
			{
				glm::ivec2 p = mStage->at(y).at(x).getPosition();
				p.y += CELL;
				mStage->at(y).at(x).setPosition(p);
			}
		}
	}




#undef OFFSET_RIGHT 21 
#undef OFFSET_LEFT 4

#undef OFFSET_DOWN 15 
#undef OFFSET_UP 4



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
