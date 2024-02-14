#include "Charges.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "ResultScene.h"

// ��ʃT�C�Y�̒�`
#define SCREEN_WIDTH 640
#define SCREEN_HIGHT 480

// �ٔ��̏��
#define Limit 15	

// �N�[���^�C���̐ݒ�i�t���[�����j
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
	// �N�[���_�E������
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
	//�ٔ�������z�����ꍇ�ŉ摜�\��
	if (judgment_count >= Limit)
	{
		image_flg = true;
	}
	//�{�^������񉟂��ꂽ�̂𔻒�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && image_flg == true && once == false) {
		once = true;
	}
}

void Charges::Draw() const
{
	if (image_flg == true) 
	{
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HIGHT, GetColor(255,255,255), TRUE);
		//DrawString(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, "���Y", GetColor(255, 0, 0));
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
	// �N�[���^�C���J�n�ƍٔ��̃J�E���g�𑝉�
	count += 1;
	fps_flg = true;
	judgment_count += 1;
}
