#include "MapChip.hpp"
#include "Entry.hpp"

//�R���X�g���N�^
MapChip::MapChip() : Actor(nullptr)
{
	sprite = 0;			//�X�v���C�g
	binary = 0;			//�o�C�i��

}

// �ݒ�@�֌W

//�o�C�i��
void MapChip::setBinary(byte b)
{
	binary = b;
	//printf("%x\n",binary);
}

//�X�v���C�g
void MapChip::setSprite(int sp)
{
	sprite = sp;
}

// �擾�@�֌W

//�o�C�i��
byte MapChip::getBinary()
{
	return binary;
}

//�X�v���C�g
int MapChip::getSprite()
{
	return sprite;
}

//�X�V
void MapChip::Update()
{

}

//�`��
void MapChip::Draw()
{
	DrawRotaGraph(mPosition.x + CELL / 2,mPosition.y + CELL / 2,1.0,0,sprite,false);
}



//�f�X�g���N�^
MapChip::~MapChip()
{

}

