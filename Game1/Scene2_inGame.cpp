#include "stdafx.h"
#include "Player.h"
#include "Scene2_inGame.h"

Scene2_inGame::Scene2_inGame()
{
	tileMap[0] = new ObTileMap();
	tileMap[0]->file = "map0.txt";
	tileMap[0]->Load();

	tileMap[1] = new ObTileMap();
	tileMap[1]->file = "map1.txt";
	tileMap[1]->Load();
	//tileMap[1]->CreateTileCost();

	tileMap[2] = new ObTileMap();
	tileMap[2]->file = "map2.txt";
	tileMap[2]->Load();
	//tileMap[2]->CreateTileCost();

	player = new Player();
}

Scene2_inGame::~Scene2_inGame()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];

	delete player;
	delete mutal;
	delete pathTrail;
}

void Scene2_inGame::Init()
{
	player->Init(Vector2(800, 550));
}

void Scene2_inGame::Release()
{
}

void Scene2_inGame::Update()
{
	ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());

	CAM->position = player->GetCollider()->GetWorldPos();

	for (auto& map : tileMap)
		map->Update();
	player->Update();

}

void Scene2_inGame::LateUpdate()
{
}

void Scene2_inGame::Render()
{
	tileMap[0]->Render();
	tileMap[1]->Render();
	if (GM->DEBUG_MODE) tileMap[2]->Render();
	
	player->Render();
}

void Scene2_inGame::ResizeScreen()
{
}
