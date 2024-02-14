#include "Charges.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "ResultScene.h"

// 画面サイズの定義
#define SCREEN_WIDTH 640
#define SCREEN_HIGHT 480

// 裁判の上限
#define Limit 15	

// クールタイムの設定（フレーム数）
#define COOLTIME 300

Charges::Charges() :fps(0),count(0),judgment_count(0), image(0), image_flg(false), fps_flg(false), once(false)
{
}
Charges::~Charges()
{
}

void Charges::Initialize()
{
	image = LoadGraph("Resource/images/charges02.png");
	fps = COOLTIME;
	count = 0;
	judgment_count = 0;
	image_flg = false;
	once = false;
	fps_flg = false;
}

void Charges::Update()
{
	// クールダウン処理
	if (fps_flg == true) {
		if (fps > 0) {
			fps--;
		}
		else if (fps == 0) {
			fps = COOLTIME;
			count = 0;
			fps_flg = false;
		}
	}
	if (fps_flg && count != 1) {
		image_flg = true;
	}
	//裁判上限を越した場合で画像表示
	if (judgment_count >= Limit)
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
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", fps);
}

void Charges::Finalize()
{
	DeleteGraph(image);
}

void Charges::HitCount()
{
	// クールタイム開始と裁判のカウントを増加
	count += 1;
	fps_flg = true;
	judgment_count += 1;
}
