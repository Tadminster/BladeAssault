#include "stdafx.h"
#include "HUD.h"
#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "Scene_proto.h"

Scene_proto::Scene_proto()
{
	tileMap[0] = nullptr;
	tileMap[1] = nullptr;
	tileMap[2] = nullptr;
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
}

void Scene_proto::LateUpdate()
{
	// 지형지물 충돌처리
	HandleTerrainCollision(GM->player);				// 플레이어
	for (auto& monster : GM->monster->GetEnemy())	// 몬스터
		HandleTerrainCollision(monster);
}

void Scene_proto::Render()
{
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



