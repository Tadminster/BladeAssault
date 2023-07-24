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
					//GM->kill++;
					//GM->player->exp += monster->getExp();
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

void MonsterManager::AddMonster(class Monster* monster)
{
	this->enemy.emplace_back(monster);
}