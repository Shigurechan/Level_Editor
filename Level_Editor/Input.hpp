#ifndef ___INPUT_HPP_
#define ___INPUT_HPP_

#include "dxlib.h"


/*#################################################### 
* キー入力
* 
* 説明
* 必ずvoid Update();関数をUpdate()関数に入れる。そうしないと動かない！
######################################################*/

class Input {

public:
	Input();	//コンストラクタ
	~Input();	//デストラクタ
	
	void Update();								//キー入力状態を更新

	bool getKeyDown(unsigned char KeyCode);		//キーが押された瞬間だけ
	int  getKeyDownHold(unsigned char KeyCode);	//キーが押されている間

private:
	unsigned int Key[256];	//キー状態

};



#endif
