#pragma once

#include"SceneBase.h"
#include"Charges.h"
#include"../Object/Trial.h"
#include "GameMainScene.h"

class ResultScene : public SceneBase
{
private:
	int back_ground;
	int score;
	int enemy_count[ENEMY_NUM];
	int enemy_image[ENEMY_NUM];

public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	void ReadResultData();

};