#pragma once
class Charges
{
private:
	int fps;		//�t���[��
	int judgment_count;//�ٔ����󂯂��񐔂��J�E���g
	int count;		//�ԂƂԂ������񐔂��J�E���g
	int image;		//�摜�p

	bool image_flg; //�摜�p�t���O
	bool once;		//��x�����̏����p
	bool fps_flg;	//fps�p�t���O
public:
	Charges();
	~Charges();

	void Initialize();				//����������
	void Update();		//�X�V����
	void Draw() const;				//�`�揈��
	void Finalize();				//�I����

	//�ٔ����Z
	void JudgmentCount() { count += 1; }

	void HitCount();

	//�t���O���擾
	bool GetChargesFlg() { return image_flg; }
	bool GetOnce() { return  once; }

};

