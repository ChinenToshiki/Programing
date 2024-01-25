#pragma once

#include "SceneBase.h"

class HelpScene :public SceneBase
{
private:
	int background_image;

public:
	HelpScene();
	virtual ~HelpScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};