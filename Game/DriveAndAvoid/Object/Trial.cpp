#include "Trial.h"
#include"../Utility/InputControl.h"
#include <stdio.h>
#include "DxLib.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>


#define SELECT_DHISTANCE 30
#define MAX_QUESTION 3

Trial::Trial() : background_image(0), presiding_judge(0), win_image(0), lose_image(0), trial_data(0),sfile_name(),question_num(0)
{
	sfile_name[0] = "Resource/text/スポーツカー.txt";
	sfile_name[1] = "Resource/text/セダン車(青).txt";
	sfile_name[2] = "Resource/text/セダン車(赤).txt";
	victory_or_defeat = false;
	correct_num = 0;
	wrong_num = 0;
	select_answer = 0;
	num_of_problems_now = 0;
	num_of_actual_problems = 0;
	laughing_hard = 0;
	wrong_sound = 0;
	correct_sound = 0;
}

Trial::~Trial()
{

}

void Trial::Initilize(int type)
{


	enemy_type = type;

	question_num = 0;

	background_image = LoadGraph("Resource/images/裁判.png");
	win_image = LoadGraph("Resource/images/勝訴.png");
	lose_image = LoadGraph("Resource/images/有罪.png");

	if (background_image == -1)
	{
		throw("Resource/images/裁判.pngがありません");
	}
	if (win_image == -1)
	{
		throw("Resource/images/勝訴.pngがありません");
	}
	if (lose_image == -1)
	{
		throw("Resource/images/勝訴.bmgがありません");
	}

	laughing_hard = LoadSoundMem("Resource/sounds/爆笑3～6名.mp3");
	wrong_sound = LoadSoundMem("Resource/sounds/不正解1.mp3");
	correct_sound = LoadSoundMem("Resource/sounds/correct001.mp3");

	if (laughing_hard == -1)
	{
		throw("Resource/sounds/爆笑3～6名.mp3");
	}
	if (wrong_sound == -1)
	{
		throw("Resource/sounds/不正解1.mp3");
	}
	if (correct_sound == -1)
	{
		throw("Resource/sounds/correct001.mp3");
	}


	LoadTrialData();

	srand((unsigned)time(NULL)); //乱数の仕組みを初期化。
	num_of_actual_problems = GetRand(11); //乱数の生成

}

void Trial::Finalize()
{

}

void Trial::Update()
{

	if (num_of_problems_now < MAX_QUESTION)
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
		{
			select_answer--;

			if (select_answer < 0)
			{
				select_answer = trial_data[num_of_actual_problems].choices_num - 1;
			}
		}

		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
		{
			select_answer++;
			if (select_answer > trial_data[num_of_actual_problems].choices_num - 1)
			{
				select_answer = 0;
			}
		}

		if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
		{
			if (select_answer == trial_data[num_of_actual_problems].answer)
			{
				correct_num++;
				PlaySoundMem(correct_sound, DX_PLAYTYPE_NORMAL, TRUE);
			}
			else
			{
				PlaySoundMem(wrong_sound, DX_PLAYTYPE_NORMAL, TRUE);
			}

			select_answer = 0;


			srand((unsigned)time(NULL)); //乱数の仕組みを初期化。
			num_of_actual_problems = GetRand(11); //乱数の生成
			num_of_problems_now++;

			if (num_of_problems_now == MAX_QUESTION)
			{
				if (correct_num > MAX_QUESTION / 2)
				{
					PlaySoundMem(laughing_hard, DX_PLAYTYPE_LOOP, TRUE);
					victory_or_defeat = true;
				}
				else
				{
					PlaySoundMem(laughing_hard, DX_PLAYTYPE_LOOP, TRUE);
					victory_or_defeat = false;
				}
			}
		}
	}
	else
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
		{
			end = true;
		}
	}
}

void Trial::Draw() const
{
	//背景画像
	DrawGraph(0, 0, background_image, TRUE);


	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	//問題文を描画する箱
	DrawBox(10, 10, 590, 130, GetColor(255, 255, 255), TRUE);
	//選択肢を描画する箱
	DrawBox(10, 350, 590, 470, 0xffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	

	if (num_of_problems_now < MAX_QUESTION)
	{
		//問題文の描画
		for (int i = 0; i < trial_data[num_of_actual_problems].number_of_lines; i++)
		{
			DrawFormatString(15, 15 + (25 * i), 0x00ff00, trial_data[num_of_actual_problems].interrogatory[i].c_str());
		}
		
		SetFontSize(25);
		//選択肢の描画
		for (int i = 0; i < trial_data[num_of_actual_problems].choices_num; i++)
		{
			DrawFormatString(40, 350 + (30 * i), 0x00ff00, trial_data[num_of_actual_problems].choices[i].c_str());
		}

		//カーソルの描画
		DrawTriangle(10, 350 + (SELECT_DHISTANCE * select_answer), 10, 375 + (SELECT_DHISTANCE * select_answer), 30, 362 + (SELECT_DHISTANCE * select_answer), 0xff00ff, TRUE);
	}
	else
	{
		if (victory_or_defeat)
		{
			DrawGraph(0, 0, win_image, true);
		}
		else
		{
			DrawGraph(0, 0, lose_image, true);
		}
	}
}

//問題文を読み込む関数
void Trial::LoadTrialData()
{
	string line;					//文章読み込み用
	sTrialData local_trial_data;	//おおもとのsTrialData型のベクター型にプッシュバックするためにデータを一次保存する変数
	local_trial_data.choices_num = 0;
	local_trial_data.number_of_lines = 0;
	
	ifstream ifss(sfile_name[enemy_type].c_str());
	
	
	if (ifss.fail())
	{
		throw "ファイルオープンに失敗しました";
	}

	//ファイルから読み込んできた文章を変数に格納
	while (!ifss.eof() && getline(ifss, line))
	{
		istringstream stringstream(line);

		if (getline(stringstream, line, ' '))
		{
			if (strcmp(line.c_str(), "q") == 0)
			{
				getline(stringstream, line);

				local_trial_data.interrogatory.push_back(line);
				local_trial_data.number_of_lines++;

				continue;
			}
			else if (strcmp(line.c_str(), "s") == 0)
			{
				getline(stringstream, line);
				local_trial_data.choices.push_back(line);
				local_trial_data.choices_num++;
				continue;
			}
			else if (strcmp(line.c_str(), "A") == 0)
			{
				getline(stringstream, line);
				local_trial_data.answer = stoi(line);
				trial_data.push_back(local_trial_data);
				local_trial_data.answer = 0;
				local_trial_data.choices_num = 0;
				local_trial_data.number_of_lines = 0;
				local_trial_data.choices.clear();
				local_trial_data.interrogatory.clear();
				question_num++;
				continue;
			}
			else{}
		}

	}



}

bool Trial::GetVictoryOrDefeat()
{
	return victory_or_defeat;
}

bool Trial::GetEnd()
{
	return end;
}

