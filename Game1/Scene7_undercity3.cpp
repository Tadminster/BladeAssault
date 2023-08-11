#include "stdafx.h"
#include "HUD.h"
#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "DamageDisplayManager.h"
#include "EffectManager.h"
#include "Scene_proto.h"
#include "Scene7_undercity3.h"

Scene7_undercity3::Scene7_undercity3()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	nextMap = new ObRect();

	tileMap[0]->file = "scene7_undercity3_0.txt";
	tileMap[1]->file = "scene7_undercity3_1.txt";
	tileMap[2]->file = "scene7_undercity3_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	nextMap->pivot = OFFSET_LB;
	nextMap->SetWorldPos(Vector2(4375, 825));
	nextMap->scale = Vector2(100, 100);
	nextMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	nextMap->isFilled = true;

	// 몬스터소환 트리거
	spawnTrigger->pivot = OFFSET_LB;
	spawnTrigger->SetWorldPos(Vector2(1450, 825));
	spawnTrigger->scale = Vector2(100, 300);
	spawnTrigger->color = Vector4(0.5f, 0.5f, 0.5f, 0.3f);
	spawnTrigger->isFilled = true;

	startPostion = Vector2(925, 825);
}

Scene7_undercity3::~Scene7_undercity3()
{
	delete nextMap;
}

void Scene7_undercity3::Init()
{
	GM->player->Init();
	GM->player->SetPosition(startPostion);

	CreateChest(0, Vector2(3125, 825));
}

void Scene7_undercity3::Release()
{
	Scene_proto::Release();
}

void Scene7_undercity3::Update()
{
	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 다음 맵 이동
	if (nextMap->Intersect(GM->player->GetCollider()))
	{
		CleanupBeforeNewMap();
		SCENE->ChangeScene("sc8");
	}

	// 몬스터 소환
	if (spawnTrigger->Intersect(GM->player->GetCollider()))
	{
		// 몬스터가 소환된 적이 없다면
		if (!isSummoned)
		{
			isSummoned = true;
			SummonMonster();
		}
	}


	for (auto& map : tileMap)
		map->Update();
	nextMap->Update();
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
	Scene_proto::Render();
}

void Scene7_undercity3::ResizeScreen()
{
	GM->hud->Init();
}

void Scene7_undercity3::SummonMonster()
{
	GM->monster->SpawnMonster("redHairRat", Vector2(1350, 1050));
	GM->monster->SpawnMonster("greenHairRat", Vector2(1850, 1125));
	GM->monster->SpawnMonster("greenHairRat", Vector2(2300, 1125));
	GM->monster->SpawnMonster("redHairRat", Vector2(1900, 825));
	GM->monster->SpawnMonster("redHairRat", Vector2(2000, 825));
	GM->monster->SpawnMonster("redHairRat", Vector2(2100, 825));
	GM->monster->SpawnMonster("orangeHairRat", Vector2(2200, 825));
	GM->monster->SpawnMonster("orangeHairRat", Vector2(2300, 825));

	GM->monster->SpawnMonster("greenHairRat", Vector2(3625, 1125));
	GM->monster->SpawnMonster("greenHairRat", Vector2(3825, 1125));
	GM->monster->SpawnMonster("redHairRat", Vector2(3650, 825));
	GM->monster->SpawnMonster("redHairRat", Vector2(3750, 825));
	GM->monster->SpawnMonster("orangeHairRat", Vector2(3850, 825));
	GM->monster->SpawnMonster("orangeHairRat", Vector2(3900, 825));
}
