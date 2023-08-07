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

	// 탄이 플레이어와 충돌하면
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr) { return pr->hasCollideWithPlayer(); }
		),
		projectiles.end()
	);

	// 탄이 일정거리 이상 벗어났으면 삭제
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr) { return pr->hasTraveledTooFar(); }
		),
		projectiles.end()
	);

	// 적 업데이트
	for (auto& enemy : this->enemy)
		enemy->Update();
	// 탄 업데이트
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
	// 몬스터 위치 설정
	monster->GetCollider()->SetWorldPos(pos);
	monster->Init();
	// 몬스터를 벡터에 추가
	this->enemy.emplace_back(monster);
}

void MonsterManager::ShowMonsterStat()
{
	if (!ImGui::CollapsingHeader(u8"몬스터"))
		return;

	for (auto& monster : enemy)
	{
		ImGui::Text("[%s]"			, monster->GetName().c_str());
		ImGui::Text("hp: %d"		, monster->GetHp());
		ImGui::Text("damage: %d"	, monster->GetDamage());
		ImGui::Text("range: %d\n\n"	, monster->GetRange());
	}
}
