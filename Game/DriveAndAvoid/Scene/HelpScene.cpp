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
		throw("Resource/images/Title.bmpがありません\n");
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
	DrawString(20, 120, "ヘルプ画面",0xffffff,0);

	DrawString(20, 160, "これは障害物を避けながら", 0xffffff, 0);
	DrawString(20, 180, "走り続けるゲームです", 0xffffff, 0);
	DrawString(20, 200, "燃料が尽きるか障害物に", 0xffffff, 0);
	DrawString(20, 220, "数回当たるとゲームオーバーです。", 0xffffff, 0);

	DrawString(20, 450, "----　Bボタンを押してタイトルに戻る　----", 0xffffff, 0);
}

void HelpScene::Finalize()
{
	DeleteGraph(background_image);
}

eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}