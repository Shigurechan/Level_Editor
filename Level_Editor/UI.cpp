#include "UI.hpp"

//��`�̍��W���T�C�Y��ݒ�
void GetRectangleData(RectangleData& data, glm::ivec2 pos, glm::ivec2 size)
{
	data.pos = glm::ivec2(pos.x - size.x, pos.y - size.y);	//���W
	data.size = glm::ivec2(pos.x + size.x, pos.y + size.y);	//�T�C�Y
}
