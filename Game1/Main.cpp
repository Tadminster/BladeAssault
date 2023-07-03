#include "stdafx.h"
#include "Player.h"
#include "Main.h"

Main::Main()
{
	tileMap[0] = new ObTileMap();
	tileMap[0]->file = "map1.txt";
	tileMap[0]->Load();
	//tileMap[0]->color = Color(0.5f, 0.5f, 0.5f, 0.5f);

	tileMap[1] = new ObTileMap();
	tileMap[1]->file = "map2.txt";
	tileMap[1]->Load();
	//tileMap[1]->color = Color(0.5f, 0.5f, 0.5f, 0.5f);

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
	for (auto& map : tileMap)
		map->Update();
	CAM->position = pl->GetWorldPos();
}

void Main::LateUpdate()
{

	Int2 plIdx;
	if (tileMap[1]->WorldPosToTileIdx(pl->GetWorldPos(), plIdx))
	{
		if (tileMap[1]->GetTileState(plIdx) == TILE_WALL)
		{
			

			Vector2 playerPos = pl->GetWorldPos();
			Vector2 tilePos = Vector2(tileMap[1]->GetTilePosition(plIdx).x * 50 + 25, tileMap[1]->GetTilePosition(plIdx).y * 50 + 25);


			Vector2 Dir = playerPos - tilePos;
			Dir.Normalize();
			pl->MoveWorldPos(Dir * 300 * DELTA);
		}
	}
}

void Main::Render()
{
	for (auto& map : tileMap)
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