#include "UI.hpp"

//矩形の座標をサイズを設定
void GetRectangleData(RectangleData& data, glm::ivec2 pos, glm::ivec2 size)
{
	data.pos = glm::ivec2(pos.x - size.x, pos.y - size.y);	//座標
	data.size = glm::ivec2(pos.x + size.x, pos.y + size.y);	//サイズ
}
