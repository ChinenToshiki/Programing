#pragma once
class Charges
{
private:
	int image;		//�摜�p
	bool image_flg; //�摜�p�t���O
	bool once;		//�{�^������������
public:
	Charges();
	~Charges();

	void Initialize();				//����������
	void Update(int player_hp);		//�X�V����
	void Draw() const;				//�`�揈��
	void Finalize();				//�I����

	//�t���O���擾
	bool GetChargesFlg() { return image_flg; }
	bool GetOnce() { return  once; }

};

