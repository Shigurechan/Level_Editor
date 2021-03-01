#ifndef ___ENTRY_HPP_
#define ___ENTRY_HPP_

#include "Input.hpp"
#include <iostream>
class Game_Scene;
class StartMenu;

#define CELL ((int)48)	//セル

typedef unsigned char byte;	//バイト


//画面サイズ
#define SCREEN_WIDTH ((int)(16 + 10) * CELL)
#define SCREEN_HEIGHT ((int)(9 + 10)  * CELL)

//ステージ
#define STAGE_WIDTH ((int)100 * CELL)
#define STAGE_HEIGHT ((int)100 * CELL)

//ステージのセル数
#define STAGE_GRID_X ((int)(STAGE_WIDTH / CELL))
#define STAGE_GRID_Y ((int)(STAGE_HEIGHT / CELL))

//方向
#define VECTOR_UP glm::ivec2(0,-1)
#define VECTOR_DOWN glm::ivec2(0,1)
#define VECTOR_LEFT glm::ivec2(-1,0)
#define VECTOR_RIGHT glm::ivec2(1,0)

#define PI ((float)3.14159265359)	//PI

//ファイルモード
#define WRITE_OVERRITE 0	//上書き
#define WRITE_NEW 1			//新規作成
#define WRITE_Edit 2		//編集




//エディット情報
typedef struct EditData
{
	byte EditMode;			//エディットモード
	char FileName[200];	//書き込むファイル名


}EditData;


// シーンの種類
enum class Scene_Type
{
	Title,		//タイトル
	Game,		//メインゲーム
	GameOver,	//ゲームオーバー


	Menu,		//メニュー
	Pause,		//一時停止
};



/*####################################################
* シーン推移
* 
* 説明
* シーンの推移を行う
######################################################*/
class Entry
{
public:

	Entry();	//コンストラクタ
	~Entry();	//デストラクタ

	void Update();	//計算
	void Draw();	//描画
	int GetRand(int start, int end);	//乱数を取得
	
	int LoadSprite(const char* FileName);				//スプライトをロード


	std::shared_ptr<Input> InputKey;	//キー入力

private:

	std::shared_ptr<Game_Scene> game;	//エディット画面

	std::shared_ptr<StartMenu> start;	//ファイル選択画面

	Scene_Type type;

	EditData data;
};


#endif

