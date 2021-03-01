#include "StartMenu.hpp"
#include "Window.hpp"

#include <Dxlib.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>


//�R���X�^���N�^
StartMenu::StartMenu(Scene_Type t, Entry* e) : Scene_base(t,e)
{
#define BACK_COLOR GetColor(255,255,255)

	type = Window_Scene::Main;	//�ŏ��̃V�[��
	changeScene = false;	//�V�[����؂�ւ���
		
	//���C�����j���[
	Main_menu = std::make_shared<Window>(e,Window_Scene::Main,glm::ivec2(100,100),glm::ivec2(200,200));
	Main_menu->setTitle("�t�@�C�����j���[",GetColor(0,0,0));
	Main_menu->AddList_Down(Window_Scene::New_File, "�V�K", 1, GetColor(0, 0, 0), BACK_COLOR);
	Main_menu->AddList_Down(Window_Scene::Edit_File, "�ҏW", 2, GetColor(0, 0, 0), BACK_COLOR);
		
	//�V�K�쐬
	NewFile_menu = std::make_shared<Window>(e, Window_Scene::New_File, glm::ivec2(200, 200), glm::ivec2(300, 200));
	NewFile_menu->setTitle("  �t�@�C�������͂��Ă�������", GetColor(0, 0, 0));
	NewFile_menu->AddList_Down(Window_Scene::None, "FileName: ", 2, GetColor(0, 0, 0), BACK_COLOR,INPUT_CHARACTER);
	
	//�ҏW
	EditFile_menu = std::make_shared<Window>(e, Window_Scene::Edit_File, glm::ivec2(200, 200), glm::ivec2(300, 200));
	EditFile_menu->setTitle("  �t�@�C�������͂��Ă�������", GetColor(0, 0, 0));

	//���݂��鎞�̏㏑���m�F
	CheckFile_menu = std::make_shared<Window>(e, Window_Scene::OverWrite_Check, glm::ivec2(300, 300), glm::ivec2(400, 300));
	CheckFile_menu->setTitle("�t�@�C�������݂��܂��㏑�����܂����H", GetColor(0, 0, 0));
	CheckFile_menu->AddList_Down(Window_Scene::WriteFile_OverWrite, "YES", 3, GetColor(0, 0, 0), BACK_COLOR);
	CheckFile_menu->AddList_Down(Window_Scene::New_File, "NO", 4, GetColor(0, 0, 0), BACK_COLOR);

	//�X�e�[�W�̃T�C�Y���w�肷��
	SizeSet_NewFile_menu = std::make_shared<Window>(e, Window_Scene::SizeSet, glm::ivec2(400, 400), glm::ivec2(500, 400));
	SizeSet_NewFile_menu->setTitle("�X�e�[�W�̃T�C�Y���w��",GetColor(0,0,0));							//�^�C�g��
	SizeSet_NewFile_menu->AddList_Down(Window_Scene::Invalid, "X: ", 5, GetColor(0, 0, 0), BACK_COLOR);	//X���W���w��
	SizeSet_NewFile_menu->AddList_Down(Window_Scene::Invalid, "Y: ", 6, GetColor(0, 0, 0), BACK_COLOR);	//Y���W���w��
	SizeSet_NewFile_menu->AddList_Down(Window_Scene::Write_NewFile, "����: ", 7, GetColor(0, 0, 0), BACK_COLOR);	//����{�^��



}

//�X�V
void StartMenu::Update()
{
	switch (type)
	{
		//���C�����j���[
	case Window_Scene::Main:
	{
		Main_menu->Update();

		if (Main_menu->getChangeScene() != Window_Scene::Invalid)
		{
			type = Main_menu->getChangeScene();
			Main_menu->Reset();
		}
	}break;

	//�V�K�쐬
	case Window_Scene::New_File:
	{
		NewFile_menu->Update();

		if (NewFile_menu->getChangeScene() != Window_Scene::Invalid)
		{
			std::vector<char*> tmp;
			tmp = NewFile_menu->getInputKeyData();

			//�t�@�C�������݂��邩�ǂ����H
			if (CheckFile(tmp.at(0)) == true)
			{
				// �t�@�C�������݂���ꍇ
				type = Window_Scene::OverWrite_Check;
				NewFile_menu->Reset();

			}
			else
			{
				// �t�@�C�����Ȃ��ꍇ
				type = Window_Scene::SizeSet_NewFile;
				NewFile_menu->Reset();
			}
		}
	}break;

	









	}

}

//�`��
void StartMenu::Draw()
{
	switch (type)
	{

		//���C�����j���[
	case Window_Scene::Main:
	{
		Main_menu->Draw();
	}break;

		//�V�K�쐬
	case Window_Scene::New_File:
	{
		NewFile_menu->Draw();
	}break;


	//�V�K�쐬
	case Window_Scene::SizeSet_NewFile:
	{
	
	}break;


	}

}


//�t�@�C�������݂��邩�ǂ����H
bool StartMenu::CheckFile(const char* FileName){
	std::ifstream ifs(FileName);
	if (ifs.is_open() == false)
	{
		//printf("�t�@�C��������܂���B\n");
		return false;
	}
	else {
		//printf("�t�@�C�������݂��܂��B\n");
		return true;
	}
}


EditData StartMenu::getData()
{
	return data;
}

//�f�X�g���N�^
StartMenu::~StartMenu()
{

}

