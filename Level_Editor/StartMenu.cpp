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

	mNowScene = Window_Scene::Main;	//�ŏ��̃V�[��
	changeScene = false;	//�V�[����؂�ւ���
		
	//���C�����j���[
	Main_menu = std::make_shared<Window>(e,Window_Scene::Main,glm::ivec2(100,100),glm::ivec2(200,200));
	Main_menu->setTitle("�t�@�C�����j���[",GetColor(0,0,0));
	Main_menu->AddList_Down(Window_Scene::New_File, "�V�K", 1, GetColor(0, 0, 0), BACK_COLOR);
	Main_menu->AddList_Down(Window_Scene::Edit_File, "�ҏW", 2, GetColor(0, 0, 0), BACK_COLOR);
		
	//�V�K�쐬
	NewFile_menu = std::make_shared<Window>(e, Window_Scene::New_File, glm::ivec2(200, 200), glm::ivec2(300, 200));
	NewFile_menu->setTitle("�t�@�C�������͂��Ă�������", GetColor(0, 0, 0));
	NewFile_menu->AddList_Down(Window_Scene::Yes, "FileName: ", 2, GetColor(0, 0, 0), BACK_COLOR,INPUT_CHARACTER);
	
	//�ҏW
	EditFile_menu = std::make_shared<Window>(e, Window_Scene::Edit_File, glm::ivec2(200, 200), glm::ivec2(300, 200));
	EditFile_menu->setTitle("�t�@�C�������͂��Ă�������", GetColor(0, 0, 0));
	EditFile_menu->AddList_Down(Window_Scene::Yes, "FileName ", 3, GetColor(0, 0, 0), BACK_COLOR,INPUT_CHARACTER);

	//�㏑��
	CheckFile_menu = std::make_shared<Window>(e, Window_Scene::OverWrite_Check, glm::ivec2(300, 300), glm::ivec2(400, 300));
	CheckFile_menu->setTitle("�t�@�C�������݂��܂��㏑�����܂����H", GetColor(0, 0, 0));
	CheckFile_menu->AddList_Down(Window_Scene::Yes, "YES", 3, GetColor(0, 0, 0), BACK_COLOR);
	CheckFile_menu->AddList_Down(Window_Scene::No, "NO", 4, GetColor(0, 0, 0), BACK_COLOR);

	//�X�e�[�W�̃T�C�Y���w�肷��
	SizeSet_menu = std::make_shared<Window>(e, Window_Scene::SizeSet, glm::ivec2(400, 400), glm::ivec2(500, 400));
	SizeSet_menu->setTitle("�X�e�[�W�̃T�C�Y���w��",GetColor(0,0,0));							//�^�C�g��
	SizeSet_menu->AddList_Down(Window_Scene::Invalid, "X: ", 5, GetColor(0, 0, 0), BACK_COLOR,INPUT_NUMBER);	//X���W���w��
	SizeSet_menu->AddList_Down(Window_Scene::Invalid, "Y: ", 6, GetColor(0, 0, 0), BACK_COLOR,INPUT_NUMBER);	//Y���W���w��
	SizeSet_menu->AddList_Down(Window_Scene::Yes, "����: ", 7, GetColor(0, 0, 0), BACK_COLOR);	//����{�^��
	SizeSet_menu->AddList_Down(Window_Scene::No, "�߂�", 7, GetColor(0, 0, 0), BACK_COLOR);	//����{�^��
	
	//�T�C�Y�w��G���[
	SizeSetError_menu = std::make_shared<Window>(e, Window_Scene::SizeSetError, glm::ivec2(500, 500), glm::ivec2(600, 500));
	SizeSetError_menu->setTitle("�T�C�Y�w�肪�s���ł��B", GetColor(0, 0, 0));
	SizeSetError_menu->AddList_Down(Window_Scene::Yes, "�߂�", 7, GetColor(0, 0, 0), BACK_COLOR);

	//�t�@�C�������݂��Ȃ��ꍇ�̃G���[
	CheckFileError_menu = std::make_shared<Window>(e, Window_Scene::CheckFileError, glm::ivec2(500, 500), glm::ivec2(600, 500));
	CheckFileError_menu->setTitle("�t�@�C�������݂��܂���B",GetColor(0, 0, 0));
	CheckFileError_menu->AddList_Down(Window_Scene::Yes, "�߂�", 7, GetColor(0, 0, 0), BACK_COLOR);



}

