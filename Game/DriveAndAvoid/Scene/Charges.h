#pragma once
class Charges
{
private:
	int count;		//�ٔ����󂯂��񐔂��J�E���g
	int image;		//�摜�p
	bool image_flg; //�摜�p�t���O
	bool once;		//�{�^������������
public:
	Charges();
	~Charges();

	void Initialize();				//����������
	void Update();		//�X�V����
	void Draw() const;				//�`�揈��
	void Finalize();				//�I����

	//�ٔ����Z
	void JudgmentCount() { count += 1; }

	//�t���O���擾
	bool GetChargesFlg() { return image_flg; }
	bool GetOnce() { return  once; }

};

