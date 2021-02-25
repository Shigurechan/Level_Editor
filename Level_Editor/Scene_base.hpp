#ifndef ___SCENE_BASE_HPP_
#define ___SCENE_BASE_HPP_

#include <iostream>
#include <vector>

class Entry;
enum class Scene_Type;

/*####################################################
* �V�[���̊��N���X
* 
* ����
* �S�ẴV�[���N���X�͂��̃N���X���p������B
######################################################*/
class Scene_base
{
public:
	Scene_base(Scene_Type t,Entry* e);	//�R���X�g���N�^
	~Scene_base();						//�f�X�g���N�^

	virtual void Update() = 0;	//�X�V
	virtual void Draw() = 0;	//�`��

	Scene_Type getSceneType();	//�V�[���^�C�v���擾
protected:

	Scene_Type Type;	//�V�[���^�C�v
	Entry* Owner;		//Entry �N���X

};


#endif
