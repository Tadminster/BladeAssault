#include "stdafx.h"
#include "Player.h"
#include "Mutal.h"
#include "PathTrail.h"
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
	tileMap[1]->CreateTileCost();;
	//tileMap[1]->color = Color(0.5f, 0.5f, 0.5f, 0.5f);

	player = new Player();
	mutal = new Mutal();
	pathTrail = new PathTrail();
}

Main::~Main()
{
	delete player;
	delete mutal;
	delete pathTrail;
}

void Main::Init()
{
	player->Init(Vector2(100, 100));
	mutal->Init(Vector2(100, 230));
}

void Main::Release()
{
   
}

void Main::Update()
{
	if (INPUT->KeyDown(VK_F1))
	{
		if (tileMap[1]->PathFinding(mutal->col->GetWorldPos(),
			player->GetWorldPivot(), mutal->way))
		{
			system("cls");
			cout << "길 있음" << endl;
			for (int i = 0; i < mutal->way.size(); i++)
			{
				cout << "[" << i << "] ";
				cout << "X = " << mutal->way[i]->Pos.x << ", ";
				cout << "Y = " << mutal->way[i]->Pos.y;
				cout << endl;
			}

			pathTrail->Resize(mutal->way.size(), mutal->way);


		}
		else cout << "길 없음" << endl;
	}

    ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());
	player->Update();
	mutal->Update();
	pathTrail->Update();
	for (auto& map : tileMap)
		map->Update();
	CAM->position = player->GetWorldPos();
}

void Main::LateUpdate()
{

	//Int2 plIdx;
	//if (tileMap[1]->WorldPosToTileIdx(pl->GetWorldPos(), plIdx))
	//{
	//	if (tileMap[1]->GetTileState(plIdx) == TILE_WALL)
	//	{
	//		

	//		Vector2 playerPos = pl->GetWorldPos();
	//		Vector2 tilePos = Vector2(tileMap[1]->GetTilePosition(plIdx).x * 50 + 25, tileMap[1]->GetTilePosition(plIdx).y * 50 + 25);


	//		Vector2 Dir = playerPos - tilePos;
	//		Dir.Normalize();
	//		pl->MoveWorldPos(Dir * 300 * DELTA);
	//	}
	//}

	if (tileMap[1]->GetTileState(player->GetFoot()) == TILE_WALL)
	{
		player->GoBack();
	}
	if (tileMap[1]->GetTileState(mutal->col->GetWorldPos()) == TILE_WALL)
	{
		mutal->GoBack();
	}
}

void Main::Render()
{
	for (auto& map : tileMap)
		map->Render();
	player->Render();
	mutal->Render();
	pathTrail->Render();
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