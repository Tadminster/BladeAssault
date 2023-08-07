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
	// �������� �浹ó��
	HandleTerrainCollision(GM->player);				// �÷��̾�
	for (auto& monster : GM->monster->GetEnemy())	// ����
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

void Scene_proto::SummonMonster()
{
}

void Scene_proto::CreateChest(int type, Vector2 pos)
{
	Chest* chest = nullptr;

	// �������� ���� ������ ���� �ʱ�ȭ
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
	// ���������� �Ѿ���� ���ʿ��� Object���� ����
	
	// ���� ����
	GM->monster->ClearMonster();

	// ������ ����
	GM->item->ActivateAllItem();

	// ���� ����
	GM->obj->ClearChests();
}

void Scene_proto::ShowSystemDebug()
{
	if (!ImGui::CollapsingHeader(u8"�ý���"))
		return;


}





