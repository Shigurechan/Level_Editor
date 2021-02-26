#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include "MapChip.hpp"
#include <Dxlib.h>
#include <array>

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
	Stage();	//�R���X�g���N�^
	~Stage();	//�f�X�g���N�^

	void Update();		//�v�Z
	void Draw();		//�`��

	void setGrid(MapChip chip);	//�O���b�h�ɏ�������
	//void setObject();	//
private:


	std::shared_ptr<std::array<std::array<MapChip, STAGE_GRID_X>,STAGE_GRID_Y>> mStage;	//�X�e�[�W
	
};


#endif
