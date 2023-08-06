#include "stdafx.h"
#include "HUD.h"
#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "DamageDisplayManager.h"
#include "EffectManager.h"
#include "redHairRat.h"
#include "orangeHairRat.h"
#include "Scene_proto.h"
#include "Scene6_undercity2.h"

Scene6_undercity2::Scene6_undercity2()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	nextMap = new ObRect();

	tileMap[0]->file = "scene6_undercity2_0.txt";
	tileMap[1]->file = "scene6_undercity2_1.txt";
	tileMap[2]->file = "scene6_undercity2_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	nextMap->pivot = OFFSET_LB;
	nextMap->SetWorldPos(Vector2(2150, 725));
	nextMap->scale = Vector2(100, 100);
	nextMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	nextMap->isFilled = true;

	// 몬스터소환 트리거
	spawnTrigger->pivot = OFFSET_LB;
	spawnTrigger->SetWorldPos(Vector2(1150, 1250));
	spawnTrigger->scale = Vector2(100, 100);
	spawnTrigger->color = Vector4(0.5f, 0.5f, 0.5f, 0.3f);
	spawnTrigger->isFilled = true;

	startPostion = Vector2(1000, 1250);
}

Scene6_undercity2::~Scene6_undercity2()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];
	delete nextMap;
	delete spawnTrigger;
}

void Scene6_undercity2::Init()
{
	GM->player->Init();
	GM->player->SetPosition(startPostion);


}

void Scene6_undercity2::Release()
{
}

void Scene6_undercity2::Update()
{
	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 다음 맵 이동
	if (nextMap->Intersect(GM->player->GetCollider()))
	{
		CleanupBeforeNewMap();
		SCENE->ChangeScene("sc7");
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
	GM->monster->Update();
	GM->player->Update();
	GM->hud->Update();
	Scene_proto::Update();
}

void Scene6_undercity2::LateUpdate()
{
	Scene_proto::LateUpdate();
}

void Scene6_undercity2::Render()
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

void Scene6_undercity2::ResizeScreen()
{
	GM->hud->Init();
}

void Scene6_undercity2::SummonMonster()
{
	GM->monster->SpawnMonster(new redHairRat(), Vector2(1450, 1525));
	GM->monster->SpawnMonster(new orangeHairRat(), Vector2(2000, 1250));
	GM->monster->SpawnMonster(new redHairRat(), Vector2(1450, 1075));
	GM->monster->SpawnMonster(new redHairRat(), Vector2(1850, 975));
	GM->monster->SpawnMonster(new redHairRat(), Vector2(1200, 725));
	GM->monster->SpawnMonster(new orangeHairRat(), Vector2(1500, 725));
	GM->monster->SpawnMonster(new orangeHairRat(), Vector2(1800, 725));
}
