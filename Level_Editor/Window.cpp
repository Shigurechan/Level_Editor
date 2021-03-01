#include "Window.hpp"

//�R���X�g���N�^
Window::Window(Entry * e,Window_Scene s, glm::ivec2 pos, glm::ivec2 size) : Actor(e)
{

	KeyInput_String_Handle = MakeKeyInput(INPUT_KEY_NUMBER_MAX, false, true, false);	//������@�L�[���̓n���h�����쐬	
	KeyInput_Number_Handle = MakeKeyInput(INPUT_KEY_NUMBER_MAX, false, true, true);		//���l�@�L�[���̓n���h�����쐬	

	Scene = s;							//�E�C���h�E���
	Move_Scene = Window_Scene::Invalid;	//�ړ�����V�[��
	Cursor = 0;	//�J�[�\��

	isInput_String = false;		//���l����͂��邩�ǂ����H
	isInput_Number = false;		//��������͂��邩�ǂ����H
	isCusorBackColor = false;	//�J�[�\���I�����̔w�i�F��ς��邩�ǂ����H

	setPosition(pos);								//���W
	setSize(size);									//�傫��
	BackGroundColor = GetColor(255,255,255);		//����@�w�i�F
	CursorSelectColor = GetColor(255, 255, 255);	//����@�J�[�\���̑I�����̔w�i�F

	setTitle("���ݒ�^�C�g��",GetColor(0, 0, 0));		//����@�^�C�g��

	ItemPos = pos;	//�A�C�e�����X�g���W�̃I�t�Z�b�g
}


// ################## �ݒ�@�֌W

//��������͂��邩�ǂ����H
void Window::setInput_String()
{

}

//�^�C�g��
void Window::setTitle(std::string name,unsigned int c)
{
	Title = name;	//�\������
	TitleColor = c;	//�`��F
}

//���W
void Window::setPosition(glm::ivec2 pos)	
{
	mPosition = pos;
}

//�T�C�Y
void Window::setSize(glm::ivec2 size)	
{
	mSize.x = mPosition.x + size.x;
	mSize.y = mPosition.y + size.y;
}

//�w�i�F
void Window::setBackColor(unsigned int c)		
{
	BackGroundColor = c;
}

//�V�[���𐄈�
Window_Scene Window::getChangeScene()
{

	return Move_Scene;
}

void Window::Reset()
{
	ID = 0;
	Move_Scene = Window_Scene::Invalid;
}



/* �E�C���h�E�ɍ��ڂ�ǉ�
* 
* ����
* 
* �V�[���̐���
* ���O
* ���ʎqID
* �`��F
* �w�i�F
*/
void Window::AddList_Down(Window_Scene s,std::string name,byte id_number,unsigned int c,unsigned int b,byte input)
{
#define ITEM_POSITION_OFFSET_Y 25
#define ITEM_POSITION_OFFSET_X 50


	//printf("������");
	List_Item item;

	item.name = name;	//���O

	item.Fore_Color = c;	//�O�i�F
	item.Back_Color = b;	//�w�i�F
	
	//���W
	ItemPos.y += ITEM_POSITION_OFFSET_Y;
	ItemPos.x = mPosition.x + ITEM_POSITION_OFFSET_X;
	item.pos = ItemPos;


	//�w�i�F�̕`��̑傫��
	item.size.x = GetDrawStringWidth(name.c_str(), (int)strlen(name.c_str()));// + ItemPos.x + 50;
	item.size.y = ItemPos.y;


	item.winScene = s;	//�E�C���h�E�V�[��

	item.ID = id_number;	//���ʎqID

	// ###  ���� �ݒ� ###
	//���l����
	if (input == INPUT_NUMBER)
	{
		item.InputHandle = MakeKeyInput(INPUT_KEY_NUMBER_MAX, false, true, true);
		item.isInput_Number = true;
	}
	else if (input == INPUT_CHARACTER) 
	{
		//���������
		item.isInput_String = true;
		item.InputHandle = MakeKeyInput(INPUT_KEY_NUMBER_MAX, false, true, false);
	}
	else
	{
		//���͂Ȃ�		
		item.isInput_String = false;
		item.isInput_Number = false;
	}
	// #######################



	memset(item.InputKeyData, '\0', sizeof(item.InputKeyData));	//���͕����z���������


	lists.push_back(item);
}

//�J�[�\���̑I�����̔w�i�F��ݒ�
void Window::setCursorSelectBackColor(unsigned int c)
{
	CursorSelectColor = c;
	isCusorBackColor = true;
}

// ################## �擾�@�֌W

byte Window::getItem()
{
	return ID;
}

//�L�[���͏���Ԃ�
std::vector<char*> Window::getInputKeyData()
{
	std::vector<char*> tmp;
	
	//�L�[���͕�������x�N�^�[�ϐ��ɓ����B
	for (std::vector<List_Item>::iterator itr = lists.begin(); itr != lists.end(); itr++)
	{
		if (itr->isInput_Number == true || itr->isInput_String == true) 
		{
			tmp.push_back(itr->InputKeyData);
		}
	}

	return tmp;
}

