#ifndef ___GAME_SCENE_HPP_
#define ___GAME_SCENE_HPP_

#include "Scene_base.hpp"

#include "Entry.hpp"

class Stage;
enum class Scene_Type;
/*####################################################
* メインゲーム　シーン
*
* 説明
* メインのゲーム画面
######################################################*/
class Game_Scene : public Scene_base
{
public:
	Game_Scene(Scene_Type t,Entry* e);	//コンストラクタ
	~Game_Scene();						//デストラクタ

	void Update();	//更新
	void Draw();	//描画

private:



	std::shared_ptr<Stage> stage;

	Entry* Owner;	//Entry クラス

};

#endif
