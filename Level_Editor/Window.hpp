#ifndef ___WINDOW_HPP_
#define ___WINDOW_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"
#include <string>
#include <vector>
#include <iostream>

#include "Entry.hpp"
#include "Input.hpp"
#include "Actor.hpp"

#include "UI.hpp"

// ���j���[����
enum class Window_Scene
{
	Main,	//�ŏ��̉��
	Item,	//�A�C�e��

	//���j���[
	Buy_Menu,
	Sell_Menu,

	//����
	Buy_Conf,
	Sell_Conf,


	Check,
	Yes,
	No,

	New_File,
	Edit_File,

	OverWrite_Check,	//�㏑���`�F�b�N

	WriteFile_OverWrite,	//�㏑���쐬
	Write_NewFile,			//�V�K�쐬	
	Write_EditFile,			//�ҏW

	//�߂�@�I��
	End,
	Back,
	Invalid,
};

//�E�C���h�E�̍���
typedef struct List_Item
{
	glm::ivec2 pos;			// ���W
	glm::ivec2 size;		//�T�C�Y
	std::string name;		// ���O
	Window_Scene winScene;	// ���j���[����
	unsigned char ID;		// �A�C�e��ID
	unsigned int Color;		//�`��F


}List_Item;



//�O���錾

/*####################################################
* �E�C���h�E���
*
* ����
* �\���I�����郁�j���[���
######################################################*/
class Window : public Actor
{
public:


	Window(Entry* e, Window_Scene s, glm::ivec2 pos, glm::ivec2 size);	//�R���X�g���N�^
	~Window();							//�f�X�g���N�^





	// ################## �ݒ�@�֌W
	void setTitle(std::string name, unsigned int c);	//�^�C�g��
	void setPosition(glm::ivec2 pos);					//���W
	void setSize(glm::ivec2 size);						//�T�C�Y
	void setBackColor(unsigned int c);					//�w�i�F

	void AddList_Down(Window_Scene s, std::string name, unsigned char num, unsigned int c); //�E�C���h�E�ɍ��ڂ�ǉ�

	void Reset();
	unsigned char getItem();


	
	Window_Scene getChangeScene();									//�V�[�����ڂ��擾
	


	void Update();	//�v�Z
	void Draw();	//�`��

private:

	RectangleData window;			//��ʃT�C�Y

	std::string Title;					//�^�C�g��
	unsigned int TitleColor;			//�^�C�g���F





	unsigned int BackGroundColor;		//�w�i�F



	std::vector<List_Item> lists;		//���j���[����
	
	int Cursor;		//�J�[�\���ړ�


	Window_Scene Scene;			//���̃E�C���h�E�̃V�[��
	Window_Scene Move_Scene;	//�ړ�����V�[��
	unsigned char ID;			//�A�C�e����I��
	

	glm::ivec2 ItemPos;	//���ڂ̍��W�𒲐�




};


#endif
