#include "Input.hpp"

// コンストラクタ
Input::Input()
{
    //キー状態配列を初期化
    for (int i = 0; i < 256; i++)
    {
        Key[i] = 0;
    }
}

//キー入力状態を更新
void Input::Update()
{    
    char tmpKey[256] = { 0 };           // 現在のキーの入力状態を格納する
    GetHitKeyStateAll(tmpKey);          // 全てのキーの入力状態を得る
    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) {           // i番のキーコードに対応するキーが押されていたら
            Key[i]++;                   // 加算
        }
        else {

            // 押されていなければ
            Key[i] = 0;   // 0にする
        }
    } 
}

//キーを押した時だけ
bool Input::getKeyDown(unsigned char KeyCode)
{
    if (Key[KeyCode] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//キーを押している時
int Input::getKeyDownHold(unsigned char KeyCode)
{

    return Key[KeyCode];
}

//　デストラクタ
Input::~Input()
{

}

