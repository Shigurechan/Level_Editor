#ifndef ___CONTROL_HPP_
#define ___CONTROL_HPP_


#include <Dxlib.h>
#include "MapChip.hpp"
#include "glm/glm.hpp"

class Entry;

/*####################################################
* �R���g���[��
*
* ����
* �}�E�X�ƃL�[�{�[�h�ɂ�鑀��@�֌W�̃N���X
######################################################*/

class Control
{
public:
	Control(Entry* e);	//�R���X�g���N�^
	~Control();			//�f�X�g���N�^



	void Update();	//�X�V

	void Draw();	//�`��


	MapChip getChip();	//�}�b�v�`�b�v

	bool isWrite_cell;	//�������ނ��ǂ����H
	bool isWrite_File;	//�X�e�[�W�����o�C�i���t�@�C���ɏ������ނ��ǂ����H

private:
	Entry* Owner;	//Entry �N���X
	glm::ivec2 CursorPos;	//�J�[�\���̏ꏊ
	glm::ivec2 GridPos;	//�O���b�h�̏ꏊ

	MapChip chip;


	//������
	bool HoldKey_X;
	bool HoldKey_Y;



	//�e�X�g
	int Block_Handle;






};


#endif