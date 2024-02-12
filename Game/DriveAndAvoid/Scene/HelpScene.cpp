#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene:: ~HelpScene()
{

}

//����������
void HelpScene::Initialize()
{								
	background_image = LoadGraph("Resource/images/Title.bmp");

	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
}

//�X�V����
eSceneType HelpScene::Update()
{
	//B�{�^���������ꂽ��^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//�`�揈��
void HelpScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(16);
	DrawString(20, 120, "�w���v���",0xffffff,0);

	DrawString(20, 160, "----�@������@�@----",0xffffff,0);
	DrawString(20, 180, "�\���L�[�ŎԁE�L�[���ړ�", 0xffffff, 0);
	DrawString(20, 200, "B�{�^���Ńo���A/����", 0xffffff, 0);
	DrawString(20, 220, "RB�{�^���ŃM�A���グ��@LB�{�^���ŃM�A��������", 0xffffff, 0);
	DrawString(20, 240, "����͏�Q��������Ȃ���", 0xffffff, 0);
	DrawString(20, 260, "���葱����Q�[���ł�", 0xffffff, 0);
	DrawString(20, 280, "�R�����s���邩��Q����", 0xffffff, 0);
	DrawString(20, 300, "������x�ɍٔ����N����A�I����������܂��B", 0xffffff, 0);
	DrawString(20, 320, "�ٔ��ɏ��ĂΔR���Ƒ̗͂��񕜂���\n�ٔ��ɔs�k����ΔR���Ƒ̗͂��������܂��B", 0xffffff, 0);
	DrawString(20, 360, "���񐔈ȏ��Q���ɓ�����Ƒ����Y�ɂȂ�̂�\n�C��t���܂��傤", 0xffffff, 0);
	DrawString(20, 450, "----�@B�{�^���������ă^�C�g���ɖ߂�@----", 0xffffff, 0);
}

//�I��������
void HelpScene::Finalize()
{
	DeleteGraph(background_image);
}

//���݂̃V�[�����擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}