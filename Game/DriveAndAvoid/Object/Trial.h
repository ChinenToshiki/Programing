#pragma once
#include <vector>
#include <string>
#define ENEMY_NUM 4


using namespace std;

struct sTrialData					//裁判の文章データ構造体
{
	string interrogatory;			//問題文のベクター
	vector<string> answer;			//問題の答え
	vector<string> choices;			//問題の選択肢
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

public:
	Trial();					//コンストラクタ
	~Trial();					//デストラクタ

	void Initilize(int type);	//初期化処理
	void Finalize();			//終了処理

	void Draw() const;			//描画処理
	void Update();				//更新処理

	void LoadTrialData();		//問題文と文章をもってくる

	bool GetVictoryOrDefeat();	//勝敗の真偽を持ってくる
};

