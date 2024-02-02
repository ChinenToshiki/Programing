#include "RankingData.h"
#include <stdio.h>
#include <string.h>

RankingData::RankingData()
{
	for (int i = 0; i < 6; i++)
	{
		score[i] = NULL;
		rank[i] = NULL;
		for (int j = 0; j < 15; j++)
		{
			name[i][j] = '\0';
		}
	}
}

RankingData::~RankingData()
{

}

//初期化処理
void RankingData::Initalize()
{
	FILE* fp = nullptr;

	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "r");

	if (result != 0)
	{
		throw("Resource/dat/ranking_data.csvが開けませんでした\n");
	}

	for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%d,%d,%[^,],\n", &score[i], &rank[i], name[i], 15);
	}

	fclose(fp);

	score[5] = 0;
	rank[5] = 0;
	name[5][0] = '\0';
}

//終了処理
void RankingData::Finalize()
{

}

//データ設定処理
void RankingData::SetRankingData(int score, const char* name)
{
	this->score[5] = score;
	strcpy_s(this->name[5], name);

	SortData();
}
//スコア取得処理
int RankingData::GetScore(int value) const
{
	return score[value];
}
//ランク取得処理
int RankingData::GetRank(int value) const
{
	return rank[value];
}
//名前取得処理
const char* RankingData::GetName(int value)const
{
	return name[value];
}
//データ入れ替え処理
void RankingData::SortData()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (score[i] <= score[j])
			{
				int tmp = score[i];
				score[i] = score[j];
				score[j] = tmp;

				char buf[15] = {};
				strcpy_s(buf, name[i]);
				strcpy_s(name[i], name[j]);
				strcpy_s(name[j], buf);
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		rank[i] = 1;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (score[i] > score[j])
			{
				rank[j]++;
			}
		}
	}

	FILE* fp = nullptr;

	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "w");

	if (result != 0)
	{
		throw("Resource/dat/ranking_data.csvが開けませんでした\n");
	}

	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%d,%d,%s,\n", score[i], rank[i], name[i]);
	}
	fclose(fp);
}