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
		if ( (data.GridPos.x >= 0 && data.GridPos.x < mSize.x) && (data.GridPos.y >= 0 && data.GridPos.y < mSize.y) )
		{
			printf("������\n");
			mStage->at(data.GridPos.y).at(data.GridPos.x).setBinary(data.bin);
			mStage->at(data.GridPos.y).at(data.GridPos.x).setSprite(data.sprite);
		}
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

	printf("�t�@�C���ǂݍ��� \n");

	FILE* fp = NULL;
	
		//printf("FileName: %s\n", data.FileName.c_str());
		fopen_s(&fp, file.c_str(), "rb");	//�ǂݍ��݃��[�h�Ńo�C�i���t�@�C�����J��
		if (fp != NULL)
		{

		//	printf("�t�@�C���ǂݍ��� aaa   \n");

			//�擪�W�o�C�g�̓X�e�[�W�̃T�C�Y
			fread(&mSize.x, sizeof(int), 1, fp);
			fread(&mSize.y, sizeof(int), 1, fp);

			printf("mSize.x: %d\n", mSize.x);
			printf("mSize.y: %d\n", mSize.y);


			//�X�e�[�W�̋��E���t���[����ݒ�
			
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

		//�O���b�g�͈͓��̏ꍇ
		if ((control->getGridPos().x >= 0 && control->getGridPos().x < mSize.x) && (control->getGridPos().y >= 0 && control->getGridPos().y < mSize.y))
		{

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



			//���E���t���[���ړ�
			frame_right.start.x += -CELL;
			frame_right.end.x += -CELL;


			frame_left.start.x += -CELL;
			frame_left.end.x += -CELL;
		}
		else {
			if (control->getGridPos().x > mSize.x - 1)
			{
				//�O���b�h�␳
				glm::ivec2 p = control->getGridPos();
				p.x = mSize.x - 1;
				control->setGridPos(p);

				//�X�N���[���O���b�h�␳
				glm::ivec2 pos = control->getScreenGridPos();
				pos.x += -1;
				control->setScreenGridPos(pos);
			}


		}
	}

	//Left
	if ((control->getVector() == VECTOR_LEFT) && (control->getScreenGridPos().x < OFFSET_LEFT))
	{
		//printf("Left\n");
		if ((control->getGridPos().x >= 0 && control->getGridPos().x < mSize.x) && (control->getGridPos().y >= 0 && control->getGridPos().y < mSize.y))
		{



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

			//���E���t���[���ړ�
			frame_left.start.x += CELL;
			frame_left.end.x += CELL;

			frame_right.start.x += CELL;
			frame_right.end.x += CELL;
		}
		else 
		{
			if (control->getGridPos().x < 0) 
			{
				//�O���b�h�␳
				glm::ivec2 p = control->getGridPos();
				p.x = 0;
				control->setGridPos(p);

				//�X�N���[���O���b�h�␳
				glm::ivec2 pos = control->getScreenGridPos();
				pos.x += 1;
				control->setScreenGridPos(pos);
			}

		}
	}



	//Down
	if ((control->getVector() == VECTOR_DOWN) && (control->getScreenGridPos().y > OFFSET_DOWN))
	{
		//printf("Left\n");
		if ((control->getGridPos().x >= 0 && control->getGridPos().x < mSize.x) && (control->getGridPos().y >= 0 && control->getGridPos().y < mSize.y))
		{

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


			//���E���t���[���ړ�
			frame_up.start.y += -CELL;
			frame_up.end.y += -CELL;

			frame_down.start.y += -CELL;
			frame_down.end.y += -CELL;

		}
		else 
		{
			if (control->getGridPos().y > mSize.y - 1)
			{
				//�O���b�h�␳
				glm::ivec2 p = control->getGridPos();
				p.y = mSize.y - 1;
				control->setGridPos(p);

				//�X�N���[���O���b�h�␳
				glm::ivec2 pos = control->getScreenGridPos();
				pos.y += -1;
				control->setScreenGridPos(pos);
			}

		}
	}

	//UP
	if ((control->getVector() == VECTOR_UP) && (control->getScreenGridPos().y < OFFSET_UP))
	{
		//printf("Left\n");
		if ((control->getGridPos().x >= 0 && control->getGridPos().x < mSize.x) && (control->getGridPos().y >= 0 && control->getGridPos().y < mSize.y))
		{
		
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


			//���E���t���[���ړ�
			frame_up.start.y += CELL;
			frame_up.end.y += CELL;

			frame_down.start.y += CELL;
			frame_down.end.y += CELL;
		}
		else 
		{
			if (control->getGridPos().y < 0) 
			{
				//�O���b�g�␳
				glm::ivec2 p = control->getGridPos();
				p.y = 0;
				control->setGridPos(p);

				//�X�N���[���O���b�h�␳
				glm::ivec2 pos = control->getScreenGridPos();
				pos.y += 1;
				control->setScreenGridPos(pos);
			}
		}
	}

#undef OFFSET_RIGHT
#undef OFFSET_LEFT
#undef OFFSET_DOWN
#undef OFFSET_UP

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

		DrawBox(frame_up.start.x, frame_up.start.y, frame_up.end.x, frame_up.end.y, GetColor(0, 255, 0), true);
		DrawBox(frame_left.start.x, frame_left.start.y, frame_left.end.x, frame_left.end.y, GetColor(0, 255, 0), true);
		DrawBox(frame_right.start.x, frame_right.start.y, frame_right.end.x, frame_right.end.y, GetColor(0, 255, 0), true);
		DrawBox(frame_down.start.x, frame_down.start.y, frame_down.end.x, frame_down.end.y, GetColor(0, 255, 0), true);


//		DrawBox(0,0, CELL,CELL, GetColor(0, 255, 0), true);


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
