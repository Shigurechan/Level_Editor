#include "Scene_Base.hpp"


//�R���X�g���N�^
Scene_base::Scene_base(Scene_Type t, Entry* e)
{
	Type = t;	//�V�[���Ƀ^�C�v��ݒ�
	Owner = e;	//Entry �N���X
}

//�V�[���^�C�v���擾
Scene_Type Scene_base::getSceneType()
{
	return Type;
}

//�f�X�g���N�^
Scene_base::~Scene_base()
{
	
}