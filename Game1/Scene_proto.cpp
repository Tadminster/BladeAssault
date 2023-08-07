#include "stdafx.h"

#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"

#include "Chest.h"
#include "commonChest.h"
#include "uncommonChest.h"
#include "rareChest.h"

#include "HUD.h"
#include "MonsterManager.h"
#include "DamageDisplayManager.h"
#include "EffectManager.h"
#include "ItemManager.h"
#include "ObjectManager.h"

#include "Scene_proto.h"

Scene_proto::Scene_proto()
{
	spawnTrigger = new ObRect();
}

Scene_proto::~Scene_proto()
{
	//for (int i = 0; i < 3; i++)
		//delete[] tileMap[i];
}

void Scene_proto::Init()
{
}

void Scene_proto::Release()
{
}

void Scene_proto::Update()
{
	localtime += DELTA;
	spawnTrigger->Update();
	GM->item->Update();
	GM->fx->Update();
	GM->obj->Update();
	GM->monster->Update();
	GM->player->Update();
	GM->hud->Update();
	GM->damageDP->Update();
}

void Scene_proto::LateUpdate()
{
	// 지형지물 충돌처리
	HandleTerrainCollision(GM->player);				// 플레이어
	for (auto& monster : GM->monster->GetEnemy())	// 몬스터
		HandleTerrainCollision(monster);

	GM->damageDP->LateUpdate();
}

void Scene_proto::Render()
{
	if (GM->DEBUG_MODE)
		spawnTrigger->Render();
	
	GM->obj->Render();
	GM->item->Render();
	GM->monster->Render();
	GM->player->Render();
	GM->fx->Render();
	GM->damageDP->Render();
	GM->hud->Render();
}

void Scene_proto::ResizeScreen()
{
}

void Scene_proto::HandleTerrainCollision(Creature* creature)
{
	// 벽(TILE_WALL)과 부딪쳤으면
	if (OnWall(creature))
	{
		// 바닥에 붙어있는 상태
		creature->OnWallAction();
	}
	else creature->onWall = false;

	// 벽면(TILE_WALLSIDE)과 부딪쳤으면
	if (OnWallside(creature))
	{
		// 벽에 붙어있는 상태
		creature->onWallSlide = true;

		// 점프중이면
		if (creature->GetState() == State::JUMP)
			creature->OnWallSlideAction();
		// 점프중이 아니면
		else
			creature->GoBack();
	}
	else creature->onWallSlide = false;

	// 바닥(TILE_FLOOR)과 부딪쳤으면
	if (OnFloor(creature))
	{
		creature->OnFloorAction();
	}
	else creature->onFloor = false;
}


bool Scene_proto::OnFloor(Creature* creature)
{
	// 하강중에만 충돌 체크
	if (creature->isLanding)
	{
		Int2 playerlndex;
		if (tileMap[2]->WorldPosToTileIdx(creature->GetFoot(), playerlndex))
		{
			if (tileMap[2]->GetTileState(playerlndex) == TILE_FLOOR)
			{
				return true;
			}
		}
	}
	return false;
}

bool Scene_proto::OnWall(Creature* creature)
{
	Int2 playerlndex;
	// TOP 충돌 체크
	if (tileMap[2]->WorldPosToTileIdx(creature->GetHead(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALL)
		{
			creature->GoBack();
			//return true;
		}
	}
	// BOT 충돌 체크
	if (tileMap[2]->WorldPosToTileIdx(creature->GetFoot(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALL)
		{
			return true;
		}
	}

	return false;
}

bool Scene_proto::OnWallside(Creature* creature)
{
	Int2 playerlndex;
	// TOP 충돌 체크
	if (tileMap[2]->WorldPosToTileIdx(creature->GetHead(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALLSIDE)
		{
			return true;
		}
	}
	// BOT 충돌 체크
	if (tileMap[2]->WorldPosToTileIdx(creature->GetFoot(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALLSIDE)
		{
			return true;
		}
	}
	return false;
}

void Scene_proto::SummonMonster()
{
}

void Scene_proto::CreateChest(int type, Vector2 pos)
{
	Chest* chest = nullptr;

	// 랜덤으로 상자 생성을 위한 초기화
	if (type == 0)
	{
		type = RANDOM->Int(1, 3);
	}
	
	if (type == 1)
		chest = new commonChest();
	else if (type == 2)
		chest = new uncommonChest();
	else if (type == 3)
		chest = new rareChest();

	chest->SetPosition(pos);
	GM->obj->AddChest(chest);
}

void Scene_proto::CleanupBeforeNewMap()
{
	// 다음맵으로 넘어가기전 불필요한 Object들을 삭제
	
	// 몬스터 삭제
	GM->monster->ClearMonster();

	// 아이템 삭제
	GM->item->ActivateAllItem();

	// 상자 삭제
	GM->obj->ClearChests();
}

void Scene_proto::ShowSystemDebug()
{
	if (!ImGui::CollapsingHeader(u8"시스템"))
		return;


}





