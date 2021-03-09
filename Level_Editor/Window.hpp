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


#define INPUT_NONE 0		//���͂Ȃ�
#define INPUT_NUMBER 1		//���l����
#define INPUT_CHARACTER 2	//��������

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

	StageSelect,
	ChipSelect,
	ChangeSize,


	SizeSetOverWrite,

	New_File,		//�V�K�쐬
	Edit_File,		//�ҏW

	SizeSetError,	//�T�C�Y�w��̃G���[

	SizeSet,		//�T�C�Y���w��

	OverWrite_Check,	//�㏑���`�F�b�N

	CheckFileError,	//�t�@�C�������݂��邩�ǂ����m�F���


	WriteFile_OverWrite,	//�㏑���쐬
	Write_NewFile,			//�V�K�쐬	
	Write_EditFile,			//�ҏW

	//�߂�@�I��
	End,
	Back,
	Invalid,
	None, //�V�[�����ڂł͂Ȃ��B
};

// ##### �E�C���h�E�̍���
typedef struct List_Item
{
	glm::ivec2 pos;			// ���W
	glm::ivec2 size;		//�T�C�Y
	std::string name;		// ���O
	Window_Scene winScene;	// ���j���[����
	byte ID;				// �A�C�e��ID
	unsigned int Fore_Color;	//�O�i�F
	unsigned int Back_Color;	//�w�i�F

	//���͊֌W
	bool isInput_String;	//��������͂��ǂ����H
	bool isInput_Number;	//���l���͂��ǂ����H
	int InputHandle;		//�L�[���̓n���h��

	//char InputKeyData[INPUT_KEY_NUMBER_MAX];	//���̓f�[�^
	std::string InputKeyData;	//���̓f�[�^

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
	~Window();															//�f�X�g���N�^

	// ################## �ݒ�@�֌W
	void setTitle(std::string name, unsigned int c);	//�^�C�g��
	void setPosition(glm::ivec2 pos);					//���W
	void setSize(glm::ivec2 size);						//�T�C�Y
	void setBackColor(unsigned int c);					//�w�i�F
	void setInput_String();								//���������͂��邩�ǂ����H
	void AddList_Down(Window_Scene s, std::string name, byte , unsigned int c, unsigned int b, byte input = 0);			//�E�C���h�E�ɍ��ڂ�ǉ�
	void Reset();	//�ݒ�����Z�b�g
	void setCursorSelectBackColor(unsigned int c);	//�J�[�\���̑I��w�i�F
	void setSentence(const char* stc);				//���͂�ǉ�


	// ################## �擾�@�֌W
	Window_Scene getChangeScene();				//�V�[�����ڂ��擾
	std::vector<std::string> getInputKeyData();	//�L�[���͏��			
	byte getItem();	//���ʎqID���擾


	void Update();	//�v�Z
	void Draw();	//�`��

private:

	RectangleData window;			//��ʃT�C�Y

	std::string Title;					//�^�C�g��
	unsigned int TitleColor;			//�^�C�g���F


	//�e�X�g

	char name[INPUT_KEY_NUMBER_MAX];
	char size_x[INPUT_KEY_NUMBER_MAX];
	char size_y[INPUT_KEY_NUMBER_MAX];

	char str[INPUT_KEY_NUMBER_MAX];

	unsigned int BackGroundColor;		//�E�C���h�E�w�i�F
	unsigned int CursorSelectColor;		//�J�[�\���̑I�����̔w�i�F

	std::vector<std::string> InputKeyData;	//�L�[���͂�Ԃ�

	std::vector<List_Item> lists;		//���j���[����
	
	int Cursor;		//�J�[�\���ړ�


	Window_Scene Scene;			//���̃E�C���h�E�̃V�[��
	Window_Scene Move_Scene;	//�ړ�����V�[��
	unsigned char ID;			//�A�C�e����I��
	

	glm::ivec2 ItemPos;	//���ڂ̍��W�𒲐�

	int KeyInput_String_Handle;	//�������̓n���h��
	int KeyInput_Number_Handle;	//���l���̓n���h��

	std::vector<std::vector<std::string>> sentenceLine;	//����

	bool isInput_Number;	//���l����͂��邩�ǂ����H
	bool isInput_String;	//���������͂��邩�ǂ����H
	bool isCusorBackColor;	//�J�[�\���I�����̍��ڂ̔w�i�F��ς��邩�ǂ����H


};


#endif
