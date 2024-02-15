#pragma once
class Charges
{
private:
	int fps;		//�t���[��
	int type;		//�^�C�v
	int get_rand;
	int trial_count;//�ٔ����󂯂��񐔂��J�E���g
	int count;		//�ԂƂԂ������񐔂��J�E���g
	int image[3];		//�摜�p

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
	//�^�C�v���Z�b�g
	void SetType(int _type);

	//�t���O���擾
	bool GetChargesFlg() { return image_flg; }
	void SetChargesFlg(bool flg) { image_flg = flg, fps_flg = false; }
	bool GetOnce() { return  once; }
	int GetTiralCount() { return trial_count; }
	int GetFps() { return fps; }

	int Rand();

};

