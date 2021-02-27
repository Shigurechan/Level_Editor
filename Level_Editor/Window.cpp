#include "Window.hpp"

//�R���X�g���N�^
Window::Window(Entry * e,Window_Scene s, glm::ivec2 pos, glm::ivec2 size) : Actor(e)
{
	Scene = s;							//�E�C���h�E���
	Move_Scene = Window_Scene::Invalid;	//�ړ�����V�[��
	Cursor = 0;	//�J�[�\��


	setPosition(pos);								//���W
	setSize(size);									//�傫��
	BackGroundColor = GetColor(255,255,255);		//����@�w�i�F
	setTitle("���ݒ�^�C�g��",GetColor(0, 0, 0));		//����@�^�C�g��

	ItemPos = pos;
}


// ################## �ݒ�@�֌W


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
* ����
* �V�[���̐���
* ���O
* �A�C�e��ID
* �`��F
*/
void Window::AddList_Down(Window_Scene s,std::string name,unsigned char num,unsigned int c)
{
	//printf("������");
	List_Item item;

	item.name = name;	//���O
	item.Color = c;		//�J���[

	
	//���W
	ItemPos.y += 20;
	ItemPos.x = mPosition.x + 50;
	item.pos = ItemPos;
	

	//�w�i�F�̕`��̑傫��
	item.size.x = GetDrawStringWidth(name.c_str(), (int)strlen(name.c_str())) + ItemPos.x + 50;
	item.size.y = ItemPos.y;



	item.winScene = s;	//�E�C���h�E�V�[��

	item.ID = num;	//�A�C�e��ID

	lists.push_back(item);
}

unsigned char Window::getItem()
{
	return ID;
}


// ################## �擾�@�֌W





//�v�Z
void Window::Update()
{
	//mInput->Update(); // �L�[���͍X�V

	//�L�[����	
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
#define FRAME_COLOR GetColor(0,100,0)	//�t���[���̐F
#define CURSOR_COLOR GetColor(0,0,0)	//�J�[�\���̐F

	DrawBox(mPosition.x, mPosition.y, mSize.x, mSize.y, BackGroundColor, true);	//�w�i

	DrawBox(mPosition.x, mPosition.y, mSize.x, mSize.y, FRAME_COLOR, false);	//�g
	DrawBox(mPosition.x - 1, mPosition.y - 1, mSize.x + 1, mSize.y + 1, FRAME_COLOR, false);	//�g
	DrawBox(mPosition.x - 2, mPosition.y - 2, mSize.x + 2, mSize.y + 2, FRAME_COLOR, false);	//�g
	DrawBox(mPosition.x - 3, mPosition.y - 3, mSize.x + 3, mSize.y + 3, FRAME_COLOR, false);	//�g
	DrawBox(mPosition.x - 4, mPosition.y - 4, mSize.x + 4, mSize.y + 4, FRAME_COLOR, false);	//�g
	

	DrawFormatString(mPosition.x + 2, mPosition.y + 4, TitleColor,"%s",Title.c_str());	//�^�C�g��


	//���ڂ�\��
	for (std::vector<List_Item>::iterator itr = lists.begin(); itr != lists.end(); itr++)
	{
		List_Item item = *itr;
		if (lists.at(Cursor).pos == item.pos)
		{

			//�J�[�\���̏ꏊ
			DrawFormatString(itr->pos.x - 50, itr->pos.y, CURSOR_COLOR, "-->");		//�J�[�\��
			DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + 100, itr->pos.y + 16, GetColor(0,100,0), true);	//�w�i

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Color, "%s", itr->name.c_str());	//����
		}
		else {

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Color, "%s", itr->name.c_str());	//����
		}
	}
}


//�f�X�g���N�^
Window::~Window()
{

}

