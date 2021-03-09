#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include "MapChip.hpp"
#include <Dxlib.h>
#include <array>
#include <vector>
#include <map>
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
	Stage(Entry *e);	//�R���X�g���N�^
	~Stage();	//�f�X�g���N�^

	void Update();		//�v�Z
	void Draw();		//�`��

	void setGrid(MapChip chip, glm::ivec2 screen_grid);	//�O���b�h�ɏ�������
	void setMapChip(std::vector<SpriteData> data);		//�}�b�v�`�b�v�f�[�^���擾
	void WriteFile(std::string file);					//�o�C�i���t�@�C���ɃX�e�[�W����������
	void ReadFile(std::string file);					//�o�C�i���t�@�C����ǂݍ���
	void setSaveFile(bool isSave);
	void Scroll(std::shared_ptr<Control> control);		//�X�N���[���������
	void setStage(ConfigData config);					//�R���t�B�O�f�[�^���擾
	void SetUp();										//�t�H���_����X�e�[�W��ǂݍ���
	void WriteGrid(WriteData data,bool flag);			//�X�e�[�W�ɏ������ނ��ǂ����H



private:

	glm::ivec2 mSize;	//�T�C�Y
	std::shared_ptr<std::vector<std::vector<MapChip>>> mStage;	//�X�e�[�W
	std::vector<SpriteData> SpriteList;	//�X�v���C�g���X�g
	Entry* Owner;
	
	std::vector<std::string> FileNameList;	//�t�@�C�����X�g
	ConfigData Config;	//�R���t�B�O




};


#endif
