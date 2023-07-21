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
	
	// 방향 계산
	if (target.x - collider->GetWorldPos().x > 0)
		dir = RIGHT;
	else 
		dir = LEFT;

	// 스킨 방향 설정
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

	// 몬스터 상태에 따른 작동
	if (dmgTaken == MonsterDamageTaken::NORMAL)
	{
		// 컬러 정상화
		if (idle->color.x != 0.5)
		{
			idle->color = Vector4(0.5, 0.5, 0.5, 0.5);
			run->color = Vector4(0.5, 0.5, 0.5, 0.5);
			jump->color = Vector4(0.5, 0.5, 0.5, 0.5);
			attack->color = Vector4(0.5, 0.5, 0.5, 0.5);
		}

		// 다가가기
		/*if (action == MONSTER_ACTION::RUN)
			trace();*/
	}
	else if (dmgTaken == MonsterDamageTaken::DAMAGED)
	{
		// 미니언이나 엘리트 일경우 넉백
		//if (type == MONSTER_TYPE::MINION || type == MONSTER_TYPE::ELITE)
		knockBack();

		// 0.05초 후에 노말 상태로
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
		// 공격 프레임에 도달하면 발사
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

	// 업데이트
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


		// 공속계산
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
	// 상태를 데미지 받음으로 변경
	dmgTaken = MonsterDamageTaken::DAMAGED;
	// 데미지 받은 시간 기록
	timeOfDamage = TIMER->GetWorldTime();
	// 스킨 컬러 변경
	{
		idle->color = Vector4(1, 1, 1, 0.5);
		run->color = Vector4(1, 1, 1, 0.5);
		jump->color = Vector4(1, 1, 1, 0.5);
		attack->color = Vector4(1, 1, 1, 0.5);
	}
	// 체력 감소
	this->hp = max(hp + value.x, 0);
	// 넉백 계수
	knockBackFactor = value.y;
}

void Monster::knockBack()
{
	// 넉백 방향 계산
	Vector2 knockBackDir; 
	if (GM->player->GetCollider()->GetWorldPos().x < this->collider->GetWorldPos().x)
		knockBackDir = RIGHT;
	else
		knockBackDir = LEFT;

	this->collider->MoveWorldPos(knockBackDir * knockBackFactor * DELTA);
}