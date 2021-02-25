#include "Fps.hpp"

int Fps::mCount = 0;
int Fps::mStartCount = 0;

//�R���X�g���N�^
Fps::Fps() {
	mStartTime = 0;
	mCount = 0;
	mFps = 0;
}

//�X�V
bool Fps::Update() {
	mStartCount++;
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

//���݂̃t���[�����擾
int Fps::getFrame() {
	return mCount;
}

//�o�߃t���[�����擾
int Fps::getElapsed()
{
	return mStartCount;
}



//�ҋ@
void Fps::Wait() {
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {

		Sleep(waitTime);	//�ҋ@
	}

	//�o�߃t���[��
	if (mStartCount > 60000) {
		mStartCount = 0;
	}
}