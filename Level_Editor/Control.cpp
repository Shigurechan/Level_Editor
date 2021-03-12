#include "Control.hpp"
#include "Entry.hpp"
#include "MapChip.hpp"
#include "Fps.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

//�R���X�g���N�^
Control::Control(Entry* e)
{

	Owner = e;				//Entry �N���X

	printf("X %d\n", SCREEN_WIDTH / CELL);
	printf("Y %d\n",SCREEN_HEIGHT / CELL);


	
	// �`�b�v�I��
	Chip_Menu = std::make_shared<Window>(Owner, Window_Scene::ChipSelect, glm::ivec2(100, 100), glm::ivec2(300, 300));
	Chip_Menu->setTitle("�}�b�v�`�b�v��I��", GetColor(0, 0, 0));

	//�X�e�[�W�I��
	Stage_Menu = std::make_shared<Window>(Owner, Window_Scene::StageSelect, glm::ivec2(100, 100), glm::ivec2(300, 300));
	Stage_Menu->setTitle("�}�b�v��I��", GetColor(0, 0, 0));

	ChipData.GridPos = glm::ivec2(0,0);


	GridPos = glm::ivec2(13,9);			//�O���b�h���W
	Screen_GridPos = GridPos;	//�X�N���[�����W

	// ################ �}�b�v�`�b�v�����[�h�@################ 
	std::string filename = "\\Assets\\Sprite";	//�o�C�i���t�@�C���̊i�[�f�B���N�g��
	std::string path = fs::current_path().string();
	path = path + filename;
	
	if (fs::exists(path) == false)
	{
		printf("Sprite_Data�t�H���_�����݂��Ȃ����ߐV�K�쐬���܂����B\n");
		fs::create_directory(path);
	}
	else
	{
		int a = 0;
		printf("�}�b�v�`�b�v���t�@�C�������[�h\n");
		for (fs::directory_iterator itr = fs::directory_iterator(path); itr != fs::directory_iterator(); itr++)
		{
			printf("%s\n", itr->path().filename().string().c_str());	//�f�o�b�O
		

			SpriteData data;

			// 
			if (itr->path().filename().string() == "Block.png")
			{
				data.bin = (byte)MapObject::Block;
				data.name = itr->path().filename().string();
				data.sprite = Owner->LoadSprite(itr->path().string().c_str());

			}
			else if (itr->path().filename().string() == "Brick.png")
			{
				data.bin = (byte)MapObject::Brick;
				data.name = itr->path().filename().string();
				data.sprite = Owner->LoadSprite(itr->path().string().c_str());
			}
			else if (itr->path().filename().string() == "Shop.png")
			{
				data.bin = (byte)MapObject::Shop;
				data.name = itr->path().filename().string();
				data.sprite = Owner->LoadSprite(itr->path().string().c_str());
			}
			else if (itr->path().filename().string() == "Enemy.png")
			{
				data.bin = (byte)MapObject::Enemy;
				data.name = itr->path().filename().string();
				data.sprite = Owner->LoadSprite(itr->path().string().c_str());
			}
			else
			{

				printf("�V�������ݒ�̃}�b�v�`�b�v�����o %s\n", itr->path().filename().string().c_str());
			}

			SpriteList.push_back(data);	//�}�b�v�`�b�v����ݒ�

			//�t�@�C�����X�g
			Chip_Menu->AddList_Down(Window_Scene::None, data.name, a, GetColor(0, 0, 0), GetColor(255,255,255));	//���j���[
			a++;

		}
		printf("\n\n");
	}
	// ################ �@################ 


	// ################ �X�e�[�W�����[�h�@################ 
	filename = "\\Stage_Data";	//�o�C�i���t�@�C���̊i�[�f�B���N�g��
	path = fs::current_path().string();
	path = path + filename;
	if (fs::exists(path) == false)
	{
		printf("Stage_Data�t�H���_�����݂��Ȃ����ߐV�K�쐬���܂����B\n");
		fs::create_directory(path);
	}
	else
	{
		printf("�o�C�i���t�@�C�������[�h\n");
		int a = 0;
		for (fs::directory_iterator itr = fs::directory_iterator(path); itr != fs::directory_iterator(); itr++)
		{
			printf("%s\n", itr->path().string().c_str());
			StageFileNameList.push_back(itr->path().string());
			Stage_Menu->AddList_Down(Window_Scene::None, itr->path().filename().string(), a, GetColor(0, 0, 0), GetColor(255, 255, 255));	//�E�C���h�E


			a++;
		}
		printf("\n\n");
	}
	// ################ �@################ 


	//������
	HoldKey_X = false;
	HoldKey_Y = false;
	
	isWrite_cell = false;	//�������ނ��ǂ����H
	isSave = false;		//�t�@�C���ɃZ�[�u���邩�ǂ����H

	mVector = VECTOR_LEFT;

	ChipData.bin = SpriteList.at(0).bin;			//�o�C�i��
	ChipData.sprite = SpriteList.at(0).sprite;	//�X�v���C�g


	// ���j���[���
	isChipSelect = false;	//�`�b�v�I��
	isStageSelect = true;	//�X�e�[�W�I��
	isChangeSize = false;	//�T�C�Y�I��
	isSave = false;			//�Z�[�u����

}

