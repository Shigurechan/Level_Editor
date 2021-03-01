#include "Window.hpp"

//コンストラクタ
Window::Window(Entry * e,Window_Scene s, glm::ivec2 pos, glm::ivec2 size) : Actor(e)
{

	KeyInput_String_Handle = MakeKeyInput(INPUT_KEY_NUMBER_MAX, false, true, false);	//文字列　キー入力ハンドルを作成	
	KeyInput_Number_Handle = MakeKeyInput(INPUT_KEY_NUMBER_MAX, false, true, true);		//数値　キー入力ハンドルを作成	

	Scene = s;							//ウインドウ種別
	Move_Scene = Window_Scene::Invalid;	//移動するシーン
	Cursor = 0;	//カーソル

	isInput_String = false;		//数値を入力するかどうか？
	isInput_Number = false;		//文字を入力するかどうか？
	isCusorBackColor = false;	//カーソル選択時の背景色を変えるかどうか？

	setPosition(pos);								//座標
	setSize(size);									//大きさ
	BackGroundColor = GetColor(255,255,255);		//既定　背景色
	CursorSelectColor = GetColor(255, 255, 255);	//既定　カーソルの選択時の背景色

	setTitle("未設定タイトル",GetColor(0, 0, 0));		//既定　タイトル

	ItemPos = pos;	//アイテムリスト座標のオフセット
}


// ################## 設定　関係

