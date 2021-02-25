#include "Actor.hpp"

//コンストラクタ
Actor::Actor(Entry* e,glm::ivec2 pos ,glm::ivec2 vec )
{
	mVector = vec;
	mPosition = pos;
	mSize = glm::ivec2(0,0);
	Owner = e;
}

//方向を取得
glm::ivec2 Actor::getVector()
{
	return mVector;
}

//座標を取得
glm::ivec2 Actor::getPosition()
{
	return mPosition;
}

//座標を取得
void Actor::setPosition(glm::ivec2 pos)
{
	mPosition = pos;
}




//デストラクタ
Actor::~Actor()
{

}