//���͂�ǉ�
void Window::setSentence(const char* stc)
{
	for (int i = 0; i < sizeof(stc); i++)
	{

	}
}





//�v�Z
void Window::Update()
{
	//�L�[����
	if (lists.at(Cursor).isInput_String == true) 
	{
		//�@��������͂̓��͂̏ꍇ
		SetActiveKeyInput(lists.at(Cursor).InputHandle);								//���͂��A�N�e�B�u
		GetKeyInputString(lists.at(Cursor).InputKeyData, lists.at(Cursor).InputHandle);	//��������͂��󂯕t��
		//printf("��������:�@%s\n",lists.at(Cursor).InputKeyData);
	}
	else if(lists.at(Cursor).isInput_Number == true)
	{
		//�@���l�ɓ��͂̏ꍇ
		SetActiveKeyInput(lists.at(Cursor).InputHandle);								//���͂��A�N�e�B�u
		GetKeyInputString(lists.at(Cursor).InputKeyData, lists.at(Cursor).InputHandle);	//���l���͂��󂯕t��
		//printf("���l����:�@%s\n",lists.at(Cursor).InputKeyData);
	}else
	{
		SetActiveKeyInput(-1);	//���͂𖳌�
	}

	//�J�[�\���ړ�
	if (Owner->InputKey->getKeyDown(KEY_INPUT_UP) == true)
	{
		Cursor += -1;
		if (Cursor < 0)
		{
			Cursor = 0;
		}
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_DOWN) == true)
	{
		Cursor += 1;
		if (Cursor > lists.size() - 1)
		{
			Cursor = (int)lists.size() - 1;
		}
	}
	else if (Owner->InputKey->getKeyDown(KEY_INPUT_RETURN) == true)
	{	
		Move_Scene = lists.at(Cursor).winScene;	//�V�[������
		ID = lists.at(Cursor).ID;	//�A�C�e��ID
	}




}

//�`��
void Window::Draw()
{
#define FRAME_COLOR GetColor(0,100,0)			//�t���[���̐F
#define CURSOR_COLOR GetColor(0,0,0)			//�J�[�\���̐F
#define WINDOW_BACK_COLOR GetColor(255,255,255)	//�E�C���h�E�w�i
#define CURSOR_POS_OFFSET  40					//�J�[�\���̍��W�̃I�t�Z�b�g


	DrawBox(mPosition.x, mPosition.y, mSize.x, mSize.y, WINDOW_BACK_COLOR, true);	//�E�C���h�E�w�i

	//�E�C���h�E�t���[��
	DrawBox(mPosition.x, mPosition.y, mSize.x, mSize.y, FRAME_COLOR, false);	
	DrawBox(mPosition.x - 1, mPosition.y - 1, mSize.x + 1, mSize.y + 1, FRAME_COLOR, false);	
	DrawBox(mPosition.x - 2, mPosition.y - 2, mSize.x + 2, mSize.y + 2, FRAME_COLOR, false);	
	DrawBox(mPosition.x - 3, mPosition.y - 3, mSize.x + 3, mSize.y + 3, FRAME_COLOR, false);	
	DrawBox(mPosition.x - 4, mPosition.y - 4, mSize.x + 4, mSize.y + 4, FRAME_COLOR, false);
	DrawBox(mPosition.x - 5, mPosition.y - 5, mSize.x + 5, mSize.y + 5, FRAME_COLOR, false);
	
	DrawFormatString(mPosition.x + 2, mPosition.y + 4, TitleColor,"%s",Title.c_str());	//�^�C�g��


	//���ڂ�\��
	for (std::vector<List_Item>::iterator itr = lists.begin(); itr != lists.end(); itr++)
	{
		List_Item item = *itr;
		if (lists.at(Cursor).pos == itr->pos)
		{
			//�J�[�\���̏ꏊ
			DrawFormatString(itr->pos.x - CURSOR_POS_OFFSET, itr->pos.y, CURSOR_COLOR, "-->");		//�J�[�\��

			//�J�[�\���̔w�i�F
			if (isCusorBackColor == true) 
			{
				DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + itr->size.x, itr->pos.y + 16, CursorSelectColor, true);	//�J�[�\���I�����̔w�i�F
			}
			else 
			{
				DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + itr->size.x, itr->pos.y + 16, itr->Back_Color, true);	//�w�i
			}

			DrawFormatString(itr->pos.x + itr->size.x, itr->pos.y, itr->Fore_Color, "%s", itr->InputKeyData);	//���͕���

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Fore_Color, "%s", itr->name.c_str());			//�O�i
		}
		else {
			DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + itr->size.x, itr->pos.y + 16, itr->Back_Color, true);	//�w�i
			DrawFormatString(itr->pos.x, itr->pos.y, itr->Fore_Color, "%s", itr->name.c_str());			//�O�i

			DrawFormatString(itr->pos.x + itr->size.x, itr->pos.y, itr->Fore_Color, "%s", itr->InputKeyData);//���͕���

		}
	}
}


//�f�X�g���N�^
Window::~Window()
{

}


