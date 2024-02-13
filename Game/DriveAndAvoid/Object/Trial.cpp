#include "Trial.h"
#include"../Utility/InputControl.h"
#include <stdio.h>
#include "DxLib.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>


Trial::Trial() : background_image(0), presiding_judge(0), win_image(0), lose_image(0), trial_data(),sfile_name()
{
}

Trial::~Trial()
{

}

void Trial::Initilize()
{
	sfile_name[0] = "";
	sfile_name[1] = "";
	sfile_name[0] = "";
	sfile_name[0] = "";

	question_num = 1;

}

void Trial::Finalize()
{

}

void Trial::Update()
{


	unsigned int select_answer = 1;


	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{

	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{

	}

}

void Trial::Draw() const
{
	DrawGraph(0, 0, background_image, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawBox(10, 350, 590, 470, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}

//問題文を読み込む関数
void Trial::LoadTrialData()
{
	string line;					//文章読み込み用
	sTrialData local_trial_data;	//おおもとのsTrialData型のベクター型にプッシュバックするためにデータを一次保存する変数
	
	ifstream ifss(sfile_name[0].c_str());

	while (!getline(ifss, line).eof())
	{
		std::istringstream stringstream(line);

		if (stringstream, line, ' ')
		{
			if (strcmp(line.c_str(), "q") == 0)
			{
				getline(stringstream, line, ' ');
				local_trial_data.interrogatory = line;
				question_num++;
				continue;
			}
			else if (strcmp(line.c_str(), "s") == 0)
			{
				getline(stringstream, line, ' ');
				local_trial_data.choices.push_back(line);
				continue;
			}
			else if (strcmp(line.c_str(), "a") == 0)
			{
				getline(stringstream, line, ' ');
				local_trial_data.answer.push_back(line);
				trial_data.push_back(local_trial_data);
				continue;
			}
			else{}
		}

	}

}
