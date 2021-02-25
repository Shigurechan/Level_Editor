#include "Animation.hpp"

//コンストラクタ
Animation::Animation(int c)
{
	Clip = 0;		//現在の番号
	max_Clip = c;	//番号の数
	nextFrame = 1;	//次の番号になるフレーム数
	first = false;	//フレームを再計算するかどうか？
	isAnim = false;	//一回だけ再生したかどうか？
}


//デストラクタ
Animation::~Animation()
{

}

//アニメーションをループ再生
int Animation::getClip_loop(int speed)
{
	if (first == false)
	{
		nextFrame = Fps::getElapsed() + speed;//次のクリップのフレームを計算
		first = true;

//		return Clip;
	}
	
	
	if (Fps::getElapsed() == nextFrame) {

		Clip++;

		//最大クリップを超えた時
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

//1回だけ取得
bool Animation::getClip(int& num, int speed)
{

	if (first == false)
	{
		nextFrame = Fps::getElapsed() + speed;//次のクリップのフレームを計算
		first = true;
	}


	if (Fps::getElapsed() >= nextFrame) {

		Clip++;

		//最大クリップを超えた時
		if (Clip > max_Clip)
		{
			Clip = 0;

			isAnim = true;
			first = false;
			return isAnim;
		}

		//printf("いいいいいいい\n");

		first = false;

		num = Clip;
		return isAnim;
	}
	else
	{
		//printf("あああああ\n");
		num = Clip;
		return isAnim;
	}

}













