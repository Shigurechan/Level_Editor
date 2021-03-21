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
	Control(Entry* e);	//�R���X�g���N�^
	~Control();									//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��


	// ##### �ݒ�
	void setPos(glm::ivec2 size);	//�J�[�\�����W
	void setGridPos(glm::ivec2 g);	//�O���b�h���W��ݒ�
	void setScreenGridPos(glm::ivec2 p);	//�X�N���[���̃O���b�h���W���擾
	void SetUp();	//������

	// ##### �擾�@
	
	glm::ivec2 getGridPos();		//�O���b�h���W���擾
	glm::ivec2 getVector();			//����
	glm::ivec2 getScreenGridPos();	//�X�N���[���̃O���b�h���W���擾
	std::vector<SpriteData> getSpriteData();	//�X�v���C�g�f�[�^




	EditData sendData;	//���M�f�[�^

private:

	void MenuUpdate();	//�X�V
	void MenuDraw();	//�`��

	glm::ivec2 Screen_GridPos;	//��ʏ�̃O���b�h���W
	glm::ivec2 GridPos;			//�X�e�[�W�̃O���b�h���W

	glm::ivec2 ScrollMove;		//�X�N���[���������
	glm::ivec2 mVector;			//����

	int writeSprite;	//�I�𒆂̃X�v���C�g

	




	std::shared_ptr<Animation> anim;	//�J�[�\���A�j���[�V����

	std::vector<SpriteData> SpriteList;		//�X�v���C�g���X�g
	std::vector<std::string> FileNameList;	//�t�@�C�������X�g
	std::vector<std::string> StageFileNameList;

	std::string FileName;


	//�@���j���[�֌W

	


	std::shared_ptr<Window> chipMenu;	//�`�b�v�I�����
	std::shared_ptr<Window> stageMenu;	//�X�e�[�W�I�����



	//����
	bool isWriteCell;		//��������
	bool isSave;			//�ۑ�
	bool isDelete;			//�폜



	//���j���[���

	bool isMenu;	//���j���[

	bool isFileSelect;		//�t�@�C���؂�ւ�
	bool isStageResize;		//�X�e�[�W�T�C�Y�����T�C�Y
	bool isMapChipSelect;	//�}�b�v�`�b�v��؂�ւ�
	bool isNewFile;			//�V�����t�@�C�����쐬
	bool isStart;			//�X�^�[�g���


	//������
	bool HoldKey_Y;
	bool HoldKey_X;
	
	Entry* Owner;	//Entry�N���X
};


#endif