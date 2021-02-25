#include "Animation.hpp"

//�R���X�g���N�^
Animation::Animation(int c)
{
	Clip = 0;		//���݂̔ԍ�
	max_Clip = c;	//�ԍ��̐�
	nextFrame = 1;	//���̔ԍ��ɂȂ�t���[����
	first = false;	//�t���[�����Čv�Z���邩�ǂ����H
	isAnim = false;	//��񂾂��Đ��������ǂ����H
}


//�f�X�g���N�^
Animation::~Animation()
{

}

//�A�j���[�V���������[�v�Đ�
int Animation::getClip_loop(int speed)
{
	if (first == false)
	{
		nextFrame = Fps::getElapsed() + speed;//���̃N���b�v�̃t���[�����v�Z
		first = true;

//		return Clip;
	}
	
	
	if (Fps::getElapsed() == nextFrame) {

		Clip++;

		//�ő�N���b�v�𒴂�����
		if (Clip > max_Clip) 
		{
			Clip = 0;
		}

		first = false;
		return Clip;
	}
	else 
	{
		return Clip;
	}

}

//1�񂾂��擾
bool Animation::getClip(int& num, int speed)
{

	if (first == false)
	{
		nextFrame = Fps::getElapsed() + speed;//���̃N���b�v�̃t���[�����v�Z
		first = true;
	}


	if (Fps::getElapsed() >= nextFrame) {

		Clip++;

		//�ő�N���b�v�𒴂�����
		if (Clip > max_Clip)
		{
			Clip = 0;

			isAnim = true;
			first = false;
			return isAnim;
		}

		//printf("��������������\n");

		first = false;

		num = Clip;
		return isAnim;
	}
	else
	{
		//printf("����������\n");
		num = Clip;
		return isAnim;
	}

}













