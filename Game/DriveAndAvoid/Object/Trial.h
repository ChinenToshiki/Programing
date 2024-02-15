#pragma once
#include <vector>
#include <string>
#define ENEMY_NUM 4


using namespace std;

struct sTrialData					//�ٔ��̕��̓f�[�^�\����
{
	vector<string> interrogatory;	//��蕶�̃x�N�^�[
	unsigned int number_of_lines;	//��蕶�̍s��
	unsigned int answer;			//���̓���
	vector<string> choices;			//���̑I����
	unsigned int choices_num;		//�I�����̐�
};


//�ٔ��̃N���X
class Trial
{
private:
	int background_image;				//�w�i�C���[�W
	int presiding_judge;				//�ٔ����摜
	int win_image;						//���i�摜
	int lose_image;						//�s�i�摜
	int enemy_type;						//�G�̃^�C�v
	string sfile_name[ENEMY_NUM];		//�L�������Ƃ̖�蕶�Ȃǂ̃t�@�C���l�[���z��
	vector<sTrialData> trial_data;		//�\���̕ϐ�
	unsigned int question_num;			//���␔
	bool victory_or_defeat;				//���s�^�U
	unsigned int correct_num;			//����
	unsigned int wrong_num;				//�s����
	int select_answer;					//�I���J�[�\���ϐ�
	unsigned int num_of_problems_now;	//���̖�萔
	bool end;							//�ٔ���ʏI��
	unsigned int num_of_actual_problems;//���ۂ̖�萔

	//�������特���ϐ�
	int laughing_hard;					//���Ή���

public:
	Trial();					//�R���X�g���N�^
	~Trial();					//�f�X�g���N�^

	void Initilize(int type);	//����������
	void Finalize();			//�I������

	void Draw() const;			//�`�揈��
	void Update();				//�X�V����

	void LoadTrialData();		//��蕶�ƕ��͂������Ă���

	bool GetVictoryOrDefeat();	//���s�̐^�U�������Ă���
	bool GetEnd();				//�ٔ���ʏI����m�点��
};

