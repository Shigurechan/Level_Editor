#ifndef ___CONTROL_HPP_
#define ___CONTROL_HPP_


#include <Dxlib.h>
#include "MapChip.hpp"
#include "Animation.hpp"

#include "glm/glm.hpp"
#include <vector>
#include <iostream>

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
	Control(Entry* e,std::vector<int> sprite);	//�R���X�g���N�^
	~Control();			//�f�X�g���N�^



	void Update();	//�X�V

	void Draw();	//�`��

	glm::ivec2 getMove();
	MapChip getChip();	//�}�b�v�`�b�v

	bool isWrite_cell;	//�������ނ��ǂ����H
	bool isWrite_File;	//�X�e�[�W�����o�C�i���t�@�C���ɏ������ނ��ǂ����H

private:
	glm::ivec2 CursorPos;	//�J�[�\���̏ꏊ
	glm::ivec2 GridPos;		//�O���b�h�̏ꏊ
	glm::ivec2 ScrollMove;	//�X�N���[���������


	MapChip chip;	//�������ޏ��
	std::vector<int> SpriteList;	//�X�v���C�g���X�g
	std::shared_ptr<Animation> anim;

	//������
	bool HoldKey_X;
	bool HoldKey_Y;


	Entry* Owner;			//Entry �N���X
};


#endif