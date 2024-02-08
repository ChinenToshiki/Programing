#include "SceneManager.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include"TitleScene.h"
#include"GameMainScene.h"
#include"ResultScene.h"
#include"HelpScene.h"
#include"RankingDispScene.h"
#include"RankingInputScene.h"

SceneManager::SceneManager() : current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{

}

//�V�[���}�l�[�W���[�@�\:����������
void SceneManager::Initialize()
{
	//�E�B���h�E�̃^�C�g����ݒ�
	SetMainWindowText("Drive&Avoid");

	//�E�B���h�E���[�h�ŋN��
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("�E�B���h�E���[�h�ŋN���ł��܂���ł���\n");
	}

	if (DxLib_Init() == -1)
	{
		throw("Dx���C�u�������������ł��܂���ł���\n");
	}

	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("�`���̎w�肪�ł��܂���ł���\n");
	}

	//�^�C�g���V�[���֔��
	ChangeScene(eSceneType::E_TITLE);
}

//�V�[���}�l�[�W���[�@�\:�X�V
void SceneManager::Update()
{
	//�t���[���J�n����(�}�C�N���b)���擾
	LONGLONG start_time = GetNowHiPerformanceCount();

	//���C�����[�v
	while (ProcessMessage() != -1)
	{
		//���ݎ���
		LONGLONG now_time = GetNowHiPerformanceCount();

		//1�t���[��������̎��ԂɒB������X�V�ƕ`��
		if ((now_time - start_time) >= DELTA_SECOND)
		{

			//�t���[���J�n���Ԃ̍X�V
			start_time = now_time;

			//���͏���:�X�V
			InputControl::Update();
			
			//�X�V����
			eSceneType next = current_scene->Update();

			Draw();

			if (next == eSceneType::E_END)
			{
				break;
			}

			if (next != current_scene->GetNowScene())
			{
				ChangeScene(next);
			}
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) || InputControl::GetButtonUp(XINPUT_BUTTON_BACK))
		{
			break;
		}
	}
}

void SceneManager::Finalize()
{
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
	DxLib_End();
}

void SceneManager::Draw() const
{
	ClearDrawScreen();

	current_scene->Draw();

	ScreenFlip();
}

void SceneManager::ChangeScene(eSceneType scene_type)
{
	SceneBase* new_scene = dynamic_cast<SceneBase*>(CreateScene(scene_type));
	if (new_scene == nullptr)
	{
		throw("�V�[�����쐬�ł��܂���ł���\n");
	}
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	new_scene->Initialize();
	current_scene = new_scene;
}

SceneBase* SceneManager::CreateScene(eSceneType scene_type)
{
	switch (scene_type)
	{
	case E_TITLE:
		return new TitleScene;
	case E_MAIN:
		return new GameMainScene;
	case E_HELP:
		return new HelpScene;
	case E_RANKING_DISP:
		return new RankingDispScene;
	case E_RANKING_INPUT:
		return new RankingInputScene;
	case E_RESULT:
		return new ResultScene;
	default:
		return nullptr;
	}
}