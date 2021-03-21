#include "Edit_Scene.hpp"
#include "Stage.hpp"
#include "Control.hpp"

#include <filesystem>
#include <map>

namespace fs = std::filesystem;

//�R���X�g���N�^
Edit_Scene::Edit_Scene(Scene_Type t, Entry* e) : Scene_base(t, e)
{
	Owner = e;	//Entry �N���X




	// #####�@�R���|�[�l���g #####
	stage = std::make_shared<Stage>(Owner);				//�}�b�v�`��
	control = std::make_shared<Control>(Owner);	//����
}

//������
void Edit_Scene::SetUp()
{
	stage->SetUp();
	stage->setMapChip(control->getSpriteData());	//�X�v���C�g�f�[�^��ǂݍ���
	//printf("������\n");

	Type = Scene_Type::Edit;
}


//�X�V
void Edit_Scene::Update()
{



	stage->setControl(control);
	

	control->Update();	//�X�V
	stage->Update();	//�X�V

	stage->Scroll(control);												//��ʃX�N���[��

}




//�`��
void Edit_Scene::Draw()
{
	stage->Draw();
	control->Draw();


}

//�f�X�g���N�^
Edit_Scene::~Edit_Scene()
{

}