//文字を入力するかどうか？
void Window::setInput_String()
{

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
* シーンの推移
* 名前
* 識別子ID
* 描画色
* 背景色
*/
void Window::AddList_Down(Window_Scene s,std::string name,byte id_number,unsigned int c,unsigned int b,byte input)
{
#define ITEM_POSITION_OFFSET_Y 25
#define ITEM_POSITION_OFFSET_X 50


	//printf("あああ");
	List_Item item;

	item.name = name;	//名前

	item.Fore_Color = c;	//前景色
	item.Back_Color = b;	//背景色
	
	//座標
	ItemPos.y += ITEM_POSITION_OFFSET_Y;
	ItemPos.x = mPosition.x + ITEM_POSITION_OFFSET_X;
	item.pos = ItemPos;


	//背景色の描画の大きさ
	item.size.x = GetDrawStringWidth(name.c_str(), (int)strlen(name.c_str()));// + ItemPos.x + 50;
	item.size.y = ItemPos.y;


	item.winScene = s;	//ウインドウシーン

	item.ID = id_number;	//識別子ID

	// ###  入力 設定 ###
	//数値入力
	if (input == INPUT_NUMBER)
	{
		item.InputHandle = MakeKeyInput(INPUT_KEY_NUMBER_MAX, false, true, true);
		item.isInput_Number = true;
	}
	else if (input == INPUT_CHARACTER) 
	{
		//文字列入力
		item.isInput_String = true;
		item.InputHandle = MakeKeyInput(INPUT_KEY_NUMBER_MAX, false, true, false);
	}
	else
	{
		//入力なし		
		item.isInput_String = false;
		item.isInput_Number = false;
	}
	// #######################



	memset(item.InputKeyData, '\0', sizeof(item.InputKeyData));	//入力文字配列を初期化


	lists.push_back(item);
}

//カーソルの選択時の背景色を設定
void Window::setCursorSelectBackColor(unsigned int c)
{
	CursorSelectColor = c;
	isCusorBackColor = true;
}

// ################## 取得　関係

byte Window::getItem()
{
	return ID;
}

//キー入力情報を返す
std::vector<char*> Window::getInputKeyData()
{
	std::vector<char*> tmp;
	
	//キー入力文字列をベクター変数に入れる。
	for (std::vector<List_Item>::iterator itr = lists.begin(); itr != lists.end(); itr++)
	{
		if (itr->isInput_Number == true || itr->isInput_String == true) 
		{
			tmp.push_back(itr->InputKeyData);
		}
	}

	return tmp;
}

//文章を追加
void Window::setSentence(const char* stc)
{
	for (int i = 0; i < sizeof(stc); i++)
	{

	}
}





//計算
void Window::Update()
{
	//キー入力
	if (lists.at(Cursor).isInput_String == true) 
	{
		//　文字列入力の入力の場合
		SetActiveKeyInput(lists.at(Cursor).InputHandle);								//入力をアクティブ
		GetKeyInputString(lists.at(Cursor).InputKeyData, lists.at(Cursor).InputHandle);	//文字列入力を受け付け
		//printf("文字入力:　%s\n",lists.at(Cursor).InputKeyData);
	}
	else if(lists.at(Cursor).isInput_Number == true)
	{
		//　数値に入力の場合
		SetActiveKeyInput(lists.at(Cursor).InputHandle);								//入力をアクティブ
		GetKeyInputString(lists.at(Cursor).InputKeyData, lists.at(Cursor).InputHandle);	//数値入力を受け付け
		//printf("数値入力:　%s\n",lists.at(Cursor).InputKeyData);
	}else
	{
		SetActiveKeyInput(-1);	//入力を無効
	}

	//カーソル移動
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
#define FRAME_COLOR GetColor(0,100,0)			//フレームの色
#define CURSOR_COLOR GetColor(0,0,0)			//カーソルの色
#define WINDOW_BACK_COLOR GetColor(255,255,255)	//ウインドウ背景
#define CURSOR_POS_OFFSET  40					//カーソルの座標のオフセット


	DrawBox(mPosition.x, mPosition.y, mSize.x, mSize.y, WINDOW_BACK_COLOR, true);	//ウインドウ背景

	//ウインドウフレーム
	DrawBox(mPosition.x, mPosition.y, mSize.x, mSize.y, FRAME_COLOR, false);	
	DrawBox(mPosition.x - 1, mPosition.y - 1, mSize.x + 1, mSize.y + 1, FRAME_COLOR, false);	
	DrawBox(mPosition.x - 2, mPosition.y - 2, mSize.x + 2, mSize.y + 2, FRAME_COLOR, false);	
	DrawBox(mPosition.x - 3, mPosition.y - 3, mSize.x + 3, mSize.y + 3, FRAME_COLOR, false);	
	DrawBox(mPosition.x - 4, mPosition.y - 4, mSize.x + 4, mSize.y + 4, FRAME_COLOR, false);
	DrawBox(mPosition.x - 5, mPosition.y - 5, mSize.x + 5, mSize.y + 5, FRAME_COLOR, false);
	
	DrawFormatString(mPosition.x + 2, mPosition.y + 4, TitleColor,"%s",Title.c_str());	//タイトル


	//項目を表示
	for (std::vector<List_Item>::iterator itr = lists.begin(); itr != lists.end(); itr++)
	{
		List_Item item = *itr;
		if (lists.at(Cursor).pos == itr->pos)
		{
			//カーソルの場所
			DrawFormatString(itr->pos.x - CURSOR_POS_OFFSET, itr->pos.y, CURSOR_COLOR, "-->");		//カーソル

			//カーソルの背景色
			if (isCusorBackColor == true) 
			{
				DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + itr->size.x, itr->pos.y + 16, CursorSelectColor, true);	//カーソル選択時の背景色
			}
			else 
			{
				DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + itr->size.x, itr->pos.y + 16, itr->Back_Color, true);	//背景
			}

			DrawFormatString(itr->pos.x + itr->size.x, itr->pos.y, itr->Fore_Color, "%s", itr->InputKeyData);	//入力文字

			DrawFormatString(itr->pos.x, itr->pos.y, itr->Fore_Color, "%s", itr->name.c_str());			//前景
		}
		else {
			DrawBox(itr->pos.x, itr->pos.y, itr->pos.x + itr->size.x, itr->pos.y + 16, itr->Back_Color, true);	//背景
			DrawFormatString(itr->pos.x, itr->pos.y, itr->Fore_Color, "%s", itr->name.c_str());			//前景

			DrawFormatString(itr->pos.x + itr->size.x, itr->pos.y, itr->Fore_Color, "%s", itr->InputKeyData);//入力文字

		}
	}
}


//デストラクタ
Window::~Window()
{

}


