#include "stdafx.h"
#include "HUD.h"
#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "redHairRat.h"
#include "Scene_proto.h"
#include "Scene5_undercity1.h"

Scene5_undercity1::Scene5_undercity1()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	nextMap = new ObRect();
}

Scene5_undercity1::~Scene5_undercity1()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];
	delete nextMap;
}

void Scene5_undercity1::Init()
{
	tileMap[0]->file = "scene5_undercity1_0.txt";
	tileMap[1]->file = "scene5_undercity1_1.txt";
	tileMap[2]->file = "scene5_undercity1_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	nextMap->SetWorldPos(Vector2(800, 4000));
	nextMap->scale = Vector2(100, 100);
	nextMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	nextMap->isFilled = true;

	startPostion = Vector2(800, 3000);

	GM->player->SetPosition(startPostion);

	GM->monster->AddMonster(new redHairRat(Vector2(750, 900)));
	GM->monster->AddMonster(new redHairRat(Vector2(1000, 900)));
	GM->monster->AddMonster(new redHairRat(Vector2(1200, 900)));
	GM->monster->AddMonster(new redHairRat(Vector2(1500, 900)));
	GM->monster->AddMonster(new redHairRat(Vector2(1750, 900)));
	GM->monster->AddMonster(new redHairRat(Vector2(2000, 900)));
}

void Scene5_undercity1::Release()
{
}

void Scene5_undercity1::Update()
{
	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());
	ImGui::Text("player_posX : %f\n", GM->player->GetCollider()->GetWorldPos().x);
	ImGui::Text("player_posY : %f\n", GM->player->GetCollider()->GetWorldPos().y);

	ImGui::Text("onFloor : %d\n", GM->player->onFloor);
	ImGui::Text("onWall : %d\n", GM->player->onWall);
	ImGui::Text("onWallside : %d\n", GM->player->onWallSlide);

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 다음 맵 이동
	if (nextMap->Intersect(GM->player->GetCollider()))
	{
		GM->monster->ClearMonster();
		SCENE->ChangeScene("sc2");
	}

	for (auto& map : tileMap)
		map->Update();
	nextMap->Update();
	GM->monster->Update();
	GM->player->Update();
	GM->hud->Update();
}

void Scene5_undercity1::LateUpdate()
{
	Scene_proto::LateUpdate();
}

void Scene5_undercity1::Render()
{
	tileMap[0]->Render();
	tileMap[1]->Render();
	if (GM->DEBUG_MODE)
	{
		tileMap[2]->Render();
		nextMap->Render();
	}

	GM->monster->Render();
	GM->player->Render();
	GM->hud->Render();
}

void Scene5_undercity1::ResizeScreen()
{
	GM->hud->Init();
}