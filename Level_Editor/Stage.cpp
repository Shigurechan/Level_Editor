#include "Stage.hpp"
#include "Control.hpp"

//�R���X�g���N�^
Stage::Stage(Entry* e, std::vector<int> spriteList)
{	
	Owner = e;
	SpriteList = spriteList;

	mStage = std::make_shared <std::vector<std::vector<MapChip>>>();
	
	
	
}

//�O���b�h�ɏ�������
void Stage::setGrid(MapChip chip, glm::ivec2 screen_grid)
{

	//�X�N���[�����W�Ƃ̈ʒu�␳
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
		mStage->at(chip.getPosition().y).at(chip.getPosition().x).setBinary(chip.getBinary());				//�o�C�i����ݒ�
		mStage->at(chip.getPosition().y).at(chip.getPosition().x).setSprite(chip.getSprite());				//�X�v���C�g��ݒ�	
		mStage->at(chip.getPosition().y).at(chip.getPosition().x).setPosition(pos * CELL);	//���W��ݒ�
		
	}
	catch (std::exception e)
	{
		printf("setGrid():  %s\n",e.what());	//��O����
	}
}


//�t�@�C����V�K�쐬
void Stage::NewFile(EditData data)
{
	FILE* fp = NULL;	//�t�@�C���|�C���^
	fopen_s(&fp, data.FileName, "wb"); //�������ݐ�p���[�h
	fclose(fp);	//�t�@�C�������

	mSize = data.StageSize;	//�X�e�[�W�T�C�Y��ݒ�

	//�X�e�[�W��������
	std::vector<std::vector<MapChip>> stage(data.StageSize.y,std::vector<MapChip>(data.StageSize.x));
	for (int y = 0; y < mSize.y; y++)
	{
		for (int x = 0; x < mSize.x; x++)
		{
			stage.at(y).at(x).setPosition(glm::ivec2(x * CELL,y * CELL));
		}
	}
	*mStage = stage;



	WriteFile(data);	//�o�C�i���t�@�C���ɏ�������
}

//�o�C�i���t�@�C���ɃX�e�[�W����������
void Stage::WriteFile(EditData data)
{
	FILE* fp = NULL;	//�t�@�C���|�C���^
	fopen_s(&fp, data.FileName, "wb");	//�������ݐ�p�Ńo�C�i���t�@�C�����J��
	
	//�擪�W�o�C�g�̓X�e�[�W�̃T�C�Y
	fwrite(&mSize.x, sizeof(int), 1, fp);	//X�T�C�Y
	fwrite(&mSize.y, sizeof(int), 1, fp);	//Y�T�C�Y

	//�X�e�[�W�𐶐�
	for (int y = 0; y < mSize.y; y++)
	{
		for (int x = 0; x < mSize.x; x++)
		{
			byte b = mStage->at(y).at(x).getBinary();
			fwrite(&b, sizeof(byte), 1, fp);	//�o�C�i���t�@�C���ɏ�������
		}
	}

	fclose(fp);		//�t�@�C���N���[�Y
}

//�o�C�i���t�@�C�����X�e�[�W�ɓǂݍ���
void Stage::ReadFile(EditData data)
{
	printf("�t�@�C���ǂݍ���\n");

	FILE* fp = NULL;
	printf("FileName: %s\n", data.FileName);
	fopen_s(&fp, data.FileName, "rb");	//�ǂݍ��݃��[�h�Ńo�C�i���t�@�C�����J��
		
	//�擪�W�o�C�g�̓X�e�[�W�̃T�C�Y
	fread(&mSize.x, sizeof(int), 1, fp);
	fread(&mSize.y, sizeof(int), 1, fp);
	
	std::vector<MapChip> map;
	for (int y = 0; y < mSize.y; y++)
	{	
		map.clear();	//�v�f����ɂ���
		for (int x = 0; x < mSize.x; x++)
		{
			map.push_back(MapChip());	//�v�f��ǉ�

			byte b = 0;
			fread(&b, sizeof(byte), 1, fp);							//�o�C�i���t�@�C������P�o�C�g�ǂݍ���

			map.back().setBinary(b);								//�o�C�i����ݒ�
			map.back().setPosition(glm::ivec2(x * CELL, y * CELL));	//���W��ݒ�

			//�I�u�W�F�N�g�������ꍇ
			if (b == 0x00) {
				map.back().setSprite(0);	//�X�v���C�g�Ȃ�
			}
			else if (b > 0x00)
			{
				//�I�u�W�F�N�g������ꍇ
				map.back().setSprite(SpriteList.at(b - 1));	//�X�v���C�g��ݒ�
			}
		}
		mStage->push_back(map);	//�X�e�[�W�ɏ�������
	}

	fclose(fp);	//�t�@�C�������B
}

//�X�N���[��
void Stage::Scroll(std::shared_ptr<Control> control)
{
	if (control->getScreenGridPos().x > SCROLL_OFFSET_RIGHT && control->getVector() == VECTOR_RIGHT)
	{
		//���W��O�̍��W�ɖ߂��B
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
		//���W��O�̍��W�ɖ߂��B
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
		//���W��O�̍��W�ɖ߂��B
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
		//���W��O�̍��W�ɖ߂��B
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
//	DrawFormatString(0,0,GetColor(0,0,0),"Size X : %d",mStage->size());



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
	for (int y = 0; y < mSize.y; y++)
	{
		for (int x = 0; x < mSize.x; x++)
		{
			mStage->at(y).at(x).Draw();
		}
	}


}


//�f�X�g���N�^
Stage::~Stage()
{

}
