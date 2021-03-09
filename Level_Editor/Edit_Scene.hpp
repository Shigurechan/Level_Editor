#ifndef ___GAME_SCENE_HPP_
#define ___GAME_SCENE_HPP_

#include "Scene_base.hpp"
#include "Entry.hpp"

class Stage;
class Entry;
class Control;
enum class Scene_Type;
/*####################################################
* ���C���Q�[���@�V�[��
*
* ����
* ���C���̃Q�[�����
######################################################*/
class Edit_Scene : public Scene_base
{
public:
	Edit_Scene(Scene_Type t,Entry* e);	//�R���X�g���N�^
	~Edit_Scene();						//�f�X�g���N�^
	void SetUp();	//�Z�b�g�A�b�v�����ݒ�


	void Update();	//�X�V
	void Draw();	//�`��

	
	
private:



	std::shared_ptr<Stage> stage;		//�}�b�v�`��N���X
	std::shared_ptr<Control> control;	//����N���X

	
	Entry* Owner;	//Entry �N���X

	WriteData Data;
	std::string DDPath;	//D&D�p�X
	bool isEditScene = false;//�G�f�B�b�g�V�[���ɐ���
};

#endif
