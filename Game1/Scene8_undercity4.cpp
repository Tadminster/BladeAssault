#include "stdafx.h"
#include "HUD.h"
#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "DamageDisplayManager.h"
#include "EffectManager.h"
#include "ratmotan.h"
#include "Scene_proto.h"
#include "Scene8_undercity4.h"

Scene8_undercity4::Scene8_undercity4()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	nextMap = new ObRect();

	tileMap[0]->file = "scene8_undercity4_0.txt";
	tileMap[1]->file = "scene8_undercity4_1.txt";
	tileMap[2]->file = "scene8_undercity4_2.txt";

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
	spawnTrigger->SetWorldPos(Vector2(1450, 1100));
	spawnTrigger->scale = Vector2(50, 250);
	spawnTrigger->color = Vector4(0.5f, 0.5f, 0.5f, 0.3f);
	spawnTrigger->isFilled = true;

	startPostion = Vector2(875, 1100);
}

Scene8_undercity4::~Scene8_undercity4()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];
	delete nextMap;
}

void Scene8_undercity4::Init()
{
	GM->player->Init();
	GM->player->SetPosition(startPostion);
}

void Scene8_undercity4::Release()
{
}

void Scene8_undercity4::Update()
{
	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 다음 맵 이동
	if (nextMap->Intersect(GM->player->GetCollider()))
	{
		CleanupBeforeNewMap();
		SCENE->ChangeScene("sc2");
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

void Scene8_undercity4::LateUpdate()
{
	Scene_proto::LateUpdate();
}

void Scene8_undercity4::Render()
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

void Scene8_undercity4::ResizeScreen()
{
	GM->hud->Init();
}

void Scene8_undercity4::SummonMonster()
{
	// BOSS
	GM->monster->SpawnMonster("ratmotan", Vector2(3200, 650));
}
