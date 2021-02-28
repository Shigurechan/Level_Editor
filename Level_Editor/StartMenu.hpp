#ifndef ___STARTMENU_HPP
#define ___STARTMENU_HPP

#include "Scene_base.hpp"
#include "Entry.hpp"

class Window;
enum class Window_Scene;
/*####################################################
* ロードメニュー
*
* 説明
* 
* 最初の画面
* ファイルを読み込むかそれとも新規作成かを選択する画面
######################################################*/
enum class Scene_Type;
class Entry;
class StartMenu : public Scene_base
{
public:
	StartMenu(Scene_Type t, Entry* e);	//コンスタラクタ
	~StartMenu();						//デストラクタ

	void Update();	//更新
	void Draw();	//描画

	EditData getData();	//ファイル情報を返す

	bool changeScene;	//シーンを切り替える
private:
	int KeyHandle;	//キー入力ハンドル
	char FileName[256] = { '\0' };	//入力したファイル名

	
	std::shared_ptr<Window> menu;				//メインシーン
	std::shared_ptr<Window> NewFile_menu;		//新規作成でファイル名入力シーン
	std::shared_ptr<Window> EditFile_menu;		//編集するファイル名入力シーン
	std::shared_ptr<Window> CheckFile_menu;		//新規作成でファイルがあるかどうか確認シーン



	Window_Scene type;

	EditData data;	//エディット内容をエディターに伝える
	byte Mode;
	bool CheckFile(const char* FileName);

};

#endif