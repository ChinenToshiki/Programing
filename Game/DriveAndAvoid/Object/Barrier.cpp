#include "Barrier.h"
#include "DxLib.h"

Barrier::Barrier() : image(NULL), life_span(1000)
{
	image = LoadGraph("Resource/images/barrier.png");
	
	if (image == -1)
	{
		throw("Resource/images/barrier.png������܂���\n");
	}

}

Barrier::~Barrier()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);
}

void Barrier::Draw(const Vector2D& location)
{
	DrawRotaGraph(location.x, location.y, 10, 0.0, image, TRUE);
}

bool Barrier::IsFinished(float speed)
{
	life_span -= speed;
	return(life_span = 0);
}

