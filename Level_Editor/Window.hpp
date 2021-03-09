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


#define INPUT_NONE 0		//入力なし
#define INPUT_NUMBER 1		//数値入力
#define INPUT_CHARACTER 2	//文字入力

// メニュー推移
enum class Window_Scene
{
	Main,	//最初の画面
	Item,	//アイテム

	//メニュー
	Buy_Menu,
	Sell_Menu,

	//決定
	Buy_Conf,
	Sell_Conf,


	Check,
	Yes,
	No,

	StageSelect,
	ChipSelect,
	ChangeSize,


	SizeSetOverWrite,

	New_File,		//新規作成
	Edit_File,		//編集

	SizeSetError,	//サイズ指定のエラー

	SizeSet,		//サイズを指定

	OverWrite_Check,	//上書きチェック

	CheckFileError,	//ファイルが存在するかどうか確認画面


	WriteFile_OverWrite,	//上書き作成
	Write_NewFile,			//新規作成	
	Write_EditFile,			//編集

	//戻る　終了
	End,
	Back,
	Invalid,
	None, //シーン推移ではない。
};

// ##### ウインドウの項目
typedef struct List_Item
{
	glm::ivec2 pos;			// 座標
	glm::ivec2 size;		//サイズ
	std::string name;		// 名前
	Window_Scene winScene;	// メニュー推移
	byte ID;				// アイテムID
	unsigned int Fore_Color;	//前景色
	unsigned int Back_Color;	//背景色

	//入力関係
	bool isInput_String;	//文字列入力かどうか？
	bool isInput_Number;	//数値入力かどうか？
	int InputHandle;		//キー入力ハンドル

	//char InputKeyData[INPUT_KEY_NUMBER_MAX];	//入力データ
	std::string InputKeyData;	//入力データ

}List_Item;



//前方宣言

/*####################################################
* ウインドウ画面
*
* 説明
* 十字選択するメニュー画面
######################################################*/
class Window : public Actor
{
public:

	Window(Entry* e, Window_Scene s, glm::ivec2 pos, glm::ivec2 size);	//コンストラクタ
	~Window();															//デストラクタ

	// ################## 設定　関係
	void setTitle(std::string name, unsigned int c);	//タイトル
	void setPosition(glm::ivec2 pos);					//座標
	void setSize(glm::ivec2 size);						//サイズ
	void setBackColor(unsigned int c);					//背景色
	void setInput_String();								//文字列を入力するかどうか？
	void AddList_Down(Window_Scene s, std::string name, byte , unsigned int c, unsigned int b, byte input = 0);			//ウインドウに項目を追加
	void Reset();	//設定をリセット
	void setCursorSelectBackColor(unsigned int c);	//カーソルの選択背景色
	void setSentence(const char* stc);				//文章を追加


	// ################## 取得　関係
	Window_Scene getChangeScene();				//シーン推移を取得
	std::vector<std::string> getInputKeyData();	//キー入力情報			
	byte getItem();	//識別子IDを取得


	void Update();	//計算
	void Draw();	//描画

private:

	RectangleData window;			//画面サイズ

	std::string Title;					//タイトル
	unsigned int TitleColor;			//タイトル色


	//テスト

	char name[INPUT_KEY_NUMBER_MAX];
	char size_x[INPUT_KEY_NUMBER_MAX];
	char size_y[INPUT_KEY_NUMBER_MAX];

	char str[INPUT_KEY_NUMBER_MAX];

	unsigned int BackGroundColor;		//ウインドウ背景色
	unsigned int CursorSelectColor;		//カーソルの選択時の背景色

	std::vector<std::string> InputKeyData;	//キー入力を返す

	std::vector<List_Item> lists;		//メニュー項目
	
	int Cursor;		//カーソル移動


	Window_Scene Scene;			//このウインドウのシーン
	Window_Scene Move_Scene;	//移動するシーン
	unsigned char ID;			//アイテムを選択
	

	glm::ivec2 ItemPos;	//項目の座標を調整

	int KeyInput_String_Handle;	//文字入力ハンドル
	int KeyInput_Number_Handle;	//数値入力ハンドル

	std::vector<std::vector<std::string>> sentenceLine;	//文章

	bool isInput_Number;	//数値を入力するかどうか？
	bool isInput_String;	//文字列を入力するかどうか？
	bool isCusorBackColor;	//カーソル選択時の項目の背景色を変えるかどうか？


};


#endif
