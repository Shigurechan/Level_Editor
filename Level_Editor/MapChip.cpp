#include "MapChip.hpp"
#include "Entry.hpp"

//コンストラクタ
MapChip::MapChip() : Actor(nullptr)
{
	sprite = 0;			//スプライト
	binary = 0;			//バイナリ

}

// 設定　関係

//バイナリ
void MapChip::setBinary(byte b)
{
	binary = b;
	//printf("%x\n",binary);
}

//スプライト
void MapChip::setSprite(int sp)
{
	sprite = sp;
}

// 取得　関係

//バイナリ
byte MapChip::getBinary()
{
	return binary;
}

//スプライト
int MapChip::getSprite()
{
	return sprite;
}

//更新
void MapChip::Update()
{

}

//描画
void MapChip::Draw()
{
	DrawRotaGraph(mPosition.x + CELL / 2,mPosition.y + CELL / 2,1.0,0,sprite,false);
}



//デストラクタ
MapChip::~MapChip()
{

}

