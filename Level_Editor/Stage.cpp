#include "Stage.hpp"
#include "Control.hpp"

//コンストラクタ
Stage::Stage(Entry* e, std::vector<int> spriteList)
{	
	Owner = e;
	SpriteList = spriteList;

	mStage = std::make_shared <std::vector<std::vector<MapChip>>>();
	
	
	
}

//グリッドに書き込む
void Stage::setGrid(MapChip chip, glm::ivec2 screen_grid)
{

	//スクリーン座標との位置補正
	glm::ivec2 pos = screen_grid;
	if (screen_grid.x > SCROLL_OFFSET_RIGHT)
	{		
		pos.x = SCROLL_OFFSET_RIGHT;		
	}else 	if (screen_grid.x < SCROLL_OFFSET_LEFT)
	{
		pos.x = SCROLL_OFFSET_LEFT;
	}
	else if (screen_grid.y > SCROLL_OFFSET_DOWN)
	{
		pos.y = SCROLL_OFFSET_DOWN;
	}
	else if (screen_grid.y < SCROLL_OFFSET_UP)
	{
		pos.y = SCROLL_OFFSET_UP;
	}




	try {
		mStage->at(chip.getPosition().y).at(chip.getPosition().x).setBinary(chip.getBinary());				//バイナリを設定
		mStage->at(chip.getPosition().y).at(chip.getPosition().x).setSprite(chip.getSprite());				//スプライトを設定	
		mStage->at(chip.getPosition().y).at(chip.getPosition().x).setPosition(pos * CELL);	//座標を設定
		
	}
	catch (std::exception e)
	{
		printf("setGrid():  %s\n",e.what());	//例外処理
	}
}


//ファイルを新規作成
void Stage::NewFile(EditData data)
{
	FILE* fp = NULL;	//ファイルポインタ
	fopen_s(&fp, data.FileName, "wb"); //書き込み専用モード
	fclose(fp);	//ファイルを閉じる

	mSize = data.StageSize;	//ステージサイズを設定

	//ステージを初期化
	std::vector<std::vector<MapChip>> stage(data.StageSize.y,std::vector<MapChip>(data.StageSize.x));
	for (int y = 0; y < mSize.y; y++)
	{
		for (int x = 0; x < mSize.x; x++)
		{
			stage.at(y).at(x).setPosition(glm::ivec2(x * CELL,y * CELL));
		}
	}
	*mStage = stage;



	WriteFile(data);	//バイナリファイルに書き込む
}

//バイナリファイルにステージを書き込む
void Stage::WriteFile(EditData data)
{
	FILE* fp = NULL;	//ファイルポインタ
	fopen_s(&fp, data.FileName, "wb");	//書き込み専用でバイナリファイルを開く
	
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
void Stage::ReadFile(EditData data)
{
	printf("ファイル読み込み\n");

	FILE* fp = NULL;
	printf("FileName: %s\n", data.FileName);
	fopen_s(&fp, data.FileName, "rb");	//読み込みモードでバイナリファイルを開く
		
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
				map.back().setSprite(SpriteList.at(b - 1));	//スプライトを設定
			}
		}
		mStage->push_back(map);	//ステージに書き込む
	}

	fclose(fp);	//ファイルを閉じる。
}

//スクロール
void Stage::Scroll(std::shared_ptr<Control> control)
{
	if (control->getScreenGridPos().x > SCROLL_OFFSET_RIGHT && control->getVector() == VECTOR_RIGHT)
	{
		//座標を前の座標に戻す。
		glm::ivec2 pos = control->getScreenGridPos();
		pos.x += -1;
		control->setScreenGridPos(pos);

		for (int y = 0; y < mStage->size(); y++)
		{
			for (int x = 0; x < mStage->at(y).size(); x++)
			{
				glm::ivec2 p = mStage->at(y).at(x).getPosition();
				p.x += -CELL;
				mStage->at(y).at(x).setPosition(p);		
			}
		}
	}else if (control->getScreenGridPos().x < SCROLL_OFFSET_LEFT && control->getVector() == VECTOR_LEFT)
	{
		//座標を前の座標に戻す。
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
	}else if (control->getScreenGridPos().y > SCROLL_OFFSET_DOWN && control->getVector() == VECTOR_DOWN)
	{
		//座標を前の座標に戻す。
		glm::ivec2 pos = control->getScreenGridPos();
		pos.y += -1;
		control->setScreenGridPos(pos);

		for (int y = 0; y < mStage->size(); y++)
		{
			for (int x = 0; x < mStage->at(y).size(); x++)
			{
				glm::ivec2 p = mStage->at(y).at(x).getPosition();
				p.y += -CELL;
				mStage->at(y).at(x).setPosition(p);
			}
		}
	}
	else if (control->getScreenGridPos().y < SCROLL_OFFSET_UP && control->getVector() == VECTOR_UP)
	{
		//座標を前の座標に戻す。
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


//デストラクタ
Stage::~Stage()
{

}
