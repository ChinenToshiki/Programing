#include "Charges.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "ResultScene.h"

#define SCREEN_WIDTH 640
#define SCREEN_HIGHT 480
#define Limit 3

Charges::Charges() :count(0), image(0), image_flg(false), once(false)
{
}
Charges::~Charges()
{
}

void Charges::Initialize()
{
	image = LoadGraph("Resource/images/charges02.png");
	image_flg = false;
	once = false;
}

void Charges::Update(int player_hp)
{
	//裁判上限を越した場合で画像表示(仮でHPを参照中)
	if (count >= Limit)
	{
		image_flg = true;
	}
	//ボタンが一回押されたのを判定
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && image_flg == true && once == false) {
		once = true;
	}
}

void Charges::Draw() const
{
	if (image_flg == true) 
	{
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HIGHT, GetColor(255,255,255), TRUE);
		//DrawString(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, "死刑", GetColor(255, 0, 0));
		DrawGraph(30, 0, image, FALSE);
	}
}

void Charges::Finalize()
{
	DeleteGraph(image);
}
