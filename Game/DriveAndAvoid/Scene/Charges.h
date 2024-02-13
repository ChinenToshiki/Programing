#pragma once
class Charges
{
private:
	int image;		//画像用
	bool image_flg; //画像用フラグ
	bool once;		//ボタンを押したか
public:
	Charges();
	~Charges();

	void Initialize();				//初期化処理
	void Update(int player_hp);		//更新処理
	void Draw() const;				//描画処理
	void Finalize();				//終了中

	//フラグを取得
	bool GetChargesFlg() { return image_flg; }
	bool GetOnce() { return  once; }

};

