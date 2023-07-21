#include "stdafx.h"
#include "Player.h"
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
	ImGui::Text("MonsterState: %d\n", state);

	Vector2 target = GM->player->GetCollider()->GetWorldPos();
	
	// ���� ���
	if (target.x - collider->GetWorldPos().x > 0)
		dir = RIGHT;
	else 
		dir = LEFT;

	// ��Ų ���� ����
	if (dir == LEFT)
	{
		idle->reverseLR = true;
		run->reverseLR = true;
		jump->reverseLR = true;
		attack->reverseLR = true;
	}
	else if (dir == RIGHT)
	{
		idle->reverseLR = false;
		run->reverseLR = false;
		jump->reverseLR = false;
		attack->reverseLR = false;
	}

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
		//if (type == MONSTER_TYPE::MINION || type == MONSTER_TYPE::ELITE)
		knockBack();

		// 0.05�� �Ŀ� �븻 ���·�
		if (timeOfDamage + 0.05f < TIMER->GetWorldTime())
		{
			knockBackFactor = 0;
			dmgTaken = MonsterDamageTaken::NORMAL;
		}
	}

	float distance = Vector2::Distance(collider->GetWorldPos(), GM->player->GetCollider()->GetWorldPos());
	ImGui::Text("distance: %f\n", distance);


	
	if (state == MonsterState::IDLE)
	{
		// IDLE -> ATTACK
		if (distance < 200)
		{
			if (isAttackCooldown())
			{
				state = MonsterState::ATTACK;
			}
		}
		// IDLE -> RUN
		else if (distance < app.GetHalfWidth())
		{
			state = MonsterState::RUN;
		}
	}
	else if (state == MonsterState::RUN)
	{
		// RUN -> ATTACK
		if (distance < 100)
		{
			if (isAttackCooldown())
			{
				state = MonsterState::ATTACK;
			}
		}

		collider->MoveWorldPos(dir * speed * DELTA);
	}
	else if (state == MonsterState::JUMP)
	{

	}
	else if (state == MonsterState::ATTACK)
	{
		// ���� �����ӿ� �����ϸ� �߻�
		if (attack->frame.x == attackFrame && realAttack)
		{
			realAttack = false;
			Attack();
		}

		// ATTACK -> IDLE
		if (attack->frame.x == attack->maxFrame.x - 1)
		{
			state = MonsterState::IDLE;
		}
	}

	// ������Ʈ
	switch (state)
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

	switch (state)
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

bool Monster::isAttackCooldown()
{
	static float lastShotTime = 0;
	static float timeSinceLastTime = 0;

	float currentTime = TIMER->GetWorldTime();
	float elapsedTime = currentTime - lastShotTime;

	if (elapsedTime >= timeSinceLastTime)
	{
		attack->frame.x = 0;
		realAttack = true;


		// ���Ӱ��
		lastShotTime = currentTime;
		timeSinceLastTime = 1.0f / attackSpeed;

		return true;
	}

	return false;
}

void Monster::Attack()
{


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

void Monster::knockBack()
{
	// �˹� ���� ���
	Vector2 knockBackDir; 
	if (GM->player->GetCollider()->GetWorldPos().x < this->collider->GetWorldPos().x)
		knockBackDir = RIGHT;
	else
		knockBackDir = LEFT;

	this->collider->MoveWorldPos(knockBackDir * knockBackFactor * DELTA);
}