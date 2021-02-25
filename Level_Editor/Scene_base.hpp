#ifndef ___SCENE_BASE_HPP_
#define ___SCENE_BASE_HPP_

#include <iostream>
#include <vector>

class Entry;
enum class Scene_Type;

/*####################################################
* シーンの基底クラス
* 
* 説明
* 全てのシーンクラスはこのクラスを継承する。
######################################################*/
class Scene_base
{
public:
	Scene_base(Scene_Type t,Entry* e);	//コンストラクタ
	~Scene_base();						//デストラクタ

	virtual void Update() = 0;	//更新
	virtual void Draw() = 0;	//描画

	Scene_Type getSceneType();	//シーンタイプを取得
protected:

	Scene_Type Type;	//シーンタイプ
	Entry* Owner;		//Entry クラス

};


#endif
