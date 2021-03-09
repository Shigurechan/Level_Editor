#ifndef ___ENTRY_HPP_
#define ___ENTRY_HPP_

#include "Input.hpp"
#include "glm/glm.hpp"

#include <iostream>

class Edit_Scene;
class StartMenu;

#define CELL ((int)48)	//セル

typedef unsigned char byte;	//バイト


#define INPUT_KEY_NUMBER_MAX 255	//入力可能最大文字数




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
#define VECTOR_None glm::ivec2(0,0)

#define PI ((float)3.14159265359)	//PI

//ファイルモード
#define WRITE_OVERRITE 0	//上書き
#define WRITE_NEW 1			//新規作成
#define WRITE_EDIT 2		//編集

//スプライト情報
typedef struct SpriteData
{
	int sprite;			//スプライト
	byte bin;			//バイナリ
	std::string name;	//スプライト名
}SpriteData;


//エディット情報　ステージに送る
typedef struct WriteData
{
	int sprite;				//スプライト
	byte bin;				//バイナリ
	glm::ivec2 GridPos;		//グリッド座標

}WriteData;


//オプションを送信する。
typedef struct ConfigData
{
	glm::ivec2 StageSize;
	std::string StageFileName;

}ConfigData;


// シーンの種類
enum class Scene_Type
{
	Title,		//タイトル
	SetUp,
	Edit,		//エディット画面
	GameOver,	//ゲームオーバー


	Menu,		//メニュー
	Pause,		//一時停止
};


// マップオブジェクト
enum class MapObject
{

	None =	0x00,	//なし
	Block = 0x01,	//ブロック
	Brick = 0x02,	//レンガ
	Shop =	0x03,	//ショップ
	Enemy = 0x04,	//エネミー
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
	std::string GetDragPath();			//D&Dパス

private:

	std::shared_ptr<Edit_Scene> Edit;	//エディット画面

	std::shared_ptr<StartMenu> start;	//ファイル選択画面

	Scene_Type Scene;		//現在のシーン
	Scene_Type Prev_Scene;	//前のシーン

	bool changeScene = false; //シーン切り替え
	
};


#endif

