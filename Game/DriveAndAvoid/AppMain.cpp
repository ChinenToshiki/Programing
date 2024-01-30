#include"DxLib.h"
#include"Scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstancce, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	try
	{
		SceneManager manager;
		
		manager.Initialize();

		manager.Update();

		manager.Finalize();
	}
	catch (const char* err_log)
	{
		OutputDebugString(err_log);

		return -1;
	}

	return 0;
}