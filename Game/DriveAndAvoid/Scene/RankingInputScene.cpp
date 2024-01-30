#include "RankingInputScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingInputScene::RankingInputScene() :background_image(NULL), ranking(nullptr), score(0), name_num(0), cursor_x(0), cursor_y(0)
{
	memset(name, NULL, (sizeof(char) * 15));
}

RankingInputScene::~RankingInputScene()
{

}

void RankingInputScene::Initialize()
{
	background_image = LoadGraph("Resource/images/Ranking.bmp");

	if (background_image == -1)
	{
		throw("Resource / images / Ranking.bmp‚ª‚ ‚è‚Ü‚¹‚ñ\n");
	}

	ranking = new RankingData;
	ranking->Initalize();

	FILE* fp = nullptr;

	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	if (result != 0)
	{
		throw("Resource/dat/result_data.csv‚ª“Ç‚Ýž‚ß‚Ü‚¹‚ñ\n");
	}

	fscanf_s(fp, " %6d, \n", &score);

	fclose(fp);
}

eSceneType RankingInputScene::Update()
{
	bool is_change = false;

	is_change = InputName();

	if (is_change)
	{
		return eSceneType::E_RANKING_DISP;
	}
	else
	{
		return GetNowScene();
	}
}

void RankingInputScene::Draw() const
{
	DrawGraph(0, 0, background_image, TRUE);

	DrawString(150, 100, "ƒ‰ƒ“ƒLƒ“ƒO‚É“o˜^‚µ‚Ü‚·", 0xFFFFFF);
	DrawFormatString(100, 220, GetColor(255, 255, 255), ">%s", name);

	const int font_size = 25;
	for (int i = 0; i < 26; i++)
	{
		int x = (i % 13) * font_size + 15;
		int y = (i / 13) * font_size + 300;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%-3c", 'a' + i);
		y = ((i / 13) + 2) * font_size + 300;
		DrawFormatString(x, y, GetColor(255, 255, 255), " % -3c", 'A' + i);
	}
	DrawString(40, 405, "Œˆ’è", GetColor(255, 255, 255));
	DrawString(40 + font_size * 2, 405, "Á‚·", GetColor(255, 255, 255));

	if (cursor_y < 4)
	{
		int x = cursor_x * font_size + 10;
		int y = cursor_y * font_size + 295;
		DrawBox(x, y, x + font_size, y + font_size, GetColor(255, 255, 255), FALSE);
	}
	else
	{
		if (cursor_x == 0)
		{
			DrawBox(35, 400, 35 + font_size * 2, 400 + font_size, GetColor(255, 255, 255), FALSE);
		}
		else
		{
			DrawBox(0, 0, font_size, font_size, GetColor(255, 255, 255), FALSE);
		}
	}
}

void RankingInputScene::Finalize()
{
	ranking->SetRankingData(score, name);

	DeleteGraph(background_image);

	delete ranking;
}

eSceneType RankingInputScene::GetNowScene() const
{
	return eSceneType::E_RANKING_INPUT;
}

bool RankingInputScene::InputName()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		if (cursor_x > 0)
		{
			cursor_x--;
		}
		else
		{
			cursor_x = 12;
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		if (cursor_x < 12)
		{
			cursor_x++;
		}
		else
		{
			cursor_x = 0;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		if (cursor_y > 0)
		{
			cursor_y--;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		if (cursor_y < 4)
		{
			cursor_y++;
			if (cursor_y == 4)
			{
				cursor_x = 0;
			}
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		if (cursor_y < 2)
		{
			name[name_num++] = 'a' + cursor_x + (cursor_y * 13);
			if (name_num == 14)
			{
				cursor_x = 0;
				cursor_y = 4;
			}
		}
		else if (cursor_y < 4)
		{
			name[name_num++] = 'A' + cursor_x + ((cursor_y - 2) * 13);
			if (name_num == 14)
			{
				cursor_x = 0;
				cursor_y = 4;
			}
		}
		else
		{
			if (cursor_x == 0)
			{
				name[name_num] = '\0';
				return true;
			}
			else
			{
				name[name_num--] = NULL;
			}
		}
	}
	return false;
}