#ifndef ___MAPCHIP_HPP_
#define ___MAPCHIP_HPP_

#include "Actor.hpp"
#include "glm/glm.hpp"
class MapChip;
/*####################################################
* マップチップ
*
* 説明
* 
* バイナリ
* スプライト
* 座標
* を格納
######################################################*/

class MapChip : public Actor
{
public:
	MapChip();	//コンストラクタ
	~MapChip();	//デストラクタ

	void Update();	//更新
	void Draw();	//描画


	// 設定　関係
	void setBinary(byte b);	//バイナリ
	void setSprite(int sp);	//スプライト


	//取得　関係
	byte getBinary();	//バイナリ
	int getSprite();	//スプライト



private:

	byte binary;	//バイナリ
	int sprite;		//スプライト



};




#endif