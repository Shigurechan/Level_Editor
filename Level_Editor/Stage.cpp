#include "Stage.hpp"
#include "Control.hpp"
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

//�R���X�g���N�^
Stage::Stage(Entry* e)
{	
	Owner = e;	//Entry �N���X

	Config.StageFileName = "\0";
	Config.StageSize = glm::ivec2(0,0);


	mStage = std::make_shared <std::vector<std::vector<MapChip>>>();	//�X�e�[�W�z��		
}


void Stage::setMapChip(std::vector<SpriteData> data)
{
	SpriteList = data;
}

//�X�e�[�W�ɏ������ނ��ǂ����H
void Stage::WriteGrid(WriteData data, bool flag)
{
	if (flag == true)
	{
		mStage->at(data.GridPos.y).at(data.GridPos.x).setBinary(data.bin);
		mStage->at(data.GridPos.y).at(data.GridPos.x).setSprite(data.sprite);

	}
}


//�ǂݍ��݃o�C�i���t�@�C����
void Stage::setStage(ConfigData config)
{
	if (Config.StageFileName != config.StageFileName)
	{
//		printf("������\n");
		mStage->clear();
		Config.StageFileName = config.StageFileName;
		ReadFile(Config.StageFileName);
	}

}

//�o�C�i���t�@�C���ɏ�������
void Stage::setSaveFile(bool isSave)
{
	if (isSave == true)
	{
		WriteFile(Config.StageFileName);
	}
}


//�o�C�i���t�@�C���ɃX�e�[�W����������
void Stage::WriteFile(std::string file)
{
	FILE* fp = NULL;	//�t�@�C���|�C���^
	fopen_s(&fp, file.c_str(), "wb");	//�������ݐ�p�Ńo�C�i���t�@�C�����J��
	
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
void Stage::ReadFile(std::string file)
{
	//printf("�t�@�C���ǂݍ���: %s\n", data.FileName.c_str());

	FILE* fp = NULL;
	
		//printf("FileName: %s\n", data.FileName.c_str());
		fopen_s(&fp, file.c_str(), "rb");	//�ǂݍ��݃��[�h�Ńo�C�i���t�@�C�����J��
		if (fp != NULL)
		{

		//	printf("�t�@�C���ǂݍ��� aaa   \n");

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
						map.back().setSprite(SpriteList.at(b - 1).sprite);	//�X�v���C�g��ݒ�
					}
				}
				mStage->push_back(map);	//�X�e�[�W�ɏ�������
			}

			fclose(fp);	//�t�@�C�������B
		}
		else {
			printf("�t�@�C����ǂ߂܂���B");
		}
}



//�X�N���[��
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


	if (mStage->size() > 0) 
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
		for (int y = 0; y < mSize.y; y++)
		{
			for (int x = 0; x < mSize.x; x++)
			{
				mStage->at(y).at(x).Draw();
			}
		}

	}

}


//�f�X�g���N�^
Stage::~Stage()
{

}
