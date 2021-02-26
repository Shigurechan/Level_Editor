#ifndef ___MAPCHIP_HPP_
#define ___MAPCHIP_HPP_

#include "Actor.hpp"
#include "glm/glm.hpp"
class MapChip;
/*####################################################
* �}�b�v�`�b�v
*
* ����
* 
* �o�C�i��
* �X�v���C�g
* ���W
* ���i�[
######################################################*/

class MapChip : public Actor
{
public:
	MapChip();	//�R���X�g���N�^
	~MapChip();	//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��


	// �ݒ�@�֌W
	void setBinary(byte b);	//�o�C�i��
	void setSprite(int sp);	//�X�v���C�g


	//�擾�@�֌W
	byte getBinary();	//�o�C�i��
	int getSprite();	//�X�v���C�g



private:

	byte binary;	//�o�C�i��
	int sprite;		//�X�v���C�g



};




#endif