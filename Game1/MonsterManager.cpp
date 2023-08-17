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
	// 모든 몬스터를 추가
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

	// 체력이 0 이하인 몬스터 삭제
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

	// 탄이 플레이어와 충돌하면
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


	// 탄이 벽(wallside)과 충돌했으면
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

	// 탄이 일정거리 이상 벗어났으면 삭제
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


	// 탄 업데이트
	for (auto& projectiles : projectiles)
		projectiles->Update();

	// 적 업데이트
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
		cout << "몬스터 이름이 잘못되었습니다." << endl;
		return;
	}

	// 몬스터 위치 설정
	monster->GetCollider()->SetWorldPos(pos);
	monster->SetDirection(dir);
	// 몬스터를 벡터에 추가
	this->monsters.emplace_back(monster);
}

void MonsterManager::ClearMonster()
{
	for (auto& monster : this->monsters)
		monster->kill();
}

void MonsterManager::ShowMonsterStat()
{
	if (!ImGui::CollapsingHeader(u8"몬스터"))
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
