#ifndef ___ENTRY_HPP_
#define ___ENTRY_HPP_

#include "Input.hpp"
#include "glm/glm.hpp"

#include <iostream>

class Game_Scene;
class StartMenu;

#define CELL ((int)48)	//�Z��

typedef unsigned char byte;	//�o�C�g


#define INPUT_KEY_NUMBER_MAX 100	//���͉\�ő啶����



#define SCROLL_OFFSET_RIGHT 18
#define SCROLL_OFFSET_LEFT 6


#define SCROLL_OFFSET_UP 4
#define SCROLL_OFFSET_DOWN 15


//��ʃT�C�Y
#define SCREEN_WIDTH ((int)(16 + 10) * CELL)
#define SCREEN_HEIGHT ((int)(9 + 10)  * CELL)

//�X�e�[�W
#define STAGE_WIDTH ((int)100 * CELL)
#define STAGE_HEIGHT ((int)100 * CELL)

//�X�e�[�W�̃Z����
#define STAGE_GRID_X ((int)(STAGE_WIDTH / CELL))
#define STAGE_GRID_Y ((int)(STAGE_HEIGHT / CELL))

//����
#define VECTOR_UP glm::ivec2(0,-1)
#define VECTOR_DOWN glm::ivec2(0,1)
#define VECTOR_LEFT glm::ivec2(-1,0)
#define VECTOR_RIGHT glm::ivec2(1,0)
#define VECTOR_None glm::ivec2(0,0)

#define PI ((float)3.14159265359)	//PI

//�t�@�C�����[�h
#define WRITE_OVERRITE 0	//�㏑��
#define WRITE_NEW 1			//�V�K�쐬
#define WRITE_EDIT 2		//�ҏW

//�X�v���C�g���
typedef struct SpriteData
{
	int sprite;			//�X�v���C�g
	byte bin;			//�o�C�i��
	std::string name;	//�X�v���C�g��
}SpriteData;


//�G�f�B�b�g���
typedef struct EditData
{
	byte EditMode;			//�G�f�B�b�g���[�h
	char FileName[INPUT_KEY_NUMBER_MAX];		//�������ރt�@�C����
	glm::ivec2 StageSize;	//�X�e�[�W�̃T�C�Y


}EditData;


// �V�[���̎��
enum class Scene_Type
{
	Title,		//�^�C�g��
	Game,		//���C���Q�[��
	GameOver,	//�Q�[���I�[�o�[


	Menu,		//���j���[
	Pause,		//�ꎞ��~
};



/*####################################################
* �V�[������
* 
* ����
* �V�[���̐��ڂ��s��
######################################################*/
class Entry
{
public:

	Entry();	//�R���X�g���N�^
	~Entry();	//�f�X�g���N�^

	void Update();	//�v�Z
	void Draw();	//�`��
	int GetRand(int start, int end);	//�������擾
	
	int LoadSprite(const char* FileName);				//�X�v���C�g�����[�h


	std::shared_ptr<Input> InputKey;	//�L�[����

private:

	std::shared_ptr<Game_Scene> game;	//�G�f�B�b�g���

	std::shared_ptr<StartMenu> start;	//�t�@�C���I�����

	Scene_Type Scene;		//���݂̃V�[��
	Scene_Type Prev_Scene;	//�O�̃V�[��

	bool changeScene = false; //�V�[���؂�ւ�
	EditData mData;
};


#endif

