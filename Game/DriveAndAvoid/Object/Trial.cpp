#include "Trial.h"
#include"../Utility/InputControl.h"
#include <stdio.h>
#include "DxLib.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>


Trial::Trial() : background_image(0), presiding_judge(0), win_image(0), lose_image(0), trial_data(),sfile_name(),question_num(0)
{
	sfile_name[0] = "Resource/text/test.txt";
	sfile_name[1] = "Resource/text/test.txt";
	sfile_name[2] = "Resource/text/test.txt";
	sfile_name[3] = "Resource/text/test.txt";
	victory_or_defeat = false;
}

Trial::~Trial()
{

}

void Trial::Initilize(int type)
{


	enemy_type = type;

	question_num = 1;

	background_image = LoadGraph("Resource/images/裁判.png");

	if (background_image == -1)
	{
		throw("Resource/images/裁判.pngがありません");
	}

	LoadTrialData();
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
		victory_or_defeat = true;
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


	//問題文の描画
	DrawFormatString(15, 15, 0x00ff00, trial_data[0].interrogatory.c_str());

	SetFontSize(25);
	//選択肢の描画
	DrawFormatString(40, 370, 0x00ff00, trial_data[0].choices[0].c_str());
	DrawFormatString(40, 420, 0x00ff00, trial_data[0].choices[1].c_str());

	//カーソルの描画
	DrawTriangle(10, 350, 10, 375, 30, 362, 0xff00ff, TRUE);



}

//問題文を読み込む関数
void Trial::LoadTrialData()
{
	string line;					//文章読み込み用
	sTrialData local_trial_data;	//おおもとのsTrialData型のベクター型にプッシュバックするためにデータを一次保存する変数
	
	ifstream ifss(sfile_name[enemy_type].c_str());
	
	
	if (ifss.fail())
	{
		throw "ファイルオープンに失敗しました";
	}

	while (!ifss.eof() && getline(ifss, line))
	{
		istringstream stringstream(line);

		if (getline(stringstream, line, ' '))
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
			else if (strcmp(line.c_str(), "A") == 0)
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

bool Trial::GetVictoryOrDefeat()
{
	return victory_or_defeat;
}

