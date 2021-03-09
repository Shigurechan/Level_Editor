#ifndef ___CONTROL_HPP_
#define ___CONTROL_HPP_


#include <Dxlib.h>
#include "MapChip.hpp"
#include "Animation.hpp"
#include "Window.hpp"

#include "glm/glm.hpp"
#include <vector>
#include <map>
#include <iostream>

class Entry;

/*####################################################
* コントロール
*
* 説明
* マウスとキーボードによる操作　関係のクラス
######################################################*/

class Control 
{
public:
	Control(Entry* e);	//コンストラクタ
	~Control();									//デストラクタ

	void Update();	//更新
	void Draw();	//描画


	// ##### 設定
	void setPos(glm::ivec2 size);	//カーソル座標
	void setGridPos(glm::ivec2 g);	//グリッド座標を設定
	void setScreenGridPos(glm::ivec2 p);	//スクリーンのグリッド座標を取得
	void SetUp();	//初期化

	// ##### 取得　
	
	glm::ivec2 getGridPos();		//グリッド座標を取得
	glm::ivec2 getVector();			//向き
	glm::ivec2 getScreenGridPos();	//スクリーンのグリッド座標を取得
	ConfigData getConfig();			//コンフィグデータを取得
	std::vector<SpriteData> getMapChip();	//マップチップを取得
	WriteData getWriteData();	//書き込みデータを取得





	
	bool isWrite_cell;	//ステージ情報をバイナリファイルに書き込むかどうか？
	bool isSave;		//セーブする

private:

	void MenuUpdate();	//更新
	void MenuDraw();	//描画

	glm::ivec2 Screen_GridPos;	//画面上のグリッド座標
	glm::ivec2 GridPos;			//ステージのグリッド座標

	glm::ivec2 ScrollMove;		//スクロールする向き
	glm::ivec2 mVector;			//向き



	//送信データ
	WriteData ChipData;	//書き込むデータ
	ConfigData Config;	//コンフィグ





	std::shared_ptr<Animation> anim;	//カーソルアニメーション

	std::vector<SpriteData> SpriteList;		//スプライトリスト
	std::vector<std::string> FileNameList;	//ファイル名リスト
	std::vector<std::string> StageFileNameList;

	std::string FileName;


	//　メニュー関係

	bool isChipSelect;	//マップチップを選択	
	bool isStageSelect;	//ステージを選択
	bool isChangeSize;	//ステージの大きさを変更
	



	std::shared_ptr<Window> Chip_Menu;	//チップ選択画面
	std::shared_ptr<Window> Stage_Menu;	//ステージ選択画面








	//長押し
	bool HoldKey_Y;
	bool HoldKey_X;
	
	Entry* Owner;	//Entryクラス
};


#endif