//������
void Control::SetUp()
{
	
}


//����
glm::ivec2 Control::getVector()
{
	return mVector;
}

//���j���[�X�V
void Control::MenuUpdate() 
{
	//�X�e�[�W�I��
	if (isStageSelect == true) 
	{
		Stage_Menu->Update();
		if (Stage_Menu->getChangeScene() != Window_Scene::Invalid)
		{
			Config.StageFileName = StageFileNameList.at(Stage_Menu->getItem());	//�R���t�B�O�f�[�^�ɃX�e�[�W����ݒ�		
			Stage_Menu->Reset();
			isStageSelect = false;
		}
	}
	else if (isChipSelect == true)
	{
		// �`�b�v�I��
		Chip_Menu->Update();

		if (Chip_Menu->getChangeScene() != Window_Scene::Invalid)
		{
			ChipData.bin = SpriteList.at(Chip_Menu->getItem()).bin;			//�o�C�i��
			ChipData.sprite = SpriteList.at(Chip_Menu->getItem()).sprite;	//�X�v���C�g
			//ChipData.GridPos = GridPos;										//���W

			Chip_Menu->Reset();
			isChipSelect = false;
		}
	}








}

//�R���t�B�O�f�[�^���擾
ConfigData Control::getConfig()
{
	return Config;
}


//�}�b�v�`�b�v���擾
std::vector<SpriteData> Control::getMapChip()
{
	return SpriteList;
}



//���j���[�`��
void Control::MenuDraw()
{
	//�X�e�[�W�I��
	if (isStageSelect == true) 
	{
		Stage_Menu->Draw();
	}
	else if (isChipSelect == true)
	{
		// �`�b�v�I��
		Chip_Menu->Draw();
	}



}





