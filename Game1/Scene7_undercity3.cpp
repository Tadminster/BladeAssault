#include "stdafx.h"
#include "HUD.h"
#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "DamageDisplayManager.h"
#include "redHairRat.h"
#include "orangeHairRat.h"
#include "Scene_proto.h"
#include "Scene7_undercity3.h"

Scene7_undercity3::Scene7_undercity3()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	nextMap = new ObRect();

	//tileMap[0]->file = "scene6_undercity2_0.txt";
	//tileMap[1]->file = "scene6_undercity2_1.txt";
	//tileMap[2]->file = "scene6_undercity2_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	nextMap->SetWorldPos(Vector2(800, 4000));
	nextMap->scale = Vector2(100, 100);
	nextMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	nextMap->isFilled = true;

	startPostion = Vector2(1000, 1250);
}

Scene7_undercity3::~Scene7_undercity3()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];
	delete nextMap;
}

void Scene7_undercity3::Init()
{
	GM->player->Init();
	GM->player->SetPosition(startPostion);

	GM->monster->AddMonster(new redHairRat(Vector2(1450, 1525)));
	GM->monster->AddMonster(new orangeHairRat(Vector2(2000, 1250)));
	GM->monster->AddMonster(new redHairRat(Vector2(1450, 1075)));
	GM->monster->AddMonster(new redHairRat(Vector2(1850, 975)));
	GM->monster->AddMonster(new redHairRat(Vector2(1200, 725)));
	GM->monster->AddMonster(new orangeHairRat(Vector2(1500, 725)));
	GM->monster->AddMonster(new orangeHairRat(Vector2(1800, 725)));
}

void Scene7_undercity3::Release()
{
}

void Scene7_undercity3::Update()
{
	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());
	ImGui::Text("player_posX : %f\n", GM->player->GetCollider()->GetWorldPos().x);
	ImGui::Text("player_posY : %f\n", GM->player->GetCollider()->GetWorldPos().y);

	ImGui::Text("onFloor : %d\n", GM->player->onFloor);
	ImGui::Text("onWall : %d\n", GM->player->onWall);
	ImGui::Text("onWallside : %d\n", GM->player->onWallSlide);

	//Scene_proto::Update();

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
	Scene_proto::Update();
}

void Scene7_undercity3::LateUpdate()
{
	Scene_proto::LateUpdate();
}

void Scene7_undercity3::Render()
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
	Scene_proto::Render();
}

void Scene7_undercity3::ResizeScreen()
{
	GM->hud->Init();
}