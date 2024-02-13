#pragma once
#include <vector>
#include <string>
#define ENEMY_NUM 4


using namespace std;

struct sTrialData					//�ٔ��̕��̓f�[�^�\����
{
	string interrogatory;			//��蕶�̃x�N�^�[
	vector<string> answer;			//���̓���
	vector<string> choices;			//���̑I����
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

public:
	Trial();					//�R���X�g���N�^
	~Trial();					//�f�X�g���N�^

	void Initilize(int type);	//����������
	void Finalize();			//�I������

	void Draw() const;			//�`�揈��
	void Update();				//�X�V����

	void LoadTrialData();		//��蕶�ƕ��͂������Ă���

	bool GetVictoryOrDefeat();	//���s�̐^�U�������Ă���
};

