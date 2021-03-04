#include "Entry.hpp"
#include "Game_Scene.hpp"
#include "StartMenu.hpp"

//�R���X�g���N�^
Entry::Entry()
{
	//printf("SCRREN_WIDTH : %d\n", SCREEN_WIDTH);
	//printf("SCRREN_HEIGHT : %d\n",SCREEN_HEIGHT);

	InputKey = std::make_shared<Input>();	//�L�[����

	game = std::make_shared<Game_Scene>(Scene_Type::Game, this);
	start = std::make_shared<StartMenu>(Scene_Type::Title, this);

	Scene = Scene_Type::Title;	//�ŏ��̃V�[��
}

//�X�v���C�g�����[�h
int Entry::LoadSprite(const char* FileName)
{
	int a = LoadGraph(FileName);

	if (a == -1)
	{
		printf("�t�@�C�������݂��܂���BPath: %s \n",FileName);
		return -1;
	}
	else {
		return a;
	}
}





//�v�Z
void Entry::Update()
{
	InputKey->Update();

	switch (Scene)	
	{

		//�^�C�g��
	case Scene_Type::Title:
	{
		start->Update();				//�X�V
		Scene = start->getSceneType();	//�V�[������
		mData = start->getEditData();	//�G�f�B�b�g�f�[�^���擾
	}break;

		//���C���Q�[��
	case Scene_Type::Game:
	{
		game->Update();					//�X�V
		game->setEditData(mData);		//�G�f�B�b�g�f�[�^��ݒ�
		Scene = game->getSceneType();	//�V�[������
	}break;




	};
}

//�`��
void Entry::Draw()
{
	switch (Scene)
	{

	//�^�C�g��
	case Scene_Type::Title:
	{
		start->Draw();
		Scene = start->getSceneType();
	}break;


	//���C���Q�[��
	case Scene_Type::Game:
	{
		game->Draw();
		Scene = game->getSceneType();
	}break;




	};
}

//�f�X�g���N�^
Entry::~Entry()
{
	
}

