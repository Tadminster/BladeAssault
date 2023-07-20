#include "stdafx.h"
#include "Monster.h"

Monster::Monster()
{
	collider = new ObRect();
	idle = nullptr;
	run = nullptr;
	jump = nullptr;
	attack = nullptr;
}

Monster::~Monster()
{
	delete collider;
	delete idle;
	delete run;
	delete jump;
	delete attack;
}

void Monster::Init(Vector2 spawnPos)
{
}

void Monster::Update()
{
	// ���� ���¿� ���� �۵�
	if (dmgTaken == MonsterDamageTaken::NORMAL)
	{
		// �÷� ����ȭ
		if (idle->color.x != 0.5)
		{
			idle->color = Vector4(0.5, 0.5, 0.5, 0.5);
			run->color = Vector4(0.5, 0.5, 0.5, 0.5);
			jump->color = Vector4(0.5, 0.5, 0.5, 0.5);
			attack->color = Vector4(0.5, 0.5, 0.5, 0.5);
		}

		// �ٰ�����
		/*if (action == MONSTER_ACTION::RUN)
			trace();*/
	}
	else if (dmgTaken == MonsterDamageTaken::DAMAGED)
	{
		// �̴Ͼ��̳� ����Ʈ �ϰ�� �˹�
		/*if (type == MONSTER_TYPE::MINION || type == MONSTER_TYPE::ELITE)
			knockBack();*/

		// 0.05�� �Ŀ� �븻 ���·�
		if (timeOfDamage + 0.05f < TIMER->GetWorldTime())
		{
			knockBackFactor = 0;
			dmgTaken = MonsterDamageTaken::NORMAL;
		}
	}

	// ������Ʈ
	switch (status)
	{
	case MonsterState::IDLE:
		idle->Update();
		break;
	case MonsterState::RUN:
		run->Update();
		break;
	case MonsterState::JUMP:
		jump->Update();
		break;
	case MonsterState::ATTACK:
		attack->Update();
		break;
	}
	collider->Update();
}

void Monster::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	switch (status)
	{
	case MonsterState::IDLE:
		idle->Render();
		break;
	case MonsterState::RUN:
		run->Render();
		break;
	case MonsterState::JUMP:
		jump->Render();
		break;
	case MonsterState::ATTACK:
		attack->Render();
		break;
	}
}

void Monster::actionsWhenDamaged(Vector4 value)
{
	// ���¸� ������ �������� ����
	dmgTaken = MonsterDamageTaken::DAMAGED;
	// ������ ���� �ð� ���
	timeOfDamage = TIMER->GetWorldTime();
	// ��Ų �÷� ����
	{
		idle->color = Vector4(1, 1, 1, 0.5);
		run->color = Vector4(1, 1, 1, 0.5);
		jump->color = Vector4(1, 1, 1, 0.5);
		attack->color = Vector4(1, 1, 1, 0.5);
	}
	// ü�� ����
	this->hp = max(hp + value.x, 0);
	// �˹� ���
	knockBackFactor = value.y;
}
