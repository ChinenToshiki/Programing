#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy(int type, int handle) :type(type), image(handle), speed(0.0f), location(0.0f), box_size(0.0f)
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	float random_x = (float)(GetRand(4) * 105 + 40);
	location = Vector2D(random_x, -50.0f);
	box_size = Vector2D(31.0f, 60.0f);
	speed = (float)(this->type * 2);
}

void Enemy::Update(float speed)
{
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Enemy::Finalize()
{

}

int Enemy::GetType() const
{
	return type;
}

Vector2D Enemy::GetLocation() const
{
	return location;
}

Vector2D Enemy::GetBoxSize() const
{
	return box_size;
}

