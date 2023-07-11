#include "stdafx.h"
#include "Player.h"
#include "Mutal.h"
#include "PathTrail.h"
#include "Scene2_inGame.h"

Scene2_inGame::Scene2_inGame()
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

Scene2_inGame::~Scene2_inGame()
{
	delete player;
	delete mutal;
	delete pathTrail;
}

void Scene2_inGame::Init()
{
	player->Init(Vector2(100, 100));
	mutal->Init(Vector2(100, 230));
}

void Scene2_inGame::Release()
{
}

void Scene2_inGame::Update()
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
	if (INPUT->KeyDown(VK_F2))
	{
		mutal->isMoving = true;
	}

	ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());
	ImGui::Text(u8"[ F1 ] 경로설정\n");
	ImGui::Text(u8"[ F2 ] 뮤탈이동\n");
	ImGui::Text("\n");
	player->Update();
	mutal->Update();
	pathTrail->Update();
	for (auto& map : tileMap)
		map->Update();
	CAM->position = player->GetWorldPos();
}

void Scene2_inGame::LateUpdate()
{
	if (tileMap[1]->GetTileState(player->GetFoot()) == TILE_WALL)
	{
		player->GoBack();
	}
	if (tileMap[1]->GetTileState(mutal->col->GetWorldPos()) == TILE_WALL)
	{
		mutal->GoBack();
	}
}

void Scene2_inGame::Render()
{
	for (auto& map : tileMap)
		map->Render();
	player->Render();
	mutal->Render();
	pathTrail->Render();
}

void Scene2_inGame::ResizeScreen()
{
}
