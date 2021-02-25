#ifndef ___FPS_HPP_
#define ___FPS_HPP_

#include <math.h>
#include "DxLib.h"


/*####################################################
* �t���[�����[�g����
######################################################*/

class Fps {
	
public:
	Fps();
	bool Update();	//�X�V
	void Wait();	//�ҋ@
	
	static int getFrame();		//�t���[�����擾
	static int getElapsed();	//�o�߃t���[�����擾

private:
	int mStartTime;				//����J�n����
	static int mCount;			//�J�E���^
	static int mStartCount;		//�N�����Ă���̌o�߃t���[��
	float mFps;					//fps
	static const int N = 60;	//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS

};
#endif