//�X�V
void StartMenu::Update()
{
	switch (mNowScene)
	{

		//���C�����j���[
	case Window_Scene::Main:
	{
		Main_menu->Update(); //�X�V
	
		if (Main_menu->getChangeScene() != Window_Scene::Invalid) 
		{
			//�V�K�쐬
			if (Main_menu->getChangeScene() == Window_Scene::New_File)
			{
				mNowScene = Window_Scene::New_File; //�V�K�쐬�E�C���h�E�Ɉڍs
			}
			else if (Main_menu->getChangeScene() == Window_Scene::Edit_File)
			{
				//�G�f�B�b�g
				mNowScene = Window_Scene::Edit_File; //�ҏW�E�C���h�E�Ɉڍs
			}
			Main_menu->Reset();	//�E�C���h�E�����Z�b�g
		}
	}break;
	
		//�ҏW
	case Window_Scene::Edit_File:
	{
		EditFile_menu->Update(); //�X�V

		if (EditFile_menu->getChangeScene() != Window_Scene::Invalid)
		{
			std::vector<char*> tmp = EditFile_menu->getInputKeyData();	//�L�[���͂��擾

			//����
			if (EditFile_menu->getChangeScene() == Window_Scene::Yes)
			{
				if (CheckFile(tmp.at(0)) == true) 
				{
					//�t�@�C�������݂��鎞

					memcpy(data.FileName, tmp.at(0), sizeof(data.FileName));	//�t�@�C������ݒ�	
					Type = Scene_Type::Game;								//Game �V�[���Ɉړ�
					data.EditMode = WRITE_EDIT;								//�G�f�B�b�g���[�h

	
				}
				else {
					//�t�@�C�������݂��Ȃ���
					memcpy(FileName, tmp.at(0), sizeof(FileName));	//�t�@�C�������R�s�[
					mNowScene = Window_Scene::CheckFileError; //�t�@�C��������܂���G���[�V�[���ɐ���
				}
			}
			
			EditFile_menu->Reset();	//�E�C���h�E�����Z�b�g
		}
	}break;

		//�t�@�C�������݂��Ȃ���
	case Window_Scene::CheckFileError:
	{
		CheckFileError_menu->Update(); //�X�V

		if (CheckFileError_menu->getChangeScene() != Window_Scene::Invalid)
		{		
			//����
			if (CheckFileError_menu->getChangeScene() == Window_Scene::Yes)
			{
				mNowScene = Window_Scene::Edit_File; //�ҏW�t�@�C�������̓E�C���h�E�ɖ߂�
			}
			CheckFileError_menu->Reset();	//�E�C���h�E�����Z�b�g
		}
	}break;

		//�V�K�쐬
	case Window_Scene::New_File:
	{
		NewFile_menu->Update();	//�X�V

		if (NewFile_menu->getChangeScene() != Window_Scene::Invalid) 
		{
			//����̎�
			if (NewFile_menu->getChangeScene() == Window_Scene::Yes)
			{
				std::vector<char*> tmp = NewFile_menu->getInputKeyData();	//���̓f�[�^���擾

				//�t�@�C���������݂��邩�ǂ����H
				if (CheckFile(tmp.at(0)) == true)
				{
					//���݂���ꍇ

					memcpy(FileName, tmp.at(0), sizeof(FileName));	//�t�@�C�������擾
					mNowScene = Window_Scene::Check;				//�㏑���m�F�E�C���h�E�Ɉڍs

				}
				else {
					//���݂��Ȃ��ꍇ

					memcpy(FileName, tmp.at(0), sizeof(data.FileName));	//�t�@�C�������擾
					mNowScene = Window_Scene::SizeSet; //�T�C�Y�ݒ�E�C���h�E�Ɉڍs

				}
			}

			NewFile_menu->Reset(); //�E�C���h�E�����Z�b�g
		}
	}break;

		//�T�C�Y�w��
	case Window_Scene::SizeSet:
	{
		SizeSet_menu->Update();	//�X�V

		if (SizeSet_menu->getChangeScene() != Window_Scene::Invalid) {

			//����
			if (SizeSet_menu->getChangeScene() == Window_Scene::Yes)
			{
				std::vector<char*> tmp = SizeSet_menu->getInputKeyData();	//���̓f�[�^�[���擾

				//�T�C�Y��ݒ�
				data.StageSize.x = atoi(tmp.at(0));	//X
				data.StageSize.y = atoi(tmp.at(1));	//Y

				// �X�e�[�W�T�C�Y���s�����ǂ����H
				if (data.StageSize.y > 0 && data.StageSize.x > 0)
				{
					memcpy(data.FileName, FileName, sizeof(data.FileName));	//�t�@�C������ݒ�	
					Type = Scene_Type::Game;								//Game �V�[���Ɉړ�
					data.EditMode = WRITE_NEW;								//�G�f�B�b�g���[�h
				}
				else {
					//�s���̎�

					mNowScene = Window_Scene::SizeSetError;	//�T�C�Y�w��G���[��ʂɐ���
				}
			}
			else if (SizeSet_menu->getChangeScene() == Window_Scene::No) {

				//�߂�
				mNowScene = Window_Scene::New_File;	//�V�K�쐬��ʂɐ���
			}

			SizeSet_menu->Reset(); //�E�C���h�E�����Z�b�g
		}

	}break;

	//�T�C�Y�w��G���[
	case Window_Scene::SizeSetError:
	{
		SizeSetError_menu->Update();	//�X�V

		//�߂�
		if (SizeSetError_menu->getChangeScene() != Window_Scene::Invalid)
		{
			mNowScene = Window_Scene::SizeSet; //�T�C�Y�w��E�C���h�E�Ɉڍs

			SizeSetError_menu->Reset();	//�E�C���h�E�����Z�b�g
		}

	}break;



	//�㏑���m�F
	case Window_Scene::Check:
	{
		CheckFile_menu->Update();	//�X�V

		if (CheckFile_menu->getChangeScene() != Window_Scene::Invalid)
		{
			//����
			if (CheckFile_menu->getChangeScene() == Window_Scene::Yes)
			{
				memcpy(data.FileName, FileName, sizeof(data.FileName));	//�t�@�C������ݒ�	
				Type = Scene_Type::Game;								//Game �V�[���Ɉړ�
				data.EditMode = WRITE_OVERRITE;							//�G�f�B�b�g���[�h

			}else if (CheckFile_menu->getChangeScene() == Window_Scene::No)
			{
				//�߂�
				mNowScene = Window_Scene::New_File;	//�V�K�t�@�C�����͉�ʂɖ߂�B
			}
			CheckFile_menu->Reset();	//�E�C���h�E�����Z�b�g
		}

	}break;






	}

}

//�`��
void StartMenu::Draw()
{
	switch (mNowScene) 
	{
		//���C�����j���[
	case Window_Scene::Main:
	{
		Main_menu->Draw();
	}break;

	//���C�����j���[
	case Window_Scene::New_File:
	{
		NewFile_menu->Draw();
	}break;

	//�T�C�Y�w��
	case Window_Scene::SizeSet:
	{
		SizeSet_menu->Draw();
	}break;
	
	//�T�C�Y�w��G���[
	case Window_Scene::SizeSetError:
	{
		SizeSetError_menu->Draw();
	}break;

	//�㏑���`�F�b�N�m�F
	case Window_Scene::Check:
	{
		CheckFile_menu->Draw();
	}break;

	//�ҏW
	case Window_Scene::Edit_File:
	{
		EditFile_menu->Draw();
	}break;

	//�ҏW
	case Window_Scene::CheckFileError:
	{
		CheckFileError_menu->Draw();
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


EditData StartMenu::getEditData()
{
	return data;
}

//�f�X�g���N�^
StartMenu::~StartMenu()
{

}

