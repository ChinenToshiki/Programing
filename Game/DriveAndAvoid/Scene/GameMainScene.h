#pragma once
#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include "../Object/Trial.h"
#include"Charges.h"
#include"../Object/Trial.h"

class GameMainScene :public SceneBase
{
private:
	int high_score;
	int back_ground;
	int barrier_image;
	int mileage;
	int enemy_image[ENEMY_NUM];
	int enemy_count[ENEMY_NUM];
	bool hit;

	Player* player;
	Enemy** enemy;
	Charges* charges;
	Trial* trial;
	static int JudgeCount;

public:

	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
	static const int GetTiarl();

private:
	void ReadHighScore();
	bool IsHitCheck(Player* p, Enemy* e);
};