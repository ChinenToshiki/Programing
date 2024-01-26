#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene:: ~HelpScene()
{

}

void HelpScene::Initialize()
{
	background_image = LoadGraph("Resource/images/Title.bmp");

	if (background_image = -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
}

eSceneType HelpScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

void HelpScene::Draw() const
{
	DrawGraph(0, 0, background_image, FALSE);

	SetFontSize(16);
	DrawString(20, 120, "�w���v���",0xffffff,0);

	DrawString(20, 160, "����͏�Q��������Ȃ���", 0xffffff, 0);
	DrawString(20, 180, "���葱����Q�[���ł�", 0xffffff, 0);
	DrawString(20, 200, "�R�����s���邩��Q����", 0xffffff, 0);
	DrawString(20, 220, "���񓖂���ƃQ�[���I�[�o�[�ł��B", 0xffffff, 0);

	DrawString(20, 450, "----�@B�{�^���������ă^�C�g���ɖ߂�@----", 0xffffff, 0);
}

void HelpScene::Finalize()
{
	DeleteGraph(background_image);
}

eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}