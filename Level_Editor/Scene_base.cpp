#include "Scene_Base.hpp"


//コンストラクタ
Scene_base::Scene_base(Scene_Type t, Entry* e)
{
	Type = t;	//シーンにタイプを設定
	Owner = e;	//Entry クラス
}

//シーンタイプを取得
Scene_Type Scene_base::getSceneType()
{
	return Type;
}

//デストラクタ
Scene_base::~Scene_base()
{
	
}