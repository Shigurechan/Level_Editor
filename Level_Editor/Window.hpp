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

	New_File,
	Edit_File,

	OverWrite_Check,	//上書きチェック

	WriteFile_OverWrite,	//上書き作成
	Write_NewFile,			//新規作成	
	Write_EditFile,			//編集

	//戻る　終了
	End,
	Back,
	Invalid,
};

//ウインドウの項目
typedef struct List_Item
{
	glm::ivec2 pos;			// 座標
	glm::ivec2 size;		//サイズ
	std::string name;		// 名前
	Window_Scene winScene;	// メニュー推移
	unsigned char ID;		// アイテムID
	unsigned int Color;		//描画色


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
	~Window();							//デストラクタ





	// ################## 設定　関係
	void setTitle(std::string name, unsigned int c);	//タイトル
	void setPosition(glm::ivec2 pos);					//座標
	void setSize(glm::ivec2 size);						//サイズ
	void setBackColor(unsigned int c);					//背景色

	void AddList_Down(Window_Scene s, std::string name, unsigned char num, unsigned int c); //ウインドウに項目を追加

	void Reset();
	unsigned char getItem();


	
	Window_Scene getChangeScene();									//シーン推移を取得
	


	void Update();	//計算
	void Draw();	//描画

private:

	RectangleData window;			//画面サイズ

	std::string Title;					//タイトル
	unsigned int TitleColor;			//タイトル色





	unsigned int BackGroundColor;		//背景色



	std::vector<List_Item> lists;		//メニュー項目
	
	int Cursor;		//カーソル移動


	Window_Scene Scene;			//このウインドウのシーン
	Window_Scene Move_Scene;	//移動するシーン
	unsigned char ID;			//アイテムを選択
	

	glm::ivec2 ItemPos;	//項目の座標を調整




};


#endif
