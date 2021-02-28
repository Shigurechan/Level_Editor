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

	type = Window_Scene::Main;	//�ŏ��̃V�[��
	changeScene = false;	//�V�[����؂�ւ���
	KeyHandle = MakeKeyInput(100, false, true, false);	//�L�[���̓n���h�����쐬
	if (KeyHandle == -1) { printf("Error MakeKeyInput()\n"); }


	//���C�����j���[
	menu = std::make_shared<Window>(e,Window_Scene::Main,glm::ivec2(100,100),glm::ivec2(200,200));
	menu->setTitle("�t�@�C�����j���[",GetColor(0,0,0));
	menu->AddList_Down(Window_Scene::New_File, "�V�K", 0, GetColor(0, 0, 0));
	menu->AddList_Down(Window_Scene::Edit_File, "�ҏW", 1, GetColor(0, 0, 0));

	//�V�K�쐬
	NewFile_menu = std::make_shared<Window>(e, Window_Scene::New_File, glm::ivec2(100, 100), glm::ivec2(300, 200));
	NewFile_menu->setTitle("  �t�@�C�������͂��Ă�������", GetColor(0,0,0));

	//�ҏW���鎞�̃t�@�C��������
	EditFile_menu = std::make_shared<Window>(e, Window_Scene::Edit_File, glm::ivec2(100, 100), glm::ivec2(300, 200));
	EditFile_menu->setTitle("  �t�@�C�������͂��Ă�������", GetColor(0, 0, 0));


	//�t�@�C�������݂��邩�ǂ����H�@���݂��鎞�̏㏑���m�F
	CheckFile_menu = std::make_shared<Window>(e, Window_Scene::OverWrite_Check, glm::ivec2(200, 200), glm::ivec2(300, 300));
	CheckFile_menu->setTitle("�t�@�C�������݂��܂��㏑�����܂����H", GetColor(0, 0, 0));
	CheckFile_menu->AddList_Down(Window_Scene::WriteFile_OverWrite, "YES", 1, GetColor(0, 0, 0));
	CheckFile_menu->AddList_Down(Window_Scene::New_File, "NO", 0, GetColor(0, 0, 0));

}

