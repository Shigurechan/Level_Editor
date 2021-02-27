#include "Control.hpp"
#include "Entry.hpp"
#include "MapChip.hpp"

//�R���X�g���N�^
Control::Control(Entry* e)
{
	Owner = e; //Entry �N���X
	CursorPos = glm::ivec2(0, 0);	//�J�[�\�����W
	GridPos = CursorPos;			//�O���b�h�̍��W

	//������
	HoldKey_X = false;
	HoldKey_Y = false;

	isWrite_cell = false;	//�������ނ��ǂ����H
	isWrite_File = false;	//�o�C�i���t�@�C���ɃX�e�[�W�����������ނ��ǂ����H



	Block_Handle = Owner->LoadSprite("Assets/Block.png");	//�u���b�N	
}

//�X�V
void Control::Update()
{
	int speed = CELL;	
#define HOLD_TIME 30	//���������Ă��甽������܂ł̎���



	//���E
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_LEFT) > 0)
	{
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
	}else if (Owner->InputKey->getKeyDownHold(KEY_INPUT_RIGHT) > 0)
	{
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
	if (Owner->InputKey->getKeyDownHold(KEY_INPUT_UP)  > 0)
	{
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
	else if(Owner->InputKey->getKeyDownHold(KEY_INPUT_DOWN) > 0)
	{
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





	//�X�y�[�X�ŏ�������
	if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
	{
		chip.setBinary(0x01);			//�o�C�i��
		chip.setSprite(Block_Handle);	//�X�v���C�g
		chip.setPosition(GridPos);		//�O���b�h���W

		isWrite_cell = true;	//�O���b�h�ɏ�������
	}
	else {
		isWrite_cell = false;
	}






}


MapChip Control::getChip()
{
	return chip;
}


//�`��
void Control::Draw()
{
	//��`�`��
	DrawBox(CursorPos.x + 1, CursorPos.y + 1, CursorPos.x + CELL, CursorPos.y + CELL, GetColor(0,0,120),true);
}

//�f�X�g���N�^
Control::~Control()
{

}

