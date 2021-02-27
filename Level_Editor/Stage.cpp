#include "Stage.hpp"

//コンストラクタ
Stage::Stage()
{	
	mStage = std::make_shared < std::array<std::array<MapChip, STAGE_GRID_X>, STAGE_GRID_Y>>();


	//グリッドを初期化
	for (int y = 0; y < STAGE_GRID_Y; y++)
	{
		for (int x = 0; x < STAGE_GRID_X; x++)
		{
			mStage->at(y).at(x).setPosition(glm::ivec2(x * CELL,y * CELL));		
		}
	}
}

//グリッドに書き込む
void Stage::setGrid(MapChip chip)
{
	mStage->at(chip.getPosition().y).at(chip.getPosition().x).setBinary(chip.getBinary());	//バイナリを設定
	mStage->at(chip.getPosition().y).at(chip.getPosition().x).setSprite(chip.getSprite());	//スプライトを設定
}


//バイナリファイルにステージを書き込む
void Stage::WriteFile(EditData data)
{
	FILE* fp = NULL;

	fopen_s(&fp, data.FileName, "wb");	//書き込み専用でバイナリファイルを開く

	glm::ivec2 size(STAGE_GRID_X,STAGE_GRID_Y);
	
	//先頭８バイトはステージのサイズ
	fwrite(&size.x, sizeof(int), 1, fp);
	fwrite(&size.y, sizeof(int), 1, fp);



	for (int y = 0; y < STAGE_GRID_Y; y++)
	{
		for (int x = 0; x < STAGE_GRID_X; x++)
		{
			byte b = mStage->at(y).at(x).getBinary();
			fwrite(&b, sizeof(byte), 1, fp);
		}
	}

	fclose(fp);
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
	for (int y = 0; y < mStage->size(); y++)
	{
		for (int x = 0; x < mStage->at(y).size(); x++)
		{
			mStage->at(y).at(x).Draw();
		}
	}


}


//デストラクタ
Stage::~Stage()
{

}
