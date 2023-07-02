#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Mutal.h"
#include "Main.h"

Main::Main()
{
	map = new ObTileMap();
	map->file = "map1.txt";
	map->Load();
	map->color = Color(0.5f, 0.5f, 0.5f, 0.5f);

	pl = new Player();
}

Main::~Main()
{
}

void Main::Init()
{
	pl->Init(Vector2());
}

void Main::Release()
{
   
}

void Main::Update()
{
    ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());
	pl->Update();
	map->Update();
	CAM->position = pl->GetWorldPos();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	map->Render();
	pl->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(800.0f,600.0f);
    app.background = Color(0.3, 0.3, 0.3);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}