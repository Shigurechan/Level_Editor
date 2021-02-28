#ifndef ___STARTMENU_HPP
#define ___STARTMENU_HPP

#include "Scene_base.hpp"
#include "Entry.hpp"

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

	EditData getData();	//�t�@�C������Ԃ�

	bool changeScene;	//�V�[����؂�ւ���
private:
	int KeyHandle;	//�L�[���̓n���h��
	char FileName[256] = { '\0' };	//���͂����t�@�C����

	
	std::shared_ptr<Window> menu;				//���C���V�[��
	std::shared_ptr<Window> NewFile_menu;		//�V�K�쐬�Ńt�@�C�������̓V�[��
	std::shared_ptr<Window> EditFile_menu;		//�ҏW����t�@�C�������̓V�[��
	std::shared_ptr<Window> CheckFile_menu;		//�V�K�쐬�Ńt�@�C�������邩�ǂ����m�F�V�[��



	Window_Scene type;

	EditData data;	//�G�f�B�b�g���e���G�f�B�^�[�ɓ`����
	byte Mode;
	bool CheckFile(const char* FileName);

};

#endif