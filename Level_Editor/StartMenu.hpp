#ifndef ___STARTMENU_HPP
#define ___STARTMENU_HPP

#include "Scene_base.hpp"
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

private:

	
	std::shared_ptr<Window> menu;

	Window_Scene type;


};

#endif

