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

	//�}�b�v�`�b�v�I��
	chipMenu = std::make_shared<Window>(Owner,Window_Scene::ChipSelect,glm::ivec2(100,100), glm::ivec2(200, 200));
	chipMenu->setTitle("�}�b�v�`�b�v��I��",GetColor(0,0,0));


	GridPos = glm::ivec2(13,9);	//�O���b�h���W
	Screen_GridPos = GridPos;	//�X�N���[�����W

	// ################ �}�b�v�`�b�v�����[�h�@################ 
	std::string filename = "MapChip";	//�o�C�i���t�@�C���̊i�[�f�B���N�g��
	std::string path = fs::current_path().string();
	path = path + "\\" + filename;
	
	if (fs::exists(path) == false)
	{
		printf("Sprite_Data�t�H���_�����݂��Ȃ����ߐV�K�쐬���܂����B\n");
		fs::create_directory(path);
	}
	else
	{
		int num = 0;
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
			chipMenu->AddList_Down(Window_Scene::None, data.name, num, GetColor(0, 0, 0),GetColor(255, 255, 255),0);
			num++;

		}
		printf("\n\n");
	}
	// ################ �@################ 

	//������
	HoldKey_X = false;
	HoldKey_Y = false;
	
	mVector = VECTOR_LEFT;	//����




	//���j���[�؂�ւ�
	isMenu = false;	//���j���[

	isStart = false;			//�X�^�[�g���
	isFileSelect = false;		//�t�@�C���؂�ւ�
	isStageResize = false;		//�X�e�[�W�T�C�Y�����T�C�Y
	isMapChipSelect = false;		//�}�b�v�`�b�v��؂�ւ�
	isNewFile = false;			//�V�����t�@�C�����쐬


}

//������
void Control::SetUp()
{
	
}

//�X�v���C�g�f�[�^���擾
std::vector<SpriteData> Control::getSpriteData()
{
	return SpriteList;
}

//����
glm::ivec2 Control::getVector()
{
	return mVector;
}

//���j���[�X�V
void Control::MenuUpdate()
{
	if (isMapChipSelect == true)
	{
		chipMenu->Update();
		if (chipMenu->getChangeScene() != Window_Scene::Invalid)
		{
			sendData.sprite = SpriteList.at((int)chipMenu->getItem()).sprite;	//�X�v���C�g
			sendData.bin = SpriteList.at((int)chipMenu->getItem()).bin;			//�o�C�i��

			chipMenu->Reset();	//���Z�b�g
			isMapChipSelect = false;
		}
	}

	


}



//���j���[�`��
void Control::MenuDraw()
{
	if (isMapChipSelect == true)
	{
		chipMenu->Draw();
	}
	
}





//�X�V
void Control::Update()
{
	int speed = CELL;
#define HOLD_TIME 30	//���������Ă��甽������܂ł̎���

	//���j���[��ʂ��J��
	if (Owner->InputKey->getKeyDown(KEY_INPUT_C) == true) //�}�b�v�`�b�v��I��
	{
		isMapChipSelect = !isMapChipSelect;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_M) == true)	//�X�e�[�W�t�@�C����I��
	{
		isFileSelect = !isFileSelect;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_S) == true)	//�T�C�Y��ύX
	{
		isStageResize = !isStageResize;
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)	//�ۑ�
	{
		
		sendData.isSave = true;
	}
	else 
	{
		
	}





	//�G�f�B�^����
	
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
		sendData.isWriteCell = true;	//�X�e�[�W�ɏ�������
		sendData.gridPos = GridPos;		//�O���b�h���W��ݒ�
	} 
		

	//�X�e�[�W�̏������݂�����
	if (Owner->InputKey->getKeyDown(KEY_INPUT_DELETE) == true)
	{
		sendData.isDelete = true;
		sendData.gridPos = GridPos;		//�O���b�h���W��ݒ�

	}
		
	
	

	MenuUpdate();


	
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



//�O���b�h���W��ݒ�
void Control::setGridPos(glm::ivec2 g)
{
	GridPos = g;
}

//�`��
void Control::Draw()
{
	

	if (isMapChipSelect == false && isFileSelect == false && isStageResize == false)
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

		//printf("������\n");
		MenuDraw();	//���j���[�`��
	}





}

//�f�X�g���N�^
Control::~Control()
{

}

