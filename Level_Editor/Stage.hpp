#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include "MapChip.hpp"
#include <Dxlib.h>
#include <array>
#include <vector>

/*####################################################
* �G�f�B�b�g����X�e�[�W��`��
*
* ����
* 
* 
######################################################*/

class Stage
{
public:
	Stage(Entry *e,std::vector<int> spriteList);	//�R���X�g���N�^
	~Stage();	//�f�X�g���N�^

	void Update();		//�v�Z
	void Draw();		//�`��

	void setGrid(MapChip chip);		//�O���b�h�ɏ�������
	void WriteFile(EditData data);	//�o�C�i���t�@�C���ɃX�e�[�W����������
	void ReadFile(EditData data);	//�o�C�i���t�@�C����ǂݍ���

	void Scroll(glm::ivec2 m);	//�X�N���[���������
private:


	std::shared_ptr<std::array<std::array<MapChip, STAGE_GRID_X>,STAGE_GRID_Y>> mStage;	//�X�e�[�W
	std::vector<int> SpriteList;	//�X�v���C�g���X�g
	Entry* Owner;
	
};


#endif
