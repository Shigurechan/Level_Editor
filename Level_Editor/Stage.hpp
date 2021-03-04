#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include "MapChip.hpp"
#include <Dxlib.h>
#include <array>
#include <vector>
#include <iostream>

/*####################################################
* �G�f�B�b�g����X�e�[�W��`��
*
* ����
* 
* 
######################################################*/

class Control;	//����

class Stage
{
public:
	Stage(Entry *e,std::vector<int> spriteList);	//�R���X�g���N�^
	~Stage();	//�f�X�g���N�^

	void Update();		//�v�Z
	void Draw();		//�`��

	void setGrid(MapChip chip, glm::ivec2 screen_grid);		//�O���b�h�ɏ�������
	void WriteFile(EditData data);	//�o�C�i���t�@�C���ɃX�e�[�W����������
	void ReadFile(EditData data);	//�o�C�i���t�@�C����ǂݍ���
	void NewFile(EditData data);	//�V�K�t�@�C�����쐬

	void Scroll(std::shared_ptr<Control> control);	//�X�N���[���������
private:

	glm::ivec2 mSize;	//�T�C�Y
	std::shared_ptr<std::vector<std::vector<MapChip>>> mStage;	//�X�e�[�W
	std::vector<int> SpriteList;	//�X�v���C�g���X�g
	Entry* Owner;
	
};


#endif
