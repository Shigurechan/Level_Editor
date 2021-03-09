#include "Entry.hpp"
#include "Edit_Scene.hpp"

//コンストラクタ
Entry::Entry()
{
	//printf("SCRREN_WIDTH : %d\n", SCREEN_WIDTH);
	//printf("SCRREN_HEIGHT : %d\n",SCREEN_HEIGHT);

	InputKey = std::make_shared<Input>();	//キー入力

	
	Edit = std::make_shared<Edit_Scene>(Scene_Type::Edit, this);

	Scene = Scene_Type::SetUp;	//最初のシーン
}

//スプライトをロード
int Entry::LoadSprite(const char* FileName)
{
	int a = LoadGraph(FileName);

	if (a == -1)
	{
		printf("ファイルが存在しません。Path: %s \n",FileName);
		return -1;
	}
	else {
		return a;
	}
}


//D&Dパスを取得
std::string Entry::GetDragPath()
{
	//	printf("Command %s\n\n", GetCommandLine());
	std::string cmd(GetCommandLine());
	int all = cmd.length();	//全部の文字列
	int f = cmd.find(' ');	//取り出す位置
	cmd = cmd.substr((f + 1), all - f);

	//printf("%s ",cmd.c_str());
	return cmd;
}

//計算
void Entry::Update()
{
	InputKey->Update();

	switch (Scene)	
	{

		//初期化
	case Scene_Type::SetUp:
	{

		Edit->SetUp();	//初期化

		Scene = Scene_Type::Edit;
	}break;

		//エディット
	case Scene_Type::Edit:
	{

		Edit->Update();					//更新
		Scene = Edit->getSceneType();	//シーン推移
	}break;




	};
}

//描画
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

//デストラクタ
Entry::~Entry()
{
	
}

