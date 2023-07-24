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

//void Monster::Init(Vector2 spawnPos)
//{
//}

void Monster::Update()
{
	ImGui::Text("MonsterState: %d\n", state);
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


	
	if (state == MonsterState::IDLE)
	{
		// IDLE -> ATTACK
		if (distanceX_abs < 200)
		{
			if (distanceY_abs < 100)
			{
				// 플레이어와 비슷한 높이에 있다면 공격시도
				if (isAttackCooldown())
				{
					state = MonsterState::ATTACK;
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
			state = MonsterState::RUN;
		}
	}
	else if (state == MonsterState::RUN)
	{
		// RUN -> ATTACK
		if (distanceX_abs < 100)
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

	// 중력
	if (!onWall && !onFloor)
	{
		gravity += 1500.0f * DELTA;
		collider->MoveWorldPos(DOWN * gravity * DELTA);
	}

	// 업데이트
	shadow->Update();
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

	shadow->Render();
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

void Monster::OnFloorAction()
{
	onFloor = true;
	gravity = 0;
}

void Monster::OnWallAction()
{
	onWall = true;
	gravity = 0;
}

void Monster::OnWallSlideAction()
{
	collider->SetWorldPosX(lastPos.x);
	collider->Update();
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

void Monster::GoBack()
{
	gravity = 0;
	collider->SetWorldPos(lastPos);
	collider->Update();
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

Vector2 Monster::GetFoot()
{
	//29 38
	//Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
	//Utility::IntersectRectRect()

	//                              중앙에서나갈위치    발중앙위치 보정
	return collider->GetWorldPos() + (dir + DOWN) * Vector2(collider->scale.x * 0.5f, collider->scale.y * 0.5f);
}

Vector2 Monster::GetHead()
{
	//29 38
	//Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
	//Utility::IntersectRectRect()

	//                              중앙에서나갈위치    발중앙위치 보정
	return collider->GetWorldPos() + (dir + UP) * Vector2(collider->scale.x * 0.5f, collider->scale.y * 0.5f);
}
