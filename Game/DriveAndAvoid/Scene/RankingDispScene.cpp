#include"RankingDispScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

RankingDispScene::RankingDispScene() : background_image(NULL), ranking(nullptr)
{

}

RankingDispScene::~RankingDispScene()
{

}

void RankingDispScene::Initialize()
{
	background_image = LoadGraph("Resource/images/Ranking.bmp");

	if (background_image == -1)
	{
		throw("Resource/images/Ranking.bmp‚ª‚ ‚è‚Ü‚¹‚ñ\n");
	}

	ranking = new RankingData;
	ranking->Initalize();
}

eSceneType RankingDispScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

void RankingDispScene::Draw() const
{
	DrawGraph(0, 0, background_image, FALSE);

	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %-15s %6d", ranking->GetRank(i), ranking->GetName(i), ranking->GetScore(i));
	}
}

void RankingDispScene::Finalize()
{
	DeleteGraph(background_image);

	ranking->Finalize();
	delete ranking;
}

eSceneType RankingDispScene::GetNowScene() const
{
	return eSceneType::E_RANKING_DISP;
}