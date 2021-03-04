#ifndef ___STARTMENU_HPP
#define ___STARTMENU_HPP

#include "Scene_base.hpp"
#include "Entry.hpp"

/*####################################################
* ���[�h���j���[
*
* ����
* 
* �ŏ��̉��
* �t�@�C����ǂݍ��ނ�����Ƃ��V�K�쐬����I��������
######################################################*/

enum class Scene_Type;
enum class Window_Scene;
class Entry;
class Window;

class StartMenu : public Scene_base
{
public:
	StartMenu(Scene_Type t, Entry* e);	//�R���X�^���N�^
	~StartMenu();						//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��

	EditData getEditData();	//�t�@�C������Ԃ�

	bool changeScene;	//�V�[����؂�ւ���
private:
	
	std::shared_ptr<Window> Main_menu;				//���C���V�[��
	std::shared_ptr<Window> NewFile_menu;		//�V�K�쐬�Ńt�@�C�������̓V�[��
	std::shared_ptr<Window> EditFile_menu;		//�ҏW����t�@�C�������̓V�[��
	std::shared_ptr<Window> CheckFile_menu;		//�V�K�쐬�Ńt�@�C�������邩�ǂ����m�F�V�[��
	
	std::shared_ptr<Window> SizeSet_menu;		//�V�K�쐬�ŃX�e�[�W�T�C�Y��ݒ肷��V�[��
	std::shared_ptr<Window> SizeSetError_menu;		//�T�C�Y��ݒ肵�Ȃ����̕\��

	std::shared_ptr<Window> CheckFileError_menu;		//�t�@�C�������݂��Ȃ����̃E�C���h�E




	std::shared_ptr<Window> test_menu;	//�e�X�g�p








	Window_Scene mNowScene;	//���݂̃E�C���h�E�V�[������

	EditData data;	//�G�f�B�b�g���e���G�f�B�^�[�ɓ`����
	byte Mode;		//���[�h
	bool CheckFile(const char* FileName);	//�t�@�C�������݂��邩�ǂ����H
	char FileName[INPUT_KEY_NUMBER_MAX] = { '\0' };
};

#endif