#include "Game_Scene.hpp"
#include "Stage.hpp"
#include "Control.hpp"

#include <filesystem>
#include <map>

namespace fs = std::filesystem;

//�R���X�g���N�^
Game_Scene::Game_Scene(Scene_Type t, Entry* e) : Scene_base(t, e)
{
	Owner = e;	//Entry �N���X


	// #####�@�X�v���C�g�����[�h #####
	std::vector<SpriteData> SpriteList;	//�X�v���C�g���X�g
	
	//�ǂݍ��݃t�@�C���p�X��ݒ�
	std::string filename = "/Sprite_Data/";
	std::string path = fs::current_path().string();
	//path = filename;
	path = path + filename;
	
	//�X�v���C�g�ǂݍ���
	
	for (fs::directory_iterator itr = fs::directory_iterator(path); itr != fs::directory_iterator(); itr++)
	{
		printf("%s\n",itr->path().string().c_str());

		SpriteData data;	//�X�v���C�g�f�[�^

		data.sprite = Owner->LoadSprite(itr->path().string().c_str());	//�X�v���C�g��ݒ�

		std::string name = itr->path().filename().string();	//�t�@�C�������擾
		data.name = name;	//�t�@�C������ݒ�

		if (data.name == "Block.png")
		{
			data.bin = 0x01;
		}
		else if (data.name == "Brick.png")
		{
			data.bin = 0x02;
		}
		else if (data.name == "Shop.png")
		{
			data.bin = 0x03;
		}
		else {
			printf("�o�C�i����񖢐ݒ�: %s\n",data.name.c_str());
		}

		SpriteList.push_back(data);	//�X�v���C�g		
	}
	
	









	// #####�@�R���|�[�l���g #####
	stage = std::make_shared<Stage>(Owner,SpriteList);				//�}�b�v�`��
	control = std::make_shared<Control>(Owner,SpriteList);	//����
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
	stage->Draw();
	control->Draw();


}

//�f�X�g���N�^
Game_Scene::~Game_Scene()
{

}
