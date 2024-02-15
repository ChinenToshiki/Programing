#pragma once
class Charges
{
private:
	int fps;		//フレーム
	int type;		//タイプ
	int get_rand;
	int trial_count;//裁判を受けた回数をカウント
	int count;		//車とぶつかった回数をカウント
	int image[3];		//画像用

	bool image_flg; //画像用フラグ
	bool once;		//一度だけの処理用
	bool fps_flg;	//fps用フラグ
public:
	Charges();
	~Charges();

	void Initialize();				//初期化処理
	void Update();		//更新処理
	void Draw() const;				//描画処理
	void Finalize();				//終了中

	//裁判加算
	void JudgmentCount() { count += 1; }
	void HitCount();
	//タイプをセット
	void SetType(int _type);

	//フラグを取得
	bool GetChargesFlg() { return image_flg; }
	void SetChargesFlg(bool flg) { image_flg = flg, fps_flg = false; }
	bool GetOnce() { return  once; }
	int GetTiralCount() { return trial_count; }
	int GetFps() { return fps; }

	int Rand();

};

