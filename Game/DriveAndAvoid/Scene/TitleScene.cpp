#include"TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), menu_image(NULL), cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	background_image = LoadGraph("Resource/images/title.bmp");
	menu_image = LoadGraph("Resource/images/menu.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	if (background_image == -1)
	{
		throw("Resource/images/title.bmp‚ª‚ ‚è‚Ü‚¹‚ñ");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmp‚ª‚ ‚è‚Ü‚¹‚ñ");
	}	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp‚ª‚ ‚è‚Ü‚¹‚ñ");
	}
}

eSceneType TitleScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}


	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_RANKING_DISP;
		case 2:
			return eSceneType::E_HELP;
		default:
			return eSceneType::E_END;
		}
	}
	return GetNowScene();
}

void TitleScene::Draw() const
{
	DrawGraph(0, 0, background_image, FALSE);

	DrawGraph(120, 200, menu_image, TRUE);

	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}

void TitleScene::Finalize()
{
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}