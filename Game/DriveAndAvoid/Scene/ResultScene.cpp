#include"ResultScene.h"
#include"../Object/RankingData.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

ResultScene::ResultScene() : back_ground(NULL), score(0)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

ResultScene::~ResultScene()
{

}

//初期化処理
void ResultScene::Initialize()
{
	//画像の読み込み
	back_ground = LoadGraph("Resource/images/back.bmp");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);
	enemy_image[3] = LoadGraph("Resource/images/limousine.png");

	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (result == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}

	//ゲーム結果の読み込み
	ReadResultData();
}

//更新処理
eSceneType ResultScene::Update()
{
	//Bボタンでランキングに飛ぶ
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		if (score != 0)
		{
			return eSceneType::E_RANKING_INPUT;
		}
		else
		{
			return eSceneType::E_TITLE;
		}
	}
	return GetNowScene();
}

//描画処理
void ResultScene::Draw() const
{
	//背景の描画
	DrawGraph(0, 0, back_ground, TRUE);
	GameMainScene JudgeThrow;
	int Judge = JudgeThrow.GetTiarl();
	
	//スコア等表示領域
	DrawBox(150, 150, 490, 400, GetColor(0, 153, 0), TRUE);
	DrawBox(150, 150, 490, 400, GetColor(0, 0, 0), FALSE);

	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);

	SetFontSize(20);
	DrawString(220, 170, "ゲームオーバー", GetColor(204, 0, 0));
	SetFontSize(16);
	DrawString(180, 200, "走行距離       ", GetColor(0, 0, 0));
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (i == 3) {
			DrawRotaGraph(220, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[3], FALSE);
		}
		else {
			DrawRotaGraph(230, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[i], TRUE);
		}
		DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x %4d=%6d",
		enemy_count[i], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);
	}
	DrawString(180, 320, "スコア", GetColor(0, 0, 0));

	DrawFormatString(180, 320, 0xFFFFFFF, "        =%6d", score);

	//裁判の数
	DrawFormatString(180, 340, GetColor(0, 0, 0), "裁判の結果:\n起きた裁判の数:%2d正解した数:%2d", Judge);
	
	//裁判の数とスコアが０じゃないで場合分け
	if(Judge ==0&&score!=0)
	 {
		DrawFormatString(180, 380, GetColor(0, 0, 0), "\t*****【ゴールド免許】*****");
	 }
	else if(Judge <3 && score != 0)
	{
		DrawFormatString(180, 380, GetColor(0, 0, 0), "\t*****【プチゴールド免許】*****");
	}
	else if(Judge <7 && score != 0)
	{
	 DrawFormatString(180, 380, GetColor(0, 0, 0), "\t*****【シルバー免許】*****");
	 }
	 else if(Judge <10 && score != 0)
	 {	 
		DrawFormatString(180, 380, GetColor(0, 0, 0), "\t*****【ブロンズ免許】*****");
	 }
	 else if(Judge <14 && score != 0)
	 {	
		DrawFormatString(180, 380, GetColor(0, 0, 0), "\t*****【免許停止】*****");
	}
	 else 
	{
		//リムジンにぶつかった時用
		DrawFormatString(180, 380, GetColor(0, 0, 0), "\t*****【さようなら】*****");
	}
}
//終了時処理
void ResultScene::Finalize()
{
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}
}

//現在のシーン情報を取得
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

//リザルトデータの読み込み
void ResultScene::ReadResultData()
{
	//ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが読み込めません\n");
	}

	//結果を読み込む
	fscanf_s(fp, "%6d,\n", &score);

	//避けた数と得点を取得
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		fscanf_s(fp, "%6d,\n", &enemy_count[i]);
	}
	fclose(fp);
}