#ifndef ___ACTOR_HPP_
#define ___ACTOR_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"

class Entry;

/*####################################################
* アクター
* 
* 説明
* 全てのゲームオブジェクトはこれを継承する。
######################################################*/

class Actor
{
public:
	Actor(Entry* e,glm::ivec2 pos = glm::ivec2(0, 0), glm::ivec2 vec = glm::ivec2(0, 0));	//コンストラクタ
	~Actor();	//デストラクタ

	void virtual Update() = 0;	//計算
	void virtual Draw() = 0;	//描画

	//取得　関係
	glm::ivec2 getVector();		//方向
	glm::ivec2 getPosition();	//座標

	//設定　関係
	void setPosition(glm::ivec2 pos);

protected:

	glm::ivec2 mPosition;	//座標
	glm::ivec2 mVector;		//方向
	glm::ivec2 mSize;		//スプライトのサイズ

	Entry* Owner;			//Entry クラス

};


#endif
