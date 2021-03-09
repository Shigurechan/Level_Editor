#include "Entry.hpp"
#include "Edit_Scene.hpp"

//�R���X�g���N�^
Entry::Entry()
{
	//printf("SCRREN_WIDTH : %d\n", SCREEN_WIDTH);
	//printf("SCRREN_HEIGHT : %d\n",SCREEN_HEIGHT);

	InputKey = std::make_shared<Input>();	//�L�[����

	
	Edit = std::make_shared<Edit_Scene>(Scene_Type::Edit, this);

	Scene = Scene_Type::SetUp;	//�ŏ��̃V�[��
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


//D&D�p�X���擾
std::string Entry::GetDragPath()
{
	//	printf("Command %s\n\n", GetCommandLine());
	std::string cmd(GetCommandLine());
	int all = cmd.length();	//�S���̕�����
	int f = cmd.find(' ');	//���o���ʒu
	cmd = cmd.substr((f + 1), all - f);

	//printf("%s ",cmd.c_str());
	return cmd;
}

//�v�Z
void Entry::Update()
{
	InputKey->Update();

	switch (Scene)	
	{

		//������
	case Scene_Type::SetUp:
	{

		Edit->SetUp();	//������

		Scene = Scene_Type::Edit;
	}break;

		//�G�f�B�b�g
	case Scene_Type::Edit:
	{

		Edit->Update();					//�X�V
		Scene = Edit->getSceneType();	//�V�[������
	}break;




	};
}

//�`��
void Entry::Draw()
{
	switch (Scene)
	{
	
	//
	case Scene_Type::Edit:
	{
		Edit->Draw();
		Scene = Edit->getSceneType();
	}break;




	};
}

//�f�X�g���N�^
Entry::~Entry()
{
	
}

