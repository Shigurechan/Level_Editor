#ifndef ___STARTMENU_HPP
#define ___STARTMENU_HPP

#include "Scene_base.hpp"
#include "Entry.hpp"

/*####################################################
* ロードメニュー
*
* 説明
* 
* 最初の画面
* ファイルを読み込むかそれとも新規作成かを選択する画面
######################################################*/

enum class Scene_Type;
enum class Window_Scene;
class Entry;
class Window;

class StartMenu : public Scene_base
{
public:
	StartMenu(Scene_Type t, Entry* e);	//コンスタラクタ
	~StartMenu();						//デストラクタ

	void Update();	//更新
	void Draw();	//描画

	EditData getEditData();	//ファイル情報を返す

	bool changeScene;	//シーンを切り替える
private:
	
	std::shared_ptr<Window> Main_menu;				//メインシーン
	std::shared_ptr<Window> NewFile_menu;		//新規作成でファイル名入力シーン
	std::shared_ptr<Window> EditFile_menu;		//編集するファイル名入力シーン
	std::shared_ptr<Window> CheckFile_menu;		//新規作成でファイルがあるかどうか確認シーン
	
	std::shared_ptr<Window> SizeSet_menu;		//新規作成でステージサイズを設定するシーン
	std::shared_ptr<Window> SizeSetError_menu;		//サイズを設定しない時の表示

	std::shared_ptr<Window> CheckFileError_menu;		//ファイルが存在しない時のウインドウ




	std::shared_ptr<Window> test_menu;	//テスト用








	Window_Scene mNowScene;	//現在のウインドウシーン推移

	EditData data;	//エディット内容をエディターに伝える
	byte Mode;		//モード
	bool CheckFile(const char* FileName);	//ファイルが存在するかどうか？
	char FileName[INPUT_KEY_NUMBER_MAX] = { '\0' };
};

#endif