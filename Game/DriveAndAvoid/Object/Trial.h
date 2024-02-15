#pragma once
#include <vector>
#include <string>
#define ENEMY_NUM 4


using namespace std;

struct sTrialData					//裁判の文章データ構造体
{
	vector<string> interrogatory;	//問題文のベクター
	unsigned int number_of_lines;	//問題文の行数
	unsigned int answer;			//問題の答え
	vector<string> choices;			//問題の選択肢
	unsigned int choices_num;		//選択肢の数
};


//裁判のクラス
class Trial
{
private:
	int background_image;				//背景イメージ
	int presiding_judge;				//裁判長画像
	int win_image;						//勝訴画像
	int lose_image;						//敗訴画像
	int enemy_type;						//敵のタイプ
	string sfile_name[ENEMY_NUM];		//キャラごとの問題文などのファイルネーム配列
	vector<sTrialData> trial_data;		//構造体変数
	unsigned int question_num;			//質問数
	bool victory_or_defeat;				//勝敗真偽
	unsigned int correct_num;			//正解数
	unsigned int wrong_num;				//不正解数
	int select_answer;					//選択カーソル変数
	unsigned int num_of_problems_now;	//今の問題数
	bool end;							//裁判画面終了
	unsigned int num_of_actual_problems;//実際の問題数

	//ここから音源変数
	int laughing_hard;					//爆笑音源

public:
	Trial();					//コンストラクタ
	~Trial();					//デストラクタ

	void Initilize(int type);	//初期化処理
	void Finalize();			//終了処理

	void Draw() const;			//描画処理
	void Update();				//更新処理

	void LoadTrialData();		//問題文と文章をもってくる

	bool GetVictoryOrDefeat();	//勝敗の真偽を持ってくる
	bool GetEnd();				//裁判画面終了を知らせる
};

