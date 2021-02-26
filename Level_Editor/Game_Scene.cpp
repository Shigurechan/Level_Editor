#include "Game_Scene.hpp"
#include "Stage.hpp"
#include "Control.hpp"


//�R���X�g���N�^
Game_Scene::Game_Scene(Scene_Type t,Entry *e) : Scene_base(t,e)
{
	Owner = e;	//Entry �N���X


	// #####�@�X�v���C�g�����[�h #####

	//int Player_Handle = Owner->LoadSprite("Assets/Player/Player_0.png");	//�v���C���[
	//int Enemy_Handle = Owner->LoadSprite("Assets/Enemy.png");				//�G�l�~�[	
	
	//int Block_Handle = Owner->LoadSprite("Assets/Block.png");	//�u���b�N	
	//int Brick_Handle = Owner->LoadSprite("Assets/Brick.png");	//�����K
	//int Shop_Handle = Owner->LoadSprite("Assets/Shop.png");		//�V���b�v

	// #####�@�R���|�[�l���g #####
	stage = std::make_shared<Stage>();		//�}�b�v�`��
	control = std::make_shared<Control>(Owner);	//����



}

//�X�V
void Game_Scene::Update()
{


	stage->Update();
	control->Update();

	//�O���b�h�̏�������
	if ( control->isWrite_cell == true ){
		stage->setGrid(control->getChip());
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
