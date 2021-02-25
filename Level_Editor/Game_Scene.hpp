#ifndef ___GAME_SCENE_HPP_
#define ___GAME_SCENE_HPP_

#include "Scene_base.hpp"

#include "Entry.hpp"

class Stage;
enum class Scene_Type;
/*####################################################
* ���C���Q�[���@�V�[��
*
* ����
* ���C���̃Q�[�����
######################################################*/
class Game_Scene : public Scene_base
{
public:
	Game_Scene(Scene_Type t,Entry* e);	//�R���X�g���N�^
	~Game_Scene();						//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��

private:



	std::shared_ptr<Stage> stage;

	Entry* Owner;	//Entry �N���X

};

#endif
