#include "Game_Scene.hpp"
#include "Stage.hpp"
#include "Control.hpp"

#include <filesystem>

namespace fs = std::filesystem;

//�R���X�g���N�^
Game_Scene::Game_Scene(Scene_Type t,Entry *e) : Scene_base(t,e)
{
	Owner = e;	//Entry �N���X


	// #####�@�X�v���C�g�����[�h #####

	std::vector<int> SpriteList;	//�X�v���C�g���X�g

	//�X�v���C�g�ǂݍ���
	SpriteList.push_back(Owner->LoadSprite("Sprite_Data/Block.png"));
	SpriteList.push_back(Owner->LoadSprite("Sprite_Data/Brick.png"));
	SpriteList.push_back(Owner->LoadSprite("Sprite_Data/Shop.png"));

	// #####�@�R���|�[�l���g #####
	stage = std::make_shared<Stage>(Owner,SpriteList);				//�}�b�v�`��
	control = std::make_shared<Control>(Owner,SpriteList);			//����



}

//������
void Game_Scene::SetUp()
{
	//�V�K�쐬
	if (Data.EditMode == (byte)WRITE_NEW)
	{
		//printf("�V�K�t�@�C�����쐬\n");	
		stage->NewFile(Data);	//�t�@�C����V�K�쐬
		control->setPos(Data.StageSize);	//�����J�[�\�����W
	}
	else if (Data.EditMode == (byte)WRITE_EDIT)
	{
		//printf("�t�@�C���ҏW\n");
		stage->ReadFile(Data);	//�t�@�C����ǂݍ���
		control->setPos(Data.StageSize);	//�����J�[�\�����W

	}
	else if (Data.EditMode == (byte)WRITE_OVERRITE)
	{
		//printf("�㏑���쐬\n");
		stage->ReadFile(Data);	//�t�@�C����ǂݍ���
		control->setPos(Data.StageSize);	//�����J�[�\�����W

	}
	else 
	{
		//printf("Error ���ݒ� Data.EditMode : %d\n",Data.EditMode);
	}
}


//�X�V
void Game_Scene::Update()
{


	stage->Update();
	control->Update();

	//�O���b�h�̏�������
	if ( control->isWrite_cell == true )
	{
		stage->setGrid(control->getChip(),control->getScreenGridPos());
	}

	//�o�C�i���t�@�C���ɃX�e�[�W�����������ނ��ǂ����H
	if (control->isWrite_File == true)
	{
		stage->WriteFile(Data);
		control->isWrite_File = false;
	}

	
	stage->Scroll(control);	//��ʃX�N���[��
	





}


//�G�f�B�b�g�f�[�^���擾
void Game_Scene::setEditData(EditData data)
{
	if (isEditScene == false) 
	{
		Data = data;
		SetUp();

		isEditScene = true;
	}

}


//�`��
void Game_Scene::Draw()
{
	control->Draw();
	stage->Draw();


}

//�f�X�g���N�^
Game_Scene::~Game_Scene()
{

}
