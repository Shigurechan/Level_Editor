#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include <Dxlib.h>

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

	void Update();	//�v�Z
	void Draw();	//�`��

private:


	byte mGame_Stage[ STAGE_GRID_Y ][ STAGE_GRID_X ];	//�X�e�[�W
};


#endif
