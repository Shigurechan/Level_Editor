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
	ConfigData getConfig();			//�R���t�B�O�f�[�^���擾
	std::vector<SpriteData> getMapChip();	//�}�b�v�`�b�v���擾
	WriteData getWriteData();	//�������݃f�[�^���擾





	
	bool isWrite_cell;	//�X�e�[�W�����o�C�i���t�@�C���ɏ������ނ��ǂ����H
	bool isSave;		//�Z�[�u����

private:

	void MenuUpdate();	//�X�V
	void MenuDraw();	//�`��

	glm::ivec2 Screen_GridPos;	//��ʏ�̃O���b�h���W
	glm::ivec2 GridPos;			//�X�e�[�W�̃O���b�h���W

	glm::ivec2 ScrollMove;		//�X�N���[���������
	glm::ivec2 mVector;			//����



	//���M�f�[�^
	WriteData ChipData;	//�������ރf�[�^
	ConfigData Config;	//�R���t�B�O





	std::shared_ptr<Animation> anim;	//�J�[�\���A�j���[�V����

	std::vector<SpriteData> SpriteList;		//�X�v���C�g���X�g
	std::vector<std::string> FileNameList;	//�t�@�C�������X�g
	std::vector<std::string> StageFileNameList;

	std::string FileName;


	//�@���j���[�֌W

	bool isChipSelect;	//�}�b�v�`�b�v��I��	
	bool isStageSelect;	//�X�e�[�W��I��
	bool isChangeSize;	//�X�e�[�W�̑傫����ύX
	



	std::shared_ptr<Window> Chip_Menu;	//�`�b�v�I�����
	std::shared_ptr<Window> Stage_Menu;	//�X�e�[�W�I�����








	//������
	bool HoldKey_Y;
	bool HoldKey_X;
	
	Entry* Owner;	//Entry�N���X
};


#endif