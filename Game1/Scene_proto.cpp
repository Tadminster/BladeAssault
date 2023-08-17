#include "stdafx.h"

#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"

#include "Chest.h"
#include "commonChest.h"
#include "uncommonChest.h"
#include "rareChest.h"

#include "Projectile.h"

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
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];
	delete spawnTrigger;
}

void Scene_proto::Init()
{
}

void Scene_proto::Release()
{
	LIGHT->lightColor.x = 0.5f;
	LIGHT->lightColor.y = 0.5f;
	LIGHT->lightColor.z = 0.5f;

	isSummoned = false;

	if (GM->player->GetState() == State::DIE)
	{
		delete GM->player;
		GM->monster->ClearMonster();
		GM->player = nullptr;
	}
}

void Scene_proto::Update()
{
	if (GM->player->GetState() == State::DIE && PlayerDeadEvent)
	{
		PlayerDeadEvent = false;
		fadeout = 2.0f;
		SCENE->ChangeScene("sc1", 3.0f);
	}

	if (fadeout > 0.0f)
	{
		fadeout -= DELTA;
		LIGHT->lightColor.y = fadeout / 4.0f;
		LIGHT->lightColor.z = fadeout / 4.0f;
	}

	ShowSystemDebug();

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
	HandleTerrainCollision(GM->player);					// �÷��̾�
	
	for (auto& monster : GM->monster->GetEnemy())		// ����
		HandleTerrainCollision(monster);

	for (auto& proj : GM->monster->GetProjectiles())	// ���� �߻�ü
	{
		// ���������� ������� �߻�ü���
		if (proj->isDeleteOnWallSide)
		{
			// ���� �浹���� ����
			HandleTerrainProjectile(proj);
		}
	}

	GM->damageDP->LateUpdate();
}

void Scene_proto::Render()
{
	if (GM->DEBUG_MODE)
		spawnTrigger->Render();
	
	GM->obj->Render();
	GM->item->Render();
	GM->player->Render();
	GM->monster->Render();
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
		creature->onWallSide = true;

		// �������̸�
		if (creature->GetState() == State::JUMP)
			creature->OnWallSlideAction();
		// �������� �ƴϸ�
		else
			creature->GoBack();
	}
	else creature->onWallSide = false;

	// �ٴ�(TILE_FLOOR)�� �ε�������
	if (OnFloor(creature))
	{
		creature->OnFloorAction();
	}
	else creature->onFloor = false;
}

void Scene_proto::HandleTerrainProjectile(Projectile* projectile)
{
	Int2 projectileIndex;
	if (tileMap[2]->WorldPosToTileIdx(projectile->collider->GetWorldPos(), projectileIndex))
	{
		if (tileMap[2]->GetTileState(projectileIndex) == TILE_WALLSIDE)
		{
			projectile->onWallSide = true;
		}
	}
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

	// �ʺ���
	// ������ ����� scene�� key
	const char* itemsBackend[] = { "sc2", "sc3", "sc4", "sc5", "sc6", "sc7", "sc8" };
	// GUI�� ������ �̸�
	const char* itemsFrontend[] = { u8"��ũ��", u8"�����", u8"�ƸӸ�", u8"�����Ƽ1", u8"�����Ƽ2", u8"�����Ƽ3", u8"����ź�� ��" };
	// ���õ� �������� �ε����� ������ ����
	static int item_current_idx = 0; 
	if (ImGui::BeginListBox(u8"�� ����"))
	{
		for (int n = 0; n < IM_ARRAYSIZE(itemsBackend); n++)
		{
			const bool is_selected = (item_current_idx == n);
			if (ImGui::Selectable(itemsFrontend[n], is_selected))
			{
				item_current_idx = n;
				// ���� ������Ʈ ����
				CleanupBeforeNewMap();
				// �� ����
				SCENE->ChangeScene(itemsBackend[item_current_idx]);
			}

			// �޺��� �� �� �ʱ� ��Ŀ�� ����
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();
	}

}





