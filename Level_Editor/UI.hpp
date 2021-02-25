#ifndef ___UI_HPP_
#define ___UI_HPP_

#include "glm/glm.hpp"
#include "dxlib.h"




//ウインドウの情報
typedef struct RectangleData
{
	glm::ivec2 pos;		//座標
	glm::ivec2 size;	//サイズ
}RectangleData;

void GetRectangleData(RectangleData& data, glm::ivec2 pos, glm::ivec2 size);	//矩形サイズを設定


/*####################################################
* ユーザーインターフェイス
*
* 説明
* プレイ画面のUI　未完成
######################################################*/

class UI
{
public:
	UI(glm::ivec2 pos = glm::ivec2(0, 0), glm::ivec2 vec = glm::ivec2(0, 0));	//コンストラクタ
	~UI();	//デストラクタ

	void virtual Update() = 0;	//計算
	void virtual Draw() = 0;	//描画

	//取得関係
	glm::ivec2 getVector();		//方向
	glm::ivec2 getPosition();	//座標
protected:

	glm::ivec2 mPosition;	//座標
	glm::ivec2 mVector;		//方向
	glm::ivec2 mSize;		//スプライトのサイズ


};


#endif
