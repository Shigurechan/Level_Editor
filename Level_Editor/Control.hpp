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
	Control(Entry* e, std::vector<SpriteData> sprite);	//コンストラクタ
	~Control();									//デストラクタ

	void Update();	//更新
	void Draw();	//描画


	// ##### 設定
	void setPos(glm::ivec2 size);	//カーソル座標
	void setGridPos(glm::ivec2 g);	//グリッド座標を設定
	void setScreenGridPos(glm::ivec2 p);	//スクリーンのグリッド座標を取得


	// ##### 取得　
	MapChip getChip();				//マップチップ
	glm::ivec2 getGridPos();		//グリッド座標を取得
	glm::ivec2 getVector();			//向き
	glm::ivec2 getScreenGridPos();	//スクリーンのグリッド座標を取得



	bool isWrite_cell;	//書き込むかどうか？
	bool isWrite_File;	//ステージ情報をバイナリファイルに書き込むかどうか？
private:

	void MenuUpdate();	//更新
	void MenuDraw();	//描画

	glm::ivec2 Screen_GridPos;	//画面上のグリッド座標
	glm::ivec2 GridPos;			//ステージのグリッド座標

	glm::ivec2 ScrollMove;	//スクロールする向き
	glm::ivec2 mVector;		//向き

	MapChip chip;	//書き込む情報

	std::shared_ptr<Animation> anim;	//カーソルアニメーション

	std::vector<SpriteData> SpriteList;	//スプライト情報リスト



	//　メニュー関係
	bool isMenu = false;	//メニュー画面かどうか？
	std::shared_ptr<Window> menu;	//メニューウインドウ








	//長押し
	bool HoldKey_Y;
	bool HoldKey_X;
	
	Entry* Owner;	//Entryクラス
};


#endif