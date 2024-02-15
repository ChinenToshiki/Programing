#include "Charges.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "ResultScene.h"

// 画面サイズの定義
#define SCREEN_WIDTH 640
#define SCREEN_HIGHT 480

// 裁判の上限
#define Limit 5	

// クールタイムの設定（フレーム数）
#define COOLTIME 300

Charges::Charges() :fps(0), type(0), count(0), trial_count(0),get_rand(NULL), image_flg(false), fps_flg(false), once(false)
{
	for (int i = 0; i < 3; i++) {
		image[i] = NULL;
	}
}
Charges::~Charges()
{
}

void Charges::Initialize()
{
	image[0] = LoadGraph("Resource/images/charges02.png");
	image[1] = LoadGraph("Resource/images/リムジン死刑.png");
	image[2] = LoadGraph("Resource/images/Death.png");
	fps = COOLTIME;
	count = 0;
	trial_count = 0;
	image_flg = false;
	once = false;
	fps_flg = false;
}

void Charges::Update()
{
	//裁判上限を越した場合で画像表示
	if (trial_count >= Limit)
	{
		image_flg = true;
		fps_flg = false;
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
		if (get_rand == 1) {
			DrawGraph(30, 0, image[0], FALSE);
		}
		else
		{
			DrawGraph(30, 0, image[2], FALSE);
		}
	}
	if (type == 3 && get_rand == 1) {
		DrawGraph(460, 0, image[1], FALSE);
	}
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", fps);
}

void Charges::Finalize()
{
	for (int i = 0; i < 3; i++) {
		DeleteGraph(image[i]);
	}
}

void Charges::HitCount()
{
	// クールタイム開始と裁判のカウントを増加
	count += 1;
	fps_flg = true;
	trial_count += 1;
}

void Charges::SetType(int _type)
{
	type = _type;
}
//確率で即死
int Charges::Rand()
{
	int rand = GetRand(99);
	//5%で事故死
	if (rand >= 0 && rand <= 4) {
		get_rand = 0;
		image_flg = true;
		//fps_flg = false;
	}
	//
	else {
		get_rand = 1;
	}
	return get_rand;
}
