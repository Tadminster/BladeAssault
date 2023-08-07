#include "stdafx.h"
#include "Creature.h"
#include "Monster.h"
#include "redHairRat.h"
#include "orangeHairRat.h"
#include "greenHairRat.h"
#include "ratmotan.h"
#include "Projectile.h"
#include "MonsterManager.h"

void MonsterManager::Init()
{
	// ��� ���͸� �߰�
	monsterList.emplace("redHairRat", new redHairRat());
	monsterList.emplace("orangeHairRat", new orangeHairRat());
	monsterList.emplace("greenHairRat", new greenHairRat());
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
	ShowMonsterStat();

	// ü���� 0 ������ ���� ����
	enemy.erase(
		std::remove_if
		(
			enemy.begin(),
			enemy.end(),
			[](Monster* monster)
			{ 
				if (monster->isDead())
				{
					delete monster;
					return true;
				}
				else false;
			}
		),
		enemy.end()
	);

	// ź�� �÷��̾�� �浹�ϸ�
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr) { return pr->hasCollideWithPlayer(); }
		),
		projectiles.end()
	);

	// ź�� �����Ÿ� �̻� ������� ����
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr) { return pr->hasTraveledTooFar(); }
		),
		projectiles.end()
	);

	// �� ������Ʈ
	for (auto& enemy : this->enemy)
		enemy->Update();
	// ź ������Ʈ
	for (auto& projectiles : projectiles)
		projectiles->Update();
}

void MonsterManager::LateUpdate()
{
}

void MonsterManager::Render()
{
	for (auto& enemy : this->enemy)
		enemy->Render();

	for (auto& projectiles : projectiles)
		projectiles->Render();
}

void MonsterManager::SpawnMonster(class Monster* monster, Vector2 pos)
{
	// ���� ��ġ ����
	monster->GetCollider()->SetWorldPos(pos);
	monster->Init();
	// ���͸� ���Ϳ� �߰�
	this->enemy.emplace_back(monster);
}

void MonsterManager::ShowMonsterStat()
{
	if (!ImGui::CollapsingHeader(u8"����"))
		return;

	for (auto& monster : enemy)
	{
		ImGui::Text("[%s]"			, monster->GetName().c_str());
		ImGui::Text("hp: %d"		, monster->GetHp());
		ImGui::Text("damage: %d"	, monster->GetDamage());
		ImGui::Text("range: %d\n\n"	, monster->GetRange());
	}
}
