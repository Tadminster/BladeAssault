#include "stdafx.h"
#include "Creature.h"
#include "Monster.h"
#include "redHairRat.h"
#include "orangeHairRat.h"
#include "greenHairRat.h"
#include "ratmotan.h"
#include "shockwaveGenerator.h"
#include "Projectile.h"

#include <excpt.h>

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
	monsters.erase(
		std::remove_if
		(
			monsters.begin(),
			monsters.end(),
			[](Monster* monster)
			{
				if (monster->isDead())
				{
					delete monster;
					return true;
				}
				else return false;
			}
		),
		monsters.end()
	);

	// ź�� �÷��̾�� �浹�ϸ�
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr) 
			{ 
				if (pr->hasCollideWithPlayer())
				{
					delete pr;
					return true;
				}
				else return false;
			}
		),
		projectiles.end()
	);


	// ź�� ��(wallside)�� �浹������
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr)
			{
				if (pr->hasCollideWithWallSide())
				{
					delete pr;
					return true;
				}
				else return false;
			}
		),
		projectiles.end()
	);

	// ź�� �����Ÿ� �̻� ������� ����
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr) 
			{
				if (pr->hasTraveledTooFar())
				{
					delete pr;
					return true;
				}
				else return false;
			}
		),
		projectiles.end()
	);


	// ź ������Ʈ
	for (auto& projectiles : projectiles)
		projectiles->Update();

	// �� ������Ʈ
	for (auto& monster : this->monsters)
		monster->Update();
}

void MonsterManager::LateUpdate()
{
}

void MonsterManager::Render()
{
	for (auto& monster : this->monsters)
		monster->Render();

	for (auto& projectiles : projectiles)
		projectiles->Render();
}

void MonsterManager::SpawnMonster(string&& monsterName, Vector2 pos, Vector2 dir)
{
	Monster* monster = nullptr;
	if (monsterName == "redHairRat")
	{
		monster = new redHairRat();
	}
	else if (monsterName == "orangeHairRat")
	{
		monster = new orangeHairRat();
	}
	else if (monsterName == "greenHairRat")
	{
		monster = new greenHairRat();
	}
	else if (monsterName == "ratmotan")
	{
		monster = new ratmotan();
	}
	else if (monsterName == "shockwaveGenerator")
	{
		monster = new shockwaveGenerator();
	}
	else
	{
		cout << "���� �̸��� �߸��Ǿ����ϴ�." << endl;
		return;
	}

	// ���� ��ġ ����
	monster->GetCollider()->SetWorldPos(pos);
	monster->SetDirection(dir);
	// ���͸� ���Ϳ� �߰�
	this->monsters.emplace_back(monster);
}

void MonsterManager::ClearMonster()
{
	for (auto& monster : this->monsters)
		monster->kill();
}

void MonsterManager::ShowMonsterStat()
{
	if (!ImGui::CollapsingHeader(u8"����"))
		return;

	for (auto& monster : monsters)
	{
		ImGui::Text("[%s]"			, monster->GetName().c_str());
		ImGui::Text("hp: %d"		, monster->GetHp());
		ImGui::Text("damage: %d"	, monster->GetDamage());
		ImGui::Text("posX: %f"		, monster->GetPosition().x);
		ImGui::Text("posY: %f"		, monster->GetPosition().y);
		ImGui::Text("\n");
	}
}
