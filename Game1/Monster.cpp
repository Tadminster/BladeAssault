#include "stdafx.h"
#include "Creature.h"
#include "Player.h"
#include "Monster.h"

Monster::Monster()
{
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

//void Monster::Init(Vector2 spawnPos)
//{
//}

void Monster::Update()
{
	ImGui::Text("MonsterState: %d\n", CurrentState);
	lastPos = collider->GetWorldPos();

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
	int distanceX = GM->player->GetCollider()->GetWorldPos().x - collider->GetWorldPos().x;
	int distanceY = GM->player->GetCollider()->GetWorldPos().y - collider->GetWorldPos().y - 50;
	int distanceX_abs = abs(distanceX);
	int distanceY_abs = abs(distanceY);
	ImGui::Text("distanceX: %d\n", distanceX);
	ImGui::Text("distanceY: %d\n", distanceY);
	ImGui::Text("distanceX(abs): %d\n", distanceX_abs);
	ImGui::Text("distanceY(abs): %d\n", distanceY_abs);



	if (CurrentState == State::IDLE)
	{
		// IDLE -> ATTACK
		if (distanceX_abs < 200)
		{
			if (distanceY_abs < 100)
			{
				// 플레이어와 비슷한 높이에 있다면 공격시도
				if (isAttackCooldown())
				{
					CurrentState = State::ATTACK;
				}
			}
			else
			{
				// 플레이어가 더 높이 있다면 점프
				if (distanceY > 0)
				{

				}
				// 플레이어가 더 낮게 있다면 하강
				else if (distanceY < 0)
				{

				}
			}
		}
		// IDLE -> RUN
		else if (distanceX_abs < app.GetHalfWidth())
		{
			CurrentState = State::RUN;
		}
	}
	else if (CurrentState == State::RUN)
	{
		// RUN -> ATTACK
		if (distanceX_abs < 100)
		{
			if (isAttackCooldown())
			{
				CurrentState = State::ATTACK;
			}
		}

		collider->MoveWorldPos(dir * moveSpeed * DELTA);
	}
	else if (CurrentState == State::JUMP)
	{

	}
	else if (CurrentState == State::ATTACK)
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
			CurrentState = State::IDLE;
		}
	}

	// 중력
	if (!onWall && !onFloor)
	{
		gravity += 1500.0f * DELTA;
		collider->MoveWorldPos(DOWN * gravity * DELTA);
	}

	// 업데이트
	shadow->Update();
	switch (CurrentState)
	{
	case State::IDLE:
		idle->Update();
		break;
	case State::RUN:
		run->Update();
		break;
	case State::JUMP:
		jump->Update();
		break;
	case State::ATTACK:
		attack->Update();
		break;
	}
	collider->Update();
}

void Monster::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	shadow->Render();
	switch (CurrentState)
	{
	case State::IDLE:
		idle->Render();
		break;
	case State::RUN:
		run->Render();
		break;
	case State::JUMP:
		jump->Render();
		break;
	case State::ATTACK:
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