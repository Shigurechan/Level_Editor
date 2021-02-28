#include "Control.hpp"
#include "Entry.hpp"
#include "MapChip.hpp"
#include "Fps.hpp"

//�R���X�g���N�^
Control::Control(Entry* e, std::vector<int> sprite)
{
	printf("X: %d\n", (SCREEN_WIDTH / CELL) / 2 * CELL);


	Owner = e; //Entry �N���X
	SpriteList = sprite;	//�X�v���C�g���X�g

	CursorPos = glm::ivec2((SCREEN_WIDTH / CELL) / 2 * CELL, (SCREEN_HEIGHT / CELL) / 2 * CELL);	//�J�[�\�����W
	GridPos = glm::ivec2(CursorPos.x / CELL, CursorPos.y / CELL);		//�O���b�h�̍��W

	anim = std::make_shared<Animation>(2);	//�J�[�\���_�ŃA�j���[�V����

	//������
	HoldKey_X = false;
	HoldKey_Y = false;

	isWrite_cell = false;	//�������ނ��ǂ����H
	isWrite_File = false;	//�o�C�i���t�@�C���ɃX�e�[�W�����������ނ��ǂ����H

	//�������ݏ���ݒ�
	chip.setBinary(0x01);				//�o�C�i��
	chip.setSprite(SpriteList.at(0));	//�X�v���C�g
	chip.setPosition(GridPos);			//�O���b�h���W



	
}

//�X�V
void Control::Update()
{
	int speed = CELL;
#define HOLD_TIME 30	//���������Ă��甽������܂ł̎���



	//���E
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > 0)
	{
		//������
		if (HoldKey_X == false) {
			CursorPos.x += -speed;
			GridPos.x += -1;
			HoldKey_X = true;
		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > HOLD_TIME)
			{
				HoldKey_X = false;
			}
		}
	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
	{
		//������
		if (HoldKey_X == false) {
			CursorPos.x += speed;
			GridPos.x += 1;

			HoldKey_X = true;
		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > HOLD_TIME)
			{
				HoldKey_X = false;
			}
		}
	}
	else {
		HoldKey_X = false;
	}


	//�㉺
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > 0)
	{
		//������
		if (HoldKey_Y == false) {
			CursorPos.y += -speed;
			GridPos.y += -1;

			HoldKey_Y = true;
		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP) > HOLD_TIME)
			{
				HoldKey_Y = false;
			}
		}
	}
	else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
	{
		//������
		if (HoldKey_Y == false) {
			CursorPos.y += speed;
			GridPos.y += 1;

			HoldKey_Y = true;
		}
		else {
			if (Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > HOLD_TIME)
			{
				HoldKey_Y = false;
			}
		}
	}
	else {
		HoldKey_Y = false;

	}

	// ���[�h�؂�ւ�
	if (Owner->InputKey->getKeyDown(KEY_INPUT_P) == true)
	{
		printf("�ۑ�\n");

		isWrite_File = true;	//�t�@�C����ۑ�
	}
	else
	{
		isWrite_File = false;
	}


	//�t�@���N�V�����L�[�Ő؂�ւ�
	if (Owner->InputKey->getKeyDown(KEY_INPUT_F1) == true)
	{
		chip.setBinary(0x01);				//�o�C�i��
		chip.setSprite(SpriteList.at(0));	//�X�v���C�g
		chip.setPosition(GridPos);			//�O���b�h���W
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_F2) == true)
	{
		chip.setBinary(0x02);				//�o�C�i��
		chip.setSprite(SpriteList.at(1));	//�X�v���C�g
		chip.setPosition(GridPos);			//�O���b�h���W
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_F3) == true)
	{
		chip.setBinary(0x03);				//�o�C�i��
		chip.setSprite(SpriteList.at(2));	//�X�v���C�g
		chip.setPosition(GridPos);			//�O���b�h���W
	}


	if (Owner->InputKey->getKeyDown(KEY_INPUT_F1) == true)
	{
		chip.setBinary(0x01);				//�o�C�i��
		chip.setSprite(SpriteList.at(0));	//�X�v���C�g
		chip.setPosition(GridPos);			//�O���b�h���W
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

//�}�b�v���X�N���[���������
glm::ivec2 Control::getMove()
{
	return ScrollMove;
}


MapChip Control::getChip()
{
	return chip;
}


//�`��
void Control::Draw()
{
	//��`�`��
	int c = anim->getClip_loop(5);
	if (c == 1) {
		DrawBox(CursorPos.x + 1, CursorPos.y + 1, CursorPos.x + CELL, CursorPos.y + CELL, GetColor(0, 255, 0), true);
	
	}
}

//�f�X�g���N�^
Control::~Control()
{

}

