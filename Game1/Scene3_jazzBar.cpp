#include "stdafx.h"
#include "HUD.h"
#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "DamageDisplayManager.h"
#include "ObjectManager.h"
#include "EffectManager.h"
#include "ItemManager.h"
#include "redHairRat.h"
#include "orangeHairRat.h"
#include "greenHairRat.h"
#include "Scene_proto.h"
#include "Scene3_jazzBar.h"

Scene3_jazzBar::Scene3_jazzBar()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	for (int i = 0; i < 2; i++)
		nextMap[i] = new ObRect();
	//spawnTrigger = new ObRect();
	stairLeft = new ObRect();
	stairRight = new ObRect();

	tileMap[0]->file = "scene3_jazzbar_0.txt";
	tileMap[1]->file = "scene3_jazzbar_1.txt";
	tileMap[2]->file = "scene3_jazzbar_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	nextMap[0]->pivot = OFFSET_LB;
	nextMap[1]->pivot = OFFSET_LB;
	nextMap[0]->SetWorldPos(Vector2(4225, 1800));
	nextMap[1]->SetWorldPos(Vector2(4225, 1100));
	for (int i = 0; i < 2; i++)
	{
		nextMap[i]->scale = Vector2(75, 425);
		nextMap[i]->color = Vector4(0.5f, 0.5f, 0.5f, 0.3f);
		nextMap[i]->isFilled = true;
	}

	// 몬스터소환 트리거
	spawnTrigger->pivot = OFFSET_LB;
	spawnTrigger->SetWorldPos(Vector2(3000, 1800));
	spawnTrigger->scale = Vector2(100, 100);
	spawnTrigger->color = Vector4(0.5f, 0.5f, 0.5f, 0.3f);
	spawnTrigger->isFilled = true;

	// 계단(왼쪽)
	stairLeft->pivot = OFFSET_LB;
	stairLeft->SetWorldPos(Vector2(3000, 1150));
	stairLeft->scale = Vector2(50, 50);
	stairLeft->color = Vector4(0.5f, 0.5f, 0.5f, 0.3f);
	stairLeft->isFilled = true;

	// 계단(오른쪽)
	stairRight->pivot = OFFSET_LB;
	stairRight->SetWorldPos(Vector2(3975, 1100));
	stairRight->scale = Vector2(50, 50);
	stairRight->color = Vector4(0.5f, 0.5f, 0.5f, 0.3f);
	stairRight->isFilled = true;

	startPostion = Vector2(2820, 1800);
}

Scene3_jazzBar::~Scene3_jazzBar()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];

	for (int i = 0; i < 2; i++)
		delete nextMap[i];
	delete spawnTrigger;
	delete stairLeft;
}

void Scene3_jazzBar::Init()
{
	GM->player->SetPosition(startPostion);

}

void Scene3_jazzBar::Release()
{
}

void Scene3_jazzBar::Update()
{
	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());\

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 다음	맵으로 이동
	for (auto& next : nextMap)
	{
		if (next->Intersect(GM->player->GetCollider()))
		{
			
			CleanupBeforeNewMap();
			SCENE->ChangeScene("sc4");
		}
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

	// 계단(왼쪽)
	if (stairLeft->Intersect(GM->player->GetCollider()))
	{
		if (GM->player->GetDirection() == LEFT && GM->player->GetState() == State::RUN)
		{
			GM->player->onWall = true;
			GM->player->gravity = 0;
			GM->player->GetCollider()->MoveWorldPos(UP * 200 * DELTA);
		}
	}

	// 계단(오른쪽)
	if (stairRight->Intersect(GM->player->GetCollider()))
	{
		if (GM->player->GetDirection() == LEFT && GM->player->GetState() == State::RUN)
		{
			GM->player->onWall = true;
			GM->player->gravity = 0;
			GM->player->GetCollider()->MoveWorldPos(UP * 200 * DELTA);
		}
	}


	for (auto& map : tileMap)
		map->Update();
	nextMap[0]->Update();
	nextMap[1]->Update();
	stairLeft->Update();
	stairRight->Update();

	Scene_proto::Update();
}

void Scene3_jazzBar::LateUpdate()
{
	Scene_proto::LateUpdate();
}

void Scene3_jazzBar::Render()
{
	tileMap[0]->Render();
	tileMap[1]->Render();
	if (GM->DEBUG_MODE)
	{
		tileMap[2]->Render();
		nextMap[0]->Render();
		nextMap[1]->Render();
		stairLeft->Render();
		stairRight->Render();
	}

	Scene_proto::Render();

}

void Scene3_jazzBar::ResizeScreen()
{
	GM->hud->Init();
}

void Scene3_jazzBar::SummonMonster()
{
	GM->monster->SpawnMonster(new redHairRat(), Vector2(3500, 2000));
	GM->monster->SpawnMonster(new orangeHairRat(), Vector2(3600, 2000));
	GM->monster->SpawnMonster(new greenHairRat(), Vector2(3700, 2000));
}
