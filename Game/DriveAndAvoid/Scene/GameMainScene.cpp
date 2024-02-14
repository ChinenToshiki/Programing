#include "GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), barrier_image(NULL), mileage(0), player(nullptr), enemy(nullptr),charges(nullptr)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	//高得点を読み込む
	ReadHighScore();

	//画像の読み込み
	back_ground = LoadGraph  ("Resource/images/back.bmp");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);
	enemy_image[3] = LoadGraph("Resource/images/limousine.png");
	//enemy_count[3] = 0;
	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmpがありません\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.pngがありません\n");
	}

	//オブジェクトの生成
	player = new Player;
	enemy = new Enemy * [10];
	charges = new Charges;

	//オブジェクトの初期化
	player->Initialize();
	charges->Initialize();

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
}

//更新処理
eSceneType GameMainScene::Update()
{
	//プレイヤーの更新
	player->Update();

	charges->Update();

	//移動距離の更新
	mileage += (int)player->GetSpeed() + 5;

	//敵生成処理
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (enemy[i] == nullptr)
			{
				int type = GetRand(4) % 4;
				enemy[i] = new Enemy(type, enemy_image[type]);
				enemy[i]->Initialize();
				break;
			}
		}
	}

	//敵の更新と当たり判定チェック
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(player->GetSpeed());

			//画面外に言ったら、敵を消去してスコア加算
			if (enemy[i]->GetLocation().y >= 640.0f)
			{
				enemy_count[enemy[i]->GetType()]++;
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}

			//当たり判定の確認
			if (IsHitCheck(player, enemy[i]))
			{
				//リムジンじゃなかったら
				if (enemy[i]->GetType() != 3) {
					charges->HitCount();//裁判回数加算
				}
				//リムジンだったら即死刑
				else {
					charges->SetChargesFlg(true);
				}	
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}
	//死刑判決描画中にボタンが押されてたらリザルトへ
	if (charges->GetOnce()) {
		return eSceneType::E_RESULT;
	}
	//プレイヤーの燃料or体力が0未満ならリザルトへ飛ぶ
	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	//死刑判決描画
	if (charges->GetChargesFlg()) {
		charges->Draw();
		return;
	}
	//背景描画
	DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);

	//敵の描画
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}
	//プレイヤーの描画
	player->Draw();

	//UIの描画
	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	SetFontSize(16);
	DrawFormatString(510, 20, GetColor(0, 0, 0), "ハイスコア");
	DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", high_score);
	DrawFormatString(510, 80, GetColor(0, 0, 0), "避けた数");

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (i != 3) {
			DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
			DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d", enemy_count[i]);
		}
		else {
			DrawRotaGraph(523, 190, 0.2, 0, enemy_image[3], FALSE, FALSE);
			DrawFormatString(510, 215, GetColor(255, 255, 255), "%03d", enemy_count[3]);
		}
	}

	DrawFormatString(510, 230, GetColor(0, 0, 0), "走行距離");
	DrawFormatString(555, 250, GetColor(255, 255, 255), "%08d", mileage / 10);
	DrawFormatString(510, 270, GetColor(0, 0, 0), "スピード");
	DrawFormatString(555, 290, GetColor(255, 255, 255), "%08.1f",player->GetSpeed());

	//バリア枚数の描画
	for (int i = 0; i < player->GetBarrierCount(); i++)
	{
		DrawRotaGraph(520+ i*25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	}

	//燃料ゲージの描画
	float fx = 510.0f;
	float fy = 390.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	//体力ゲージの描画
	fx = 510.0f;
	fy = 430.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy+40.0f, GetColor(0, 0, 0), FALSE);
}

//終了時処理
void GameMainScene::Finalize()
{
	if (charges->GetChargesFlg()) {
		mileage = 0;
		for (int i = 0; i < ENEMY_NUM; i++) {
			enemy_count[i] = 0;
		}
	}

	//スコア計算
	int score = (mileage / 10 * 10);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

	//リザルトデータの書き込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//ファイルオープンエラーチェック
	if (result != 0)
	{
		throw("Resource / dat / result_data.csvが開けません");
	}

	//スコアの保存
	fprintf(fp, "%d\n", score);

	//避けた数と得点の保存
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	//ファイルクローズ
	fclose(fp);

	//動的確保したオブジェクトを削除する
	player->Finallize();
	delete player;

	charges->Finalize();
	delete charges;

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
	delete[] enemy;
}

//現在のシーンを取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//ハイスコアの読み込み
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initalize();

	high_score = data.GetScore(0);

	data.Finalize();
}

//当たり判定処理(プレイヤーとエネミー)
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
	//プレイヤーがバリアを張っていたら判定無視
	if (p->IsBarrier())
	{
		return false;
	}

	//敵がいなければ判定無視
	if (e == nullptr)
	{
		return false;
	}

	//当たり判定の差分を取得
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//当たり判定のサイズを取得
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	//コリジョンデータより位置情報の差分が小さいならヒット
	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}