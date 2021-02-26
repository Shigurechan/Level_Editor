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

	type = Scene_Type::Title;	//�ŏ��̃V�[��
}

//�X�v���C�g�����[�h
int Entry::LoadSprite(const char* FileName)
{
	int a = LoadGraph(FileName);

	if (a == -1)
	{
		printf("�t�@�C�������݂��܂���B%s \n",FileName);
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

	switch (type)
	{
		//���C���Q�[��
	case Scene_Type::Game:
	{
		game->Update();
		type = game->getSceneType();
	}break;


	//�^�C�g��
	case Scene_Type::Title:
	{
		start->Update();
		type = start->getSceneType();
	}break;



	};
}

//�`��
void Entry::Draw()
{
	switch (type)
	{
		//���C���Q�[��
	case Scene_Type::Game:
	{
		game->Draw();
		type = game->getSceneType();
	}break;


	//�^�C�g��
	case Scene_Type::Title:
	{
		start->Draw();
		type = start->getSceneType();
	}break;





	};
}

//�f�X�g���N�^
Entry::~Entry()
{
	
}

