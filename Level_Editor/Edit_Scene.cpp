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
	stage->setMapChip(control->getMapChip());
}


//�X�V
void Edit_Scene::Update()
{



	stage->Update();	//�X�V
	control->Update();	//�X�V

	stage->setStage(control->getConfig());								//�ݒ�t�@�C������������
	stage->WriteGrid(control->getWriteData(),control->isWrite_cell);	//�X�e�[�W�ɏ�������
	stage->setSaveFile(control->isSave);								//�t�@�C�����Z�[�u
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
