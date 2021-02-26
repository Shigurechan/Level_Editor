#ifndef ___STARTMENU_HPP
#define ___STARTMENU_HPP

#include "Scene_base.hpp"
class Window;
enum class Window_Scene;
/*####################################################
* ���[�h���j���[
*
* ����
* 
* �ŏ��̉��
* �t�@�C����ǂݍ��ނ�����Ƃ��V�K�쐬����I��������
######################################################*/
enum class Scene_Type;
class Entry;
class StartMenu : public Scene_base
{
public:
	StartMenu(Scene_Type t, Entry* e);	//�R���X�^���N�^
	~StartMenu();						//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��

private:

	
	std::shared_ptr<Window> menu;

	Window_Scene type;


};

#endif

