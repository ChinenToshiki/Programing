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

void RankingData::Initalize()
{
	FILE* fp = nullptr;

	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "r");

	if (result != 0)
	{
		throw("Resource/dat/ranking_data.csv‚ªŠJ‚¯‚Ü‚¹‚ñ‚Å‚µ‚½\n");
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

void RankingData::Finalize()
{

}

void RankingData::SetRankingData(int score, const char* name)
{
	this->score[5] = score;
	strcpy_s(this->name[5], name);

	SortData();
}

int RankingData::GetScore(int value) const
{
	return score[value];
}

int RankingData::GetRank(int value) const
{
	return rank[value];
}

const char* RankingData::GetName(int value)const
{
	return name[value];
}

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
		throw("Resource/dat/ranking_data.csv‚ªŠJ‚¯‚Ü‚¹‚ñ‚Å‚µ‚½\n");
	}

	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%d,%d,%s,\n", score[i], rank[i], name[i]);
	}
	fclose(fp);
}