//�X�V
void Control::Update()
{
	int speed = CELL;
#define HOLD_TIME 30	//���������Ă��甽������܂ł̎���

	//���j���[��ʂ��J��
	if (Owner->InputKey->getKeyDown(KEY_INPUT_C) == true) 
	{
		isChipSelect = !isChipSelect;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_M) == true)
	{
		isStageSelect = !isStageSelect;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_S) == true)
	{
		isChangeSize = !isChangeSize;
	}

	//P �L�[�ŕۑ�
	if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)
	{
		isSave = true;
	}
	else {
		isSave = false;
	}





	//�G�f�B�^����
	if (isChipSelect == false && isChangeSize == false && isStageSelect == false)
	{
		//Left Right
		if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > 0)
		{
			//������
			if (HoldKey_X == false)
			{
				GridPos.x += -1;		//�X�e�[�W���W
				Screen_GridPos.x += -1;	//�X�N���[�����W
				HoldKey_X = true;		//������
				mVector = VECTOR_LEFT;	//����
			}
			else {
				if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > HOLD_TIME)
				{
					HoldKey_X = false;	//������
				}
			}
		}
		else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
		{
			//������
			if (HoldKey_X == false)
			{
				GridPos.x += 1;			//�X�e�[�W���W
				Screen_GridPos.x += 1;	//�X�N���[�����W
				HoldKey_X = true;		//������
				mVector = VECTOR_RIGHT;	//����

			}
			else {
				if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > HOLD_TIME)
				{
					HoldKey_X = false;	//������
				}
			}
		}
		else {
			HoldKey_X = false;	//������

			mVector = glm::ivec2(0, 0);	//�����Ȃ�
		}


		//Up Down
		if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > 0)
		{
			//������
			if (HoldKey_Y == false)
			{
				GridPos.y += -1;		//�X�e�[�W���W
				Screen_GridPos.y += -1;	//�X�N���[�����W
				HoldKey_Y = true;		//������
				mVector = VECTOR_UP;	//����

			}
			else {
				if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > HOLD_TIME)
				{
					HoldKey_Y = false;	//������
				}
			}
		}
		else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
		{
			//������
			if (HoldKey_Y == false)
			{
				GridPos.y += 1;			//�X�e�[�W���W
				Screen_GridPos.y += 1;	//�X�N���[�����W
				HoldKey_Y = true;		//������
				mVector = VECTOR_DOWN;	//����

			}
			else {
				if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > HOLD_TIME)
				{
					HoldKey_Y = false;	//������
				}
			}
		}
		else {
			HoldKey_Y = false;	//������

		}



	
		//�X�y�[�X�L�[�ŏ�������
		if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
		{
			ChipData.GridPos = GridPos;	//�O���b�h���W

			isWrite_cell = true;	//�X�e�[�W�ɏ�������
		}
		else {
			isWrite_cell = false;	//�X�e�[�W�������܂Ȃ�
		}

		//�X�e�[�W�̏������݂�����
		if (Owner->InputKey->getKeyDown(KEY_INPUT_DELETE) == true)
		{
			
			isWrite_cell = true;	//�X�e�[�W�ɏ�������
		}

	}
	else
	{
		MenuUpdate();
	}




	
}

//���݂̃O���b�g���W
glm::ivec2 Control::getGridPos()
{
	return GridPos;
}

//�X�N���[���̃O���b�h���W���擾
glm::ivec2 Control::getScreenGridPos()
{
	return Screen_GridPos;
}


//�X�N���[���̃O���b�h���W��ݒ�
void Control::setScreenGridPos(glm::ivec2 p)
{
	Screen_GridPos = p;
}

//�������݃f�[�^���擾
WriteData Control::getWriteData()
{
	return ChipData;
}


//�O���b�h���W��ݒ�
void Control::setGridPos(glm::ivec2 g)
{
	GridPos = g;
}

//�`��
void Control::Draw()
{
	

	if (isChipSelect == false && isChangeSize == false && isStageSelect == false)
	{
		//��`�`��
		if (Fps::getFrame() % 15 == 0)
		{
			//DrawBox(GridPos.x * CELL, GridPos.y * CELL, (GridPos.x * CELL) + CELL, (GridPos.y * CELL) + CELL, GetColor(0, 255, 0), true);
			DrawBox(Screen_GridPos.x * CELL, Screen_GridPos.y * CELL, (Screen_GridPos.x * CELL) + CELL, (Screen_GridPos.y * CELL) + CELL, GetColor(0, 255, 0), true);

		}

		DrawFormatString(400, 0, GetColor(255, 255, 255), "GridPos: %d , %d ", GridPos.x, GridPos.y);
		DrawFormatString(400, 32, GetColor(255, 255, 255), "Screen_GridPos: %d , %d ", Screen_GridPos.x, Screen_GridPos.y);
	}
	else {

		MenuDraw();
	}


	//�Z�[�u�\��
	if (isSave == true)
	{
		DrawFormatString(0,0, GetColor(255, 255, 255), "SAVED"); 
	}




}

//�f�X�g���N�^
Control::~Control()
{

}

