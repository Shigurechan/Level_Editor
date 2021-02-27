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

//������
void Game_Scene::SetUp()
{
	/*
	//�V�K�쐬��������
	if (Data.EditMode == (byte)WRITE_NEW)
	{
		printf("�V�K�t�@�C�����쐬\n");
		fopen_s(&fp, Data.FileName, "wb"); //�������ݐ�p���[�h
	} 
	*/


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

	//�o�C�i���t�@�C���ɃX�e�[�W�����������ނ��ǂ����H
	if (control->isWrite_File == true)
	{
		stage->WriteFile(Data);
		control->isWrite_File = false;
	}








}


//�G�f�B�b�g�f�[�^���擾
void Game_Scene::getEditData(EditData data)
{
	Data = data;
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
