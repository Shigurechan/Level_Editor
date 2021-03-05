#include "Control.hpp"
#include "Entry.hpp"
#include "MapChip.hpp"
#include "Fps.hpp"

//�R���X�g���N�^
Control::Control(Entry* e, std::vector<SpriteData> sprite)
{
	Owner = e;				//Entry �N���X

	SpriteList = sprite;	//�X�v���C�g���X�g
	
	anim = std::make_shared<Animation>(2);	//�J�[�\���_�ŃA�j���[�V����

	menu = std::make_shared<Window>(Owner,Window_Scene::Main,glm::ivec2(100,100),glm::ivec2(300,300));
	menu->setTitle("�X�v���C�g�I��", GetColor(0, 0, 0));
	for (int i = 0; i < SpriteList.size(); i++)
	{
		menu->AddList_Down(Window_Scene::Yes,SpriteList.at(i).name, i,GetColor(0,0,0), GetColor(255, 255, 255));
	}






	//������
	HoldKey_X = false;
	HoldKey_Y = false;
	
	isWrite_cell = false;	//�������ނ��ǂ����H
	isWrite_File = false;	//�o�C�i���t�@�C���ɃX�e�[�W�����������ނ��ǂ����H

	//�������ݏ���ݒ�
	chip.setBinary(SpriteList.at(0).bin);		//�o�C�i��
	chip.setSprite(SpriteList.at(0).sprite);	//�X�v���C�g
	chip.setPosition(GridPos);					//�O���b�h���W

	mVector = VECTOR_LEFT;


	printf("X: %d\n", SCREEN_WIDTH / CELL);
	printf("Y: %d\n",SCREEN_HEIGHT / CELL);

	
}

//���W���w��
void Control::setPos(glm::ivec2 size)
{
	GridPos = glm::ivec2(15, 10);		//�O���b�h�̍��W
	Screen_GridPos = glm::ivec2(15, 10);	//�X�N���[���̃O���b�h���W

}

//����
glm::ivec2 Control::getVector()
{
	return mVector;
}

//�X�V
void Control::MenuUpdate() 
{
	menu->Update();

	if (menu->getChangeScene() == Window_Scene::Yes) 
	{
		byte c = menu->getItem();
		SpriteData data = SpriteList.at(c);
		chip.setBinary(data.bin);
		chip.setSprite(data.sprite);
		

		menu->Reset();	//�E�C���h�E�����Z�b�g
		isMenu = false;	//�G�f�B�^�[�ɖ߂�
	}


}

//�`��
void Control::MenuDraw()
{
	menu->Draw();

}


//�X�V
void Control::Update()
{
	int speed = CELL;
#define HOLD_TIME 30	//���������Ă��甽������܂ł̎���

	//���j���[��ʂ��J�� M �L�[
	if (Owner->InputKey->getKeyDown(KEY_INPUT_M) == true) {
		isMenu = !isMenu;
	}

	if (isMenu == false)
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



		//�ۑ��@P�@�L�[
		if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)
		{
			printf("�ۑ�\n");

			isWrite_File = true;	//�t�@�C����ۑ�
		}
		else
		{
			isWrite_File = false;
		}

		//�X�y�[�X�L�[�ŏ�������
		if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
		{
			chip.setPosition(GridPos);			//�O���b�h���W

			isWrite_cell = true;	//�X�e�[�W�ɏ�������
		}
		else {
			isWrite_cell = false;	//�X�e�[�W�������܂Ȃ�
		}

		//�X�e�[�W�̏������݂�����
		if (Owner->InputKey->getKeyDown(KEY_INPUT_DELETE) == true)
		{
			chip.setBinary(0x00);				//�o�C�i��
			chip.setSprite(0);					//�X�v���C�g		
			chip.setPosition(GridPos);			//�O���b�h���W

			isWrite_cell = true;	//�X�e�[�W�ɏ�������
		}

	}
	else if (isMenu == true)
	{
	//���j���[��ʎ�
//	printf("���j���[���\n");
	MenuUpdate();	//���j���[���
		



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


//�}�b�v�`�b�v���擾
MapChip Control::getChip()
{
	return chip;
}

//�O���b�h���W��ݒ�
void Control::setGridPos(glm::ivec2 g)
{
	GridPos = g;
}

//�`��
void Control::Draw()
{
	

	if (isMenu == false) 
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

}

//�f�X�g���N�^
Control::~Control()
{

}

