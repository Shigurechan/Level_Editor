#include "DxLib.h"
#include <iostream>

#include "Fps.hpp"
#include "Input.hpp"
#include "Entry.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);
	
	ChangeWindowMode(TRUE);// �E�C���h�E���[�h�ŋN��	
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);//	��ʃT�C�Y


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)		
	{
		return -1;			
	}



	std::shared_ptr<Entry> scene = std::make_shared<Entry>();	//�V�[���N���X
	std::shared_ptr<Fps> fps = std::make_shared<Fps>();			//�t���[�����[�g
	std::shared_ptr<Input> input = std::make_shared<Input>();	//�L�[����




	while (true)
	{
		fps->Update();					//FPS�X�V		
		SetDrawScreen(DX_SCREEN_BACK);	//�o�b�N�o�b�t�@�[�ɕ`�����w��
		input->Update();				//�L�[���͂��X�V





		scene->Update();	//�v�Z
		scene->Draw();		//�`��



		//ESC�L�[�ŏI��
		if (input->getKeyDown(KEY_INPUT_ESCAPE) == true)
		{
			break;
		}


		ScreenFlip();		//�X���b�v�o�b�t�@
		ClearDrawScreen();	//��ʂ��N���A
		ProcessMessage();	//���b�Z�[�W����
		fps->Wait();		//FPS�ҋ@

	}
	
	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}