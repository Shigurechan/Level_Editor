#include "Window.hpp"

//コンストラクタ
Window::Window(Entry * e,Window_Scene s, glm::ivec2 pos, glm::ivec2 size) : Actor(e)
{
	Scene = s;							//ウインドウ種別
	Move_Scene = Window_Scene::Invalid;	//移動するシーン
	Cursor = 0;	//カーソル
	isInputNumber = false; //数値を入力するかどうか？

	setPosition(pos);								//座標
	setSize(size);									//大きさ
	BackGroundColor = GetColor(255,255,255);		//既定　背景色
	setTitle("未設定タイトル",GetColor(0, 0, 0));		//既定　タイトル

	ItemPos = pos;
}


// ################## 設定　関係

//数値を入力するかどうか？
void Window::setInputNumber()
{
	printf("setInputNumber()\n");
	KeyInputNumber_Handle = MakeKeyInput(INPUT_KEY_NUMBER, false, true, false);	//キー入力ハンドルを作成
	isInputNumber = true;														//入力を有効にする。
	SetActiveKeyInput(KeyInputNumber_Handle);									//入力をアクティブ

}

//タイトル
void Window::setTitle(std::string name,unsigned int c)
{
	Title = name;	//表示文字
	TitleColor = c;	//描画色
}

//座標
void Window::setPosition(glm::ivec2 pos)	
{
	mPosition = pos;
}

//サイズ
void Window::setSize(glm::ivec2 size)	
{
	mSize.x = mPosition.x + size.x;
	mSize.y = mPosition.y + size.y;
}

//背景色
void Window::setBackColor(unsigned int c)		
{
	BackGroundColor = c;
}

//シーンを推移
Window_Scene Window::getChangeScene()
{

	return Move_Scene;
}

void Window::Reset()
{
	ID = 0;
	Move_Scene = Window_Scene::Invalid;
}



/* ウインドウに項目を追加
* 
* 説明
* 
* 引数
* シーンの推移
* 名前
* アイテムID
* 描画色
*/
void Window::AddList_Down(Window_Scene s,std::string name,unsigned char num,unsigned int c)
{
	//printf("あああ");
	List_Item item;

	item.name = name;	//名前
	item.Color = c;		//カラー

	
	//座標
	ItemPos.y += 20;
	ItemPos.x = mPosition.x + 50;
	item.pos = ItemPos;
	

	//背景色の描画の大きさ
	item.size.x = GetDrawStringWidth(name.c_str(), (int)strlen(name.c_str())) + ItemPos.x + 50;
	item.size.y = ItemPos.y;



	item.winScene = s;	//ウインドウシーン

	item.ID = num;	//アイテムID

	lists.push_back(item);
}

// ################## 取得　関係

unsigned char Window::getItem()
{
	return ID;
}

//計算
void Window::Update()
{
	//数値を入力
	if (isInputNumber == true)
	{	
		GetKeyInputString(lists.at(Cursor).InputKeyData, KeyInputNumber_Handle);
		printf("数値入力:　%s\n", lists.at(Cursor).InputKeyData);

	}


	//キー入力	
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
		Move_Scene = lists.at(Cursor).winScene;	//シーン推移
		ID = lists.at(Cursor).ID;	//アイテムID
	}









}

//描画
void Window::Draw()
{
#define FRAME_COLOR GetColor(0,100,0)	//フレームの色
#define CURSOR_COLOR GetColor(0,0,0)	//カーソルの色

	DrawBox(mPosition.x, mPosition.y, mSize.x, mSize.y, BackGroundColor, true);	//背景

	DrawBox(mPosition.x, mPosition.y, mSize.x, mSize.y, FRAME_COLOR, false);	//枠
	DrawBox(mPosition.x - 1, mPosition.y - 1, mSize.x + 1, mSize.y + 1, FRAME_COLOR, false);	//枠
	DrawBox(mPosition.x - 2, mPosition.y - 2, mSize.x + 2, mSize.y + 2, FRAME_COLOR, false);	//枠
	DrawBox(mPosition.x - 3, mPosition.y - 3, mSize.x + 3, mSize.y + 3, FRAME_COLOR, false);	//枠
	DrawBox(mPosition.x - 4, mPosition.y - 4, mSize.x + 4, mSize.y + 4, FRAME_COLOR, false);	//枠
	

	DrawFormatString(mPosition.x + 2, mPosition.y + 4, TitleColor,"%s",Title.c_str());	//タイトル


	//項目を表示
	for (std::vector<List_Item>::iterator itr = lists.begin(); itr != lists.end(); itr++)
	{
		List_Item item = *itr;
		if (lists.at(Cursor).pos == item.pos)
		{

			//カーソルの場所
			DrawFormatString(itr->pos.x - 50, itr->pos.y, CURSOR_COLOR, "-->");		//カーソル
			DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + 100, itr->pos.y + 16, GetColor(0,100,0), true);	//背景

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Color, "%s", itr->name.c_str());	//項目
		}
		else {

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Color, "%s", itr->name.c_str());	//項目
		}
	}
}


//デストラクタ
Window::~Window()
{

}


