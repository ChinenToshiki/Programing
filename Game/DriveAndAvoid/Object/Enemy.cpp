#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy(int type, int handle) :type(type), image(handle), speed(0.0f), location(0.0f), box_size(0.0f)
{

}

Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	//�o�������邘���W
	float random_x = (float)(GetRand(4) * 105 + 40);
	//�����蔻��̐ݒ�
	if (type != 3) {
		box_size = Vector2D(31.0f, 60.0f);
		//�����ʒu�̐ݒ�
		location = Vector2D(random_x, -50.0f);
	}
	else {
		box_size = Vector2D(31.0f, 104.0f);
		//�����ʒu�̐ݒ�
		location = Vector2D(random_x, -100.0f);
	}
	//�����̐ݒ�
	speed = (float)(this->type * 2);
}

void Enemy::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 6);

}

void Enemy::Draw() const
{
	//�G�摜�̕`��
	if (type != 3) {
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	}
	else {
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, FALSE);
	}
}
	

void Enemy::Finalize()
{

}

//�G�̃^�C�v���擾
int Enemy::GetType() const
{
	return type;
}

//�ʒu�����擾
Vector2D Enemy::GetLocation() const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}