//�X�V
void StartMenu::Update()
{

	

	switch (type)
	{
		//���C�����j���[
	case Window_Scene::Main:
	{
//		printf("Main\n");

		menu->Update();	//�X�V
		if (menu->getChangeScene() != Window_Scene::Invalid)
		{
			//�L�[���͂��A�N�e�B�u�ɂ���B		
			SetActiveKeyInput(KeyHandle);//��������͂�L����
			
			type = menu->getChangeScene();//�V�[���؂�ւ�
			menu->Reset();//�E�C���h���ď�����
		}
	}break;


		//�V�K�쐬
	case Window_Scene::New_File:
	{
		//printf("New File\n");
		GetKeyInputString(FileName, KeyHandle);	//���͕�������擾
				
		//�G���^�[�L�[�Ō���
		if (Owner->InputKey->getKeyDown(KEY_INPUT_RETURN) == true)
		{

			//�t�@�C�������邩�ǂ����H
			if (CheckFile(FileName) == true) {
				//���݂���ꍇ
				type = Window_Scene::OverWrite_Check;	//�㏑���m�F�V�[���Ɉړ�
			}
			else {
				//�Ȃ��ꍇ(�V�K�쐬)
				type = Window_Scene::Write_NewFile;	//�V�K�쐬
				Mode = (byte)WRITE_NEW;	//�G�f�B�b�g���[�h�@�V�K�쐬

			}
		}
		else if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
		{
			// �߂�ꍇ
			type = Window_Scene::Main;	//���C�����j���[�ɖ߂�

			memset(FileName, '\0', sizeof(FileName));			//���O�̕�������ď�����
			InitKeyInput();										//���̓f�[�^���폜
			KeyHandle = MakeKeyInput(100, false, true, false);	//�L�[���̓n���h�����쐬
			SetActiveKeyInput(KeyHandle);						//���͂��A�N�e�B�u
		}
	}break;


	//�t�@�C����ҏW
	case Window_Scene::Edit_File:
	{
		//printf("New File\n");
		GetKeyInputString(FileName, KeyHandle);	//���͕�������擾

		//�G���^�[�L�[�Ō���
		if (Owner->InputKey->getKeyDown(KEY_INPUT_RETURN) == true)
		{
			type = Window_Scene::Write_EditFile;
			Mode = WRITE_Edit;	//�G�f�B�b�g���[�h�㏑��

		}
		else if (Owner->InputKey->getKeyDown(KEY_INPUT_SPACE) == true)
		{
			// �߂�ꍇ
			type = Window_Scene::Main;	//���C�����j���[�ɖ߂�

			memset(FileName, '\0', sizeof(FileName));			//���O�̕�������ď�����
			InitKeyInput();										//���̓f�[�^���폜
			KeyHandle = MakeKeyInput(100, false, true, false);	//�L�[���̓n���h�����쐬
			SetActiveKeyInput(KeyHandle);						//���͂��A�N�e�B�u
		}
	}break;


		//�㏑���m�F
	case Window_Scene::OverWrite_Check:
	{
		//		printf("Main\n");

		CheckFile_menu->Update();
		if (CheckFile_menu->getChangeScene() != Window_Scene::Invalid)
		{
			type = CheckFile_menu->getChangeScene();	//�V�[���؂�ւ�

			//�t�@�C�������͉�ʂɖ߂鎞
			if (type == Window_Scene::New_File)
			{
				memset(FileName, '\0', sizeof(FileName));			//���O�̕�������ď�����
				InitKeyInput();										//���̓f�[�^���폜
				KeyHandle = MakeKeyInput(100, false, true, false);	//�L�[���̓n���h�����쐬
				SetActiveKeyInput(KeyHandle);						//���͂��A�N�e�B�u


			}

			Mode = WRITE_OVERRITE;	//�G�f�B�b�g���[�h�㏑��

			CheckFile_menu->Reset();	//�E�C���h�E���ŏ�����
		}
	}break;


	//�@*** �t�@�C�����㏑�����ăG�f�B�b�g��ʂɈڍs *** 
	case Window_Scene::WriteFile_OverWrite:
	{
		printf("�㏑��\n");	
		memcpy(data.FileName, FileName, sizeof(data.FileName));
		data.EditMode = Mode;
		changeScene = true;

		Type = Scene_Type::Game;
	}break;


	//�@*** �V�K�t�@�C���쐬���ăG�f�B�b�g��ʂɈڍs *** 
	case Window_Scene::Write_NewFile:
	{
		//printf("�V�K�t�@�C�����쐬\n");
		memcpy(data.FileName, FileName, sizeof(data.FileName));
		data.EditMode = Mode;
		changeScene = true;
		Type = Scene_Type::Game;

	}break;

	
	//�@*** �t�@�C����ҏW���ăG�f�B�b�g��ʂɈڍs *** 
	case Window_Scene::Write_EditFile:
	{
		//printf("�t�@�C����ҏW\n");
		memcpy(data.FileName, FileName, sizeof(data.FileName));	//
		data.EditMode = Mode;									//
		changeScene = true;										//
		Type = Scene_Type::Game;								//

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
		menu->Draw();
	}break;

		//�V�K�쐬
	case Window_Scene::New_File:
	{
		NewFile_menu->Draw();
		DrawFormatString(NewFile_menu->getPosition().x + 20, NewFile_menu->getPosition().y + 50, GetColor(0, 100, 0), "FileName: %s", FileName);
	}break;

		//�㏑���m�F
	case Window_Scene::OverWrite_Check:
	{
		CheckFile_menu->Draw();	
	}break;

	//�㏑���m�F
	case Window_Scene::Edit_File:
	{
		EditFile_menu->Draw();
		DrawFormatString(EditFile_menu->getPosition().x + 20, EditFile_menu->getPosition().y + 50, GetColor(0, 100, 0), "FileName: %s", FileName);

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

