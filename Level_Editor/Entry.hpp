#ifndef ___ENTRY_HPP_
#define ___ENTRY_HPP_



#include "Game_Scene.hpp"
#include "Input.hpp"
#include <iostream>
class Game_Scene;
class Stage;


#define CELL ((int)48)	//�Z��

#define byte unsigned char	//�o�C�g

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

#define PI ((float)3.14159265359)	//PI



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


	std::shared_ptr<Input> InputKey;

private:

	std::shared_ptr<Game_Scene> game;

	Scene_Type type;

};


#endif

