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
#include "Scene5_undercity1.h"

Scene5_undercity1::Scene5_undercity1()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	nextMap = new ObRect();
	//spawnTrigger = new ObRect();

	tileMap[0]->file = "scene5_undercity1_0.txt";
	tileMap[1]->file = "scene5_undercity1_1.txt";
	tileMap[2]->file = "scene5_undercity1_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	nextMap->pivot = OFFSET_LB;
	nextMap->SetWorldPos(Vector2(2175, 700));
	nextMap->scale = Vector2(100, 100);
	nextMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	nextMap->isFilled = true;

	// 몬스터소환 트리거
	spawnTrigger->pivot = OFFSET_LB;
	spawnTrigger->SetWorldPos(Vector2(1150, 1200));
	spawnTrigger->scale = Vector2(125, 100);
	spawnTrigger->color = Vector4(0.5f, 0.5f, 0.5f, 0.3f);
	spawnTrigger->isFilled = true;

	startPostion = Vector2(850, 2950);
}

Scene5_undercity1::~Scene5_undercity1()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];
	delete nextMap;
}

void Scene5_undercity1::Init()
{
	GM->player->Init();
	GM->player->SetPosition(startPostion);


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

	//Scene_proto::Update();

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 다음 맵 이동
	if (nextMap->Intersect(GM->player->GetCollider()))
	{
		CleanupBeforeNewMap();
		SCENE->ChangeScene("sc6");
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
	Scene_proto::Render();
}

void Scene5_undercity1::ResizeScreen()
{
	GM->hud->Init();
}

void Scene5_undercity1::SummonMonster()
{
	GM->monster->SpawnMonster(new orangeHairRat(), Vector2(750, 900));
	GM->monster->SpawnMonster(new redHairRat(), Vector2(1000, 900));
	GM->monster->SpawnMonster(new redHairRat(), Vector2(1200, 900));
	GM->monster->SpawnMonster(new redHairRat(), Vector2(1500, 900));
	GM->monster->SpawnMonster(new redHairRat(), Vector2(1750, 900));
	GM->monster->SpawnMonster(new orangeHairRat(), Vector2(2000, 900));
}
