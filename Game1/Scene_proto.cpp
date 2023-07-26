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
	// �������� �浹ó��
	HandleTerrainCollision(GM->player);				// �÷��̾�
	for (auto& monster : GM->monster->GetEnemy())	// ����
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
	// ��(TILE_WALL)�� �ε�������
	if (OnWall(creature))
	{
		// �ٴڿ� �پ��ִ� ����
		creature->OnWallAction();
	}
	else creature->onWall = false;

	// ����(TILE_WALLSIDE)�� �ε�������
	if (OnWallside(creature))
	{
		// ���� �پ��ִ� ����
		creature->onWallSlide = true;

		// �������̸�
		if (creature->GetState() == State::JUMP)
			creature->OnWallSlideAction();
		// �������� �ƴϸ�
		else
			creature->GoBack();
	}
	else creature->onWallSlide = false;

	// �ٴ�(TILE_FLOOR)�� �ε�������
	if (OnFloor(creature))
	{
		creature->OnFloorAction();
	}
	else creature->onFloor = false;
}


bool Scene_proto::OnFloor(Creature* creature)
{
	// �ϰ��߿��� �浹 üũ
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
	// TOP �浹 üũ
	if (tileMap[2]->WorldPosToTileIdx(creature->GetHead(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALL)
		{
			creature->GoBack();
			//return true;
		}
	}
	// BOT �浹 üũ
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
	// TOP �浹 üũ
	if (tileMap[2]->WorldPosToTileIdx(creature->GetHead(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALLSIDE)
		{
			return true;
		}
	}
	// BOT �浹 üũ
	if (tileMap[2]->WorldPosToTileIdx(creature->GetFoot(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALLSIDE)
		{
			return true;
		}
	}
	return false;
}



