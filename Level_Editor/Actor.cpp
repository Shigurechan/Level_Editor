#include "Actor.hpp"

//�R���X�g���N�^
Actor::Actor(Entry* e,glm::ivec2 pos ,glm::ivec2 vec )
{
	mVector = vec;
	mPosition = pos;
	mSize = glm::ivec2(0,0);
	Owner = e;
}

//�������擾
glm::ivec2 Actor::getVector()
{
	return mVector;
}

//���W���擾
glm::ivec2 Actor::getPosition()
{
	return mPosition;
}

//���W���擾
void Actor::setPosition(glm::ivec2 pos)
{
	mPosition = pos;
}




//�f�X�g���N�^
Actor::~Actor()
{

}
