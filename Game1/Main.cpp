#include "stdafx.h"
#include "Scene1_title.h"
#include "Scene2_inGame.h"
#include "Main.h"

Main::Main()
{
	sc1_title = new Scene1_title();
	sc2_inGame = new Scene2_inGame();
}

Main::~Main()
{
	SCENE->~SceneManager();
}

void Main::Init()
{
	sc1_title->Init();
	sc2_inGame->Init();
	SCENE->AddScene("sc1", sc1_title);
	SCENE->AddScene("sc2", sc2_inGame);
	SCENE->ChangeScene("sc1");
}

void Main::Release()
{
   
}

void Main::Update()
{
	SCENE->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();
}

void Main::Render()
{
	SCENE->Render();
}

void Main::ResizeScreen()
{
	SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1200.0f,800.0f);
    app.background = Color(0.3, 0.3, 0.3);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}