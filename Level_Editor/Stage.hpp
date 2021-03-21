#ifndef ___STAGE_HPP_
#define ___STAGE_HPP_

#include "Entry.hpp"
#include "MapChip.hpp"
#include <Dxlib.h>
#include <array>
#include <vector>
#include <map>
#include <iostream>

/*####################################################
* エディットするステージを描画
*
* 説明
* 
* 
######################################################*/

//フレームを描画
typedef struct StageFrame
{
	glm::ivec2 start;	//始点
	glm::ivec2 end;		//終点
	int range;			//長さ
}StageFrame;


class Control;	//操作

class Stage
{
public:
	Stage(Entry *e);	//コンストラクタ
	~Stage();	//デストラクタ

	void Update();		//計算
	void Draw();		//描画



	
	void setGrid(MapChip chip, glm::ivec2 screen_grid);	//グリッドに書き込む
	void setMapChip(std::vector<SpriteData> data);		//マップチップデータを取得
	void WriteFile(std::string file);					//バイナリファイルにステージを書き込む
	void ReadFile(std::string file);					//バイナリファイルを読み込む
	void New_File(std::string name);					//ステージファイルを新規作成
	void CreateNewFile(std::string name);				//ファイルを作成する

	void Scroll(std::shared_ptr<Control> control);		//スクロールする向き

	void setControl(std::shared_ptr<Control> control);	//コントロールからデータを受け取る。

	void SetUp();												//フォルダからステージを読み込む
	void WriteGrid(int sprite, byte bin,glm::ivec2 gridPos);	//ステージに書き込むかどうか？



private:

	//ステージの境界線フレーム
	StageFrame frame_up;
	StageFrame frame_down;
	StageFrame frame_left;
	StageFrame frame_right;


	glm::ivec2 mSize;	//サイズ
	std::shared_ptr<std::vector<std::vector<MapChip>>> mStage;	//ステージ
	std::vector<SpriteData> SpriteList;	//スプライトリスト
	Entry* Owner;
	
	std::vector<std::string> FileNameList;	//ファイルリスト
	



};


#endif
