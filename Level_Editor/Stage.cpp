#include "Stage.hpp"
#include "Control.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

//�R���X�g���N�^
Stage::Stage(Entry* e)
{	
	Owner = e;	//Entry �N���X


	mStage = std::make_shared<std::vector<std::vector<MapChip>>>();	//�X�e�[�W�z��		

	mSize = glm::ivec2(100, 100);

	for (int y = 0; y < mSize.y; y++)
	{
		std::vector<MapChip> tmp;
		for (int x = 0; x < mSize.x; x++)
		{
			tmp.push_back(MapChip());
			tmp.back().setPosition(glm::ivec2(x * CELL, y * CELL));	//���W��ݒ�

		}


		mStage->push_back(tmp);

	}

}

void Stage::setMapChip(std::vector<SpriteData> data)
{
	SpriteList = data;
}

//�X�e�[�W�ɏ������ނ��ǂ����H
void Stage::WriteGrid(int sprite,byte bin,glm::ivec2 gridPos)
{
	
	if ( (gridPos.x >= 0 && gridPos.x < mSize.x) && (gridPos.y >= 0 && gridPos.y < mSize.y) )
	{
		//printf("������\n");
		mStage->at(gridPos.y).at(gridPos.x).setBinary(bin);
		mStage->at(gridPos.y).at(gridPos.x).setSprite(sprite);
	}
	
	
}



//�ǂݍ��݃o�C�i���t�@�C����
void Stage::setControl(std::shared_ptr<Control> control)
{
	if (control->sendData.isFileSelect == true)	//�t�@�C����ǂݍ���
	{
//		printf("��������\n");

	//	printf("%s\n",control->sendData.stageFileName.c_str());

		ReadFile(control->sendData.stageFileName);

		control->sendData.isFileSelect = false;

//		printf("����������\n");

	}
	else if (control->sendData.isWriteCell == true)	//�X�e�[�W�ɏ�������
	{
		//		printf("��������\n");
		printf("%d , %d \n", control->sendData.gridPos.x, control->sendData.gridPos.y);
		WriteGrid(control->sendData.sprite, control->sendData.bin, control->sendData.gridPos);

		control->sendData.isWriteCell = false;

		//		printf("����������\n");

	}
	else if (control->sendData.isDelete == true)	//�Z�����폜
	{
		WriteGrid(0, 0x00, control->sendData.gridPos);

		control->sendData.isDelete = false;

	}
	else if (control->sendData.isSave == true)	//�ۑ�
	{
		WriteFile(control->sendData.stageFileName);
		control->sendData.isSave = false;
	}
	else if (control->sendData.isNewFile == true)	//�V�K�쐬
	{
		
	//	printf("������\n");
		New_File(control->sendData.stageFileName);

		control->sendData.isNewFile = false;
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

	//�X�e�[�W�ɏ�������
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

	//printf("�t�@�C���ǂݍ��� \n");

	FILE* fp = NULL;
	//printf("�������������� %s",file.c_str());

	//printf("FileName: %s\n", data.FileName.c_str());
	//fopen_s(&fp, "test.bin", "rb");	//�ǂݍ��݃��[�h�Ńo�C�i���t�@�C�����J��
	fopen_s(&fp, file.c_str(), "rb");	//�ǂݍ��݃��[�h�Ńo�C�i���t�@�C�����J��
		if (fp != NULL)
		{

			printf("�t�@�C���ǂݍ���    \n");

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
//					printf("%d\n",b);
					map.back().setBinary(b);								//�o�C�i����ݒ�
					map.back().setPosition(glm::ivec2(x * CELL, y * CELL));	//���W��ݒ�

					//�I�u�W�F�N�g�������ꍇ
					if (b == 0x00) 
					{
						map.back().setSprite(0);	//�X�v���C�g�Ȃ�
					}
					else if (b > 0x00)
					{
						//�I�u�W�F�N�g������ꍇ
						//printf("%d\n", SpriteList.size());
						//printf("%d\n",b);
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

//		printf("iiiii\n");

}

//�V�����o�C�i���t�@�C�����쐬���邾��
void Stage::CreateNewFile(std::string name)
{
	FILE* fp = NULL;

	printf("FileName: %s\n", name.c_str());
	fopen_s(&fp, name.c_str(), "a+");

	if (fp == NULL) {
		printf("�쐬���s\n");
	}
	else {
		printf("�t�@�C���쐬\n");
		fclose(fp);
	}


}

//�V�K�쐬
void Stage::New_File(std::string name)
{
	CreateNewFile(name);


	//printf("X: %d\n", mSize.x);
	//printf("Y: %d\n", mSize.y);

	
	FILE* fp = NULL;	//�t�@�C���|�C���^
	fopen_s(&fp, name.c_str(), "wb");	//�������ݐ�p�Ńo�C�i���t�@�C�����J��

	int xx = 100;
	int yy = 100;

	if (fp != NULL) 
	{
		//�擪�W�o�C�g�̓X�e�[�W�̃T�C�Y
		fwrite(&xx, sizeof(int), 1, fp);	//X�T�C�Y
		fwrite(&yy, sizeof(int), 1, fp);	//Y�T�C�Y

		//�X�e�[�W�ɏ�������
		for (int y = 0; y < yy; y++)
		{
			for (int x = 0; x < xx; x++)
			{
				byte b = 0x00;
				fwrite(&b, sizeof(byte), 1, fp);	//�o�C�i���t�@�C���ɏ�������
			}
		}

		fclose(fp);		//�t�@�C���N���[�Y
	}
	
}





//������
void Stage::SetUp()
{

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
