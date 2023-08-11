#include "stdafx.h"
#include "HUD.h"
#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "DamageDisplayManager.h"
#include "EffectManager.h"
#include "MonsterManager.h"
#include "redHairRat.h"
#include "Scene_proto.h"
#include "Scene4_armory.h"

Scene4_armory::Scene4_armory()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	nextMap = new ObRect();
	previousMap = new ObRect();
	stair = new ObRect();

	tileMap[0]->file = "scene4_armory_0.txt";
	tileMap[1]->file = "scene4_armory_1.txt";
	tileMap[2]->file = "scene4_armory_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	previousMap->pivot = OFFSET_LB;
	previousMap->SetWorldPos(Vector2(500, 550));
	previousMap->scale = Vector2(75, 425);
	previousMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	previousMap->isFilled = true;

	nextMap->pivot = OFFSET_LB;
	nextMap->SetWorldPos(Vector2(3300, 600));
	nextMap->scale = Vector2(75, 100);
	nextMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	nextMap->isFilled = true;

	stair->SetWorldPos(Vector2(3225, 575));
	stair->scale = Vector2(50, 50);
	stair->color = Vector4(0.5, 0.5, 0.5, 0.3);
	stair->isFilled = true;

	startPostion = Vector2(700, 550);
}

Scene4_armory::~Scene4_armory()
{
	delete nextMap;
	delete previousMap;
	delete stair;
}

void Scene4_armory::Init()
{
	GM->player->Init();
	GM->player->SetPosition(startPostion);

	CreateChest(1, Vector2(1100, 550));
	CreateChest(2, Vector2(1600, 550));
	CreateChest(3, Vector2(2100, 550));
}

void Scene4_armory::Release()
{
	Scene_proto::Release();
}

void Scene4_armory::Update()
{
	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 이전 맵 이동
	if (previousMap->Intersect(GM->player->GetCollider()))
	{
		SCENE->ChangeScene("sc3");
	}

	// 다음 맵 이동
	if (nextMap->Intersect(GM->player->GetCollider()))
	{
		CleanupBeforeNewMap();
		SCENE->ChangeScene("sc5");
	}


	if (stair->Intersect(GM->player->GetCollider()))
	{
		if (GM->player->GetDirection() == RIGHT && GM->player->GetState() == State::RUN)
		{
			GM->player->GetCollider()->MoveWorldPos(UP * 200 * DELTA);
		}
	}

	for (auto& map : tileMap)
		map->Update();
	previousMap->Update();
	nextMap->Update();
	stair->Update();

	Scene_proto::Update();
}

void Scene4_armory::LateUpdate()
{
	Scene_proto::LateUpdate();
}

void Scene4_armory::Render()
{
	tileMap[0]->Render();
	tileMap[1]->Render();
	if (GM->DEBUG_MODE)
	{
		tileMap[2]->Render();
		previousMap->Render();
		nextMap->Render();
		stair->Render();
	}

	Scene_proto::Render();
}

void Scene4_armory::ResizeScreen()
{
	GM->hud->Init();
}