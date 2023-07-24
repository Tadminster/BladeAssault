#include "stdafx.h"
#include "Creature.h"
#include "Monster.h"
#include "Projectile.h"
#include "MonsterManager.h"

void MonsterManager::Init()
{
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
	for (auto& monster : enemy)
		ImGui::Text("hp: ", monster->GetHp());

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
					//GM->kill++;
					//GM->player->exp += monster->getExp();
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

void MonsterManager::AddMonster(class Monster* monster)
{
	this->enemy.emplace_back(monster);
}