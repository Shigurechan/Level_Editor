#ifndef ___FPS_HPP_
#define ___FPS_HPP_

#include <math.h>
#include "DxLib.h"


/*####################################################
* フレームレート制御
######################################################*/

class Fps {
	
public:
	Fps();
	bool Update();	//更新
	void Wait();	//待機
	
	static int getFrame();		//フレームを取得
	static int getElapsed();	//経過フレームを取得

private:
	int mStartTime;				//測定開始時刻
	static int mCount;			//カウンタ
	static int mStartCount;		//起動してからの経過フレーム
	float mFps;					//fps
	static const int N = 60;	//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

};
#endif