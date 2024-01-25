#pragma once

enum eSceneType
{
	E_TITLE,
	E_MAIN,
	E_HELP,
	E_RANKING_DISP,
	E_RANKING_INPUT,
	E_RESULT,
	E_END
};

class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Initialize() {}
	virtual eSceneType Update()
	{
		return GetNowScene();
	}

	virtual void Draw() const {}

	virtual void Finalize() {}

	virtual eSceneType GetNowScene() const = 0;

};