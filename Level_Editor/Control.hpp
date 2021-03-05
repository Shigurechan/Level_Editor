#ifndef ___CONTROL_HPP_
#define ___CONTROL_HPP_


#include <Dxlib.h>
#include "MapChip.hpp"
#include "Animation.hpp"
#include "Window.hpp"

#include "glm/glm.hpp"
#include <vector>
#include <map>
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
	Control(Entry* e, std::vector<SpriteData> sprite);	//�R���X�g���N�^
	~Control();									//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��


	// ##### �ݒ�
	void setPos(glm::ivec2 size);	//�J�[�\�����W
	void setGridPos(glm::ivec2 g);	//�O���b�h���W��ݒ�
	void setScreenGridPos(glm::ivec2 p);	//�X�N���[���̃O���b�h���W���擾


	// ##### �擾�@
	MapChip getChip();				//�}�b�v�`�b�v
	glm::ivec2 getGridPos();		//�O���b�h���W���擾
	glm::ivec2 getVector();			//����
	glm::ivec2 getScreenGridPos();	//�X�N���[���̃O���b�h���W���擾



	bool isWrite_cell;	//�������ނ��ǂ����H
	bool isWrite_File;	//�X�e�[�W�����o�C�i���t�@�C���ɏ������ނ��ǂ����H
private:

	void MenuUpdate();	//�X�V
	void MenuDraw();	//�`��

	glm::ivec2 Screen_GridPos;	//��ʏ�̃O���b�h���W
	glm::ivec2 GridPos;			//�X�e�[�W�̃O���b�h���W

	glm::ivec2 ScrollMove;	//�X�N���[���������
	glm::ivec2 mVector;		//����

	MapChip chip;	//�������ޏ��

	std::shared_ptr<Animation> anim;	//�J�[�\���A�j���[�V����

	std::vector<SpriteData> SpriteList;	//�X�v���C�g��񃊃X�g



	//�@���j���[�֌W
	bool isMenu = false;	//���j���[��ʂ��ǂ����H
	std::shared_ptr<Window> menu;	//���j���[�E�C���h�E








	//������
	bool HoldKey_Y;
	bool HoldKey_X;
	
	Entry* Owner;	//Entry�N���X
};


#endif