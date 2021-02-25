#ifndef ___UI_HPP_
#define ___UI_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"




//�E�C���h�E�̏��
typedef struct RectangleData
{
	glm::ivec2 pos;		//���W
	glm::ivec2 size;	//�T�C�Y
}RectangleData;

void GetRectangleData(RectangleData& data, glm::ivec2 pos, glm::ivec2 size);	//��`�T�C�Y��ݒ�


/*####################################################
* ���[�U�[�C���^�[�t�F�C�X
*
* ����
* �v���C��ʂ�UI�@������
######################################################*/

class UI
{
public:
	UI(glm::ivec2 pos = glm::ivec2(0, 0), glm::ivec2 vec = glm::ivec2(0, 0));	//�R���X�g���N�^
	~UI();	//�f�X�g���N�^

	void virtual Update() = 0;	//�v�Z
	void virtual Draw() = 0;	//�`��

	//�擾�֌W
	glm::ivec2 getVector();		//����
	glm::ivec2 getPosition();	//���W
protected:

	glm::ivec2 mPosition;	//���W
	glm::ivec2 mVector;		//����
	glm::ivec2 mSize;		//�X�v���C�g�̃T�C�Y


};


#endif
