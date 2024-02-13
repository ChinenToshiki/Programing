#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene:: ~HelpScene()
{

}

//初期化処理
void HelpScene::Initialize()
{								
	background_image = LoadGraph("Resource/images/Title.bmp");

	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
}

//更新処理
eSceneType HelpScene::Update()
{
	//Bボタンが押されたらタイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//描画処理
void HelpScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(16);
	DrawString(20, 120, "ヘルプ画面",0xffffff,0);

	DrawString(20, 160, "----　操作方法　----",0xffffff,0);
	DrawString(20, 180, "十字キーで車・キーを移動", 0xffffff, 0);
	DrawString(20, 200, "Bボタンでバリア/決定", 0xffffff, 0);
	DrawString(20, 220, "RBボタンでギアを上げる　LBボタンでギアを下げる", 0xffffff, 0);
	DrawString(20, 240, "これは障害物を避けながら", 0xffffff, 0);
	DrawString(20, 260, "走り続けるゲームです", 0xffffff, 0);
	DrawString(20, 280, "燃料が尽きるか障害物に", 0xffffff, 0);
	DrawString(20, 300, "当たる度に裁判が起こり、選択肢が現れます。", 0xffffff, 0);
	DrawString(20, 320, "裁判に勝てば燃料と体力が回復して\n裁判に敗北すれば燃料と体力が減少します。", 0xffffff, 0);
	DrawString(20, 360, "一定回数以上障害物に当たると即死刑になるので\n気を付けましょう", 0xffffff, 0);
	DrawString(20, 450, "----　Bボタンを押してタイトルに戻る　----", 0xffffff, 0);
}

//終了時処理
void HelpScene::Finalize()
{
	DeleteGraph(background_image);
}

//現在のシーンを取得
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}