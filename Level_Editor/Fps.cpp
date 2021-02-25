#include "Fps.hpp"

int Fps::mCount = 0;
int Fps::mStartCount = 0;

//コンストラクタ
Fps::Fps() {
	mStartTime = 0;
	mCount = 0;
	mFps = 0;
}

//更新
bool Fps::Update() {
	mStartCount++;
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

//現在のフレームを取得
int Fps::getFrame() {
	return mCount;
}

//経過フレームを取得
int Fps::getElapsed()
{
	return mStartCount;
}



//待機
void Fps::Wait() {
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {

		Sleep(waitTime);	//待機
	}

	//経過フレーム
	if (mStartCount > 60000) {
		mStartCount = 0;
	}
}