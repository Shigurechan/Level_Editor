#ifndef ___ACTOR_HPP_
#define ___ACTOR_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"

class Entry;

/*####################################################
* �A�N�^�[
* 
* ����
* �S�ẴQ�[���I�u�W�F�N�g�͂�����p������B
######################################################*/

class Actor
{
public:
	Actor(Entry* e,glm::ivec2 pos = glm::ivec2(0, 0), glm::ivec2 vec = glm::ivec2(0, 0));	//�R���X�g���N�^
	~Actor();	//�f�X�g���N�^

	void virtual Update() = 0;	//�v�Z
	void virtual Draw() = 0;	//�`��

	//�擾�@�֌W
	glm::ivec2 getVector();		//����
	glm::ivec2 getPosition();	//���W

	//�ݒ�@�֌W
	void setPosition(glm::ivec2 pos);

protected:

	glm::ivec2 mPosition;	//���W
	glm::ivec2 mVector;		//����
	glm::ivec2 mSize;		//�X�v���C�g�̃T�C�Y

	Entry* Owner;			//Entry �N���X

};


#endif
