#include "GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), barrier_image(NULL), mileage(0), player(nullptr), enemy(nullptr)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Initialize()
{
	ReadHighScore();

	back_ground = LoadGraph  ("Resource/images/back.bmp");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);

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

	player = new Player;
	enemy = new Enemy * [10];

	player->Initialize();

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
}

eSceneType GameMainScene::Update()
{
	player->Update();

	mileage += (int)player->GetSpeed() + 5;

	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (enemy[i] == nullptr)
			{
				int type = GetRand(3) % 3;
				enemy[i] = new Enemy(type, enemy_image[type]);
				enemy[i]->Initialize();
				break;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(player->GetSpeed());

			if (enemy[i]->GetLocation().y >= 640.0f)
			{
				enemy_count[enemy[i]->GetType()]++;
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}

			if (IsHitCheck(player, enemy[i]))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}

void GameMainScene::Draw() const
{
	DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	player->Draw();

	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	SetFontSize(16);
	DrawFormatString(510, 20, GetColor(0, 0, 0), "ハイスコア");
	DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", high_score);
	DrawFormatString(510, 80, GetColor(0, 0, 0), "避けた数");
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
		DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d", enemy_count[i]);
	}
	DrawFormatString(510, 200, GetColor(0, 0, 0), "走行距離");
	DrawFormatString(555, 220, GetColor(255, 255, 255), "%08d", mileage / 10);
	DrawFormatString(510, 240, GetColor(0, 0, 0), "スピード");
	DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f",player->GetSpeed());

	for (int i = 0; i < player->GetBarrierCount(); i++)
	{
		DrawRotaGraph(520+ i*25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	}

	float fx = 510.0f;
	float fy = 390.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	fx = 510.0f;
	fy = 430.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy+40.0f, GetColor(0, 0, 0), FALSE);
}

void GameMainScene::Finalize()
{
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

	FILE* fp = nullptr;

	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	if (result != 0)
	{
		throw("Resource / dat / result_data.csvが開けません");
	}

	fprintf(fp, "%d\n", score);

	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	fclose(fp);

	player->Finallize();
	delete player;

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

eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initalize();

	high_score = data.GetScore(0);

	data.Finalize();
}

bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
	if (p->IsBarrier())
	{
		return false;
	}

	if (e == nullptr)
	{
		return false;
	}

	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}