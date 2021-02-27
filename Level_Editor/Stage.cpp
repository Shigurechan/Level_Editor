#include "Stage.hpp"

//�R���X�g���N�^
Stage::Stage()
{	
	mStage = std::make_shared < std::array<std::array<MapChip, STAGE_GRID_X>, STAGE_GRID_Y>>();


	//�O���b�h��������
	for (int y = 0; y < STAGE_GRID_Y; y++)
	{
		for (int x = 0; x < STAGE_GRID_X; x++)
		{
			mStage->at(y).at(x).setPosition(glm::ivec2(x * CELL,y * CELL));		
		}
	}
}

//�O���b�h�ɏ�������
void Stage::setGrid(MapChip chip)
{
	mStage->at(chip.getPosition().y).at(chip.getPosition().x).setBinary(chip.getBinary());	//�o�C�i����ݒ�
	mStage->at(chip.getPosition().y).at(chip.getPosition().x).setSprite(chip.getSprite());	//�X�v���C�g��ݒ�
}


//�o�C�i���t�@�C���ɃX�e�[�W����������
void Stage::WriteFile(EditData data)
{
	FILE* fp = NULL;

	fopen_s(&fp, data.FileName, "wb");	//�������ݐ�p�Ńo�C�i���t�@�C�����J��

	glm::ivec2 size(STAGE_GRID_X,STAGE_GRID_Y);
	
	//�擪�W�o�C�g�̓X�e�[�W�̃T�C�Y
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






//�X�V
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

//�`��
void Stage::Draw()
{

	//�O���b�h�`��
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

	//�Z���`��
	for (int y = 0; y < mStage->size(); y++)
	{
		for (int x = 0; x < mStage->at(y).size(); x++)
		{
			mStage->at(y).at(x).Draw();
		}
	}


}


//�f�X�g���N�^
Stage::~Stage()
{

}
