#include "stdafx.h"
#include "Creature.h"
#include "Player.h"
#include "DamageDisplayManager.h"
#include "EffectManager.h"
#include "Monster.h"

Monster::Monster()
{
	ui_frame_hp = new ObImage(L"ui_frame_mosterHp.png");
	ui_gauge_hp = new ObImage(L"ui_gauge_monsterHp.png");

	spawn = new ObImage(L"monster_spawn.png");

	ui_frame_hp->pivot = OFFSET_L;
	ui_frame_hp->SetParentRT(*collider);
	ui_frame_hp->scale.x = ui_frame_hp->imageSize.x * 0.2f;
	ui_frame_hp->scale.y = ui_frame_hp->imageSize.y * 0.3f;

	ui_gauge_hp->pivot = OFFSET_L;
	ui_gauge_hp->SetParentRT(*collider);
	ui_gauge_hp->scale.x = ui_gauge_hp->imageSize.x * 0.2f;
	ui_gauge_hp->scale.y = ui_gauge_hp->imageSize.y * 0.3f;

	spawn->pivot = OFFSET_B;
	spawn->SetParentRT(*collider);
	spawn->maxFrame.x = 14;
	spawn->maxFrame.y = 1;
	spawn->scale.x = spawn->imageSize.x / spawn->maxFrame.x * 1.2f;
	spawn->scale.y = spawn->imageSize.y / spawn->maxFrame.y * 1.2f;
	spawn->ChangeAnim(ANIMSTATE::ONCE, 0.1f);

	onFloor = false;
	isLanding = true;
}

Monster::~Monster()
{
	delete ui_frame_hp;
	delete ui_gauge_hp;
}


void Monster::Update()
{

	lastPos = collider->GetWorldPos();


	// 사망 처리
	if (hp == 0 && CurrentState != State::DIE)
	{
		// 사운드 출력
		SOUND->Stop("rat_die");
		SOUND->Play("rat_die");

		// 상태변경
		CurrentState = State::DIE;
	}

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
			idle->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			run->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			jump->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			attack->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
		}
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
	int distanceY = GM->player->GetCollider()->GetWorldPos().y - collider->GetWorldPos().y;
	int distanceX_abs = abs(distanceX);
	int distanceY_abs = abs(distanceY);

	if (CurrentState == State::IDLE)
	{
		// 몬스터가 공격 가능한 거리 안에 있다면
		if (distanceX_abs < maxAttackDistance)
		{
			// 몬스터와 플레이어의 높이 비교
			if (distanceY_abs < 200)
			{
				// 플레이어와 비슷한 높이에 있다면 공격시도
				if (isAttackCooldown())
				{
					// IDLE -> ATTACK
					CurrentState = State::ATTACK;
				}
			}
			else
			{
				// 플레이어가 더 높이 있다면 점프
				if (distanceY > 0)
				{
					Jump();
				}
				// 플레이어가 더 낮게 있다면 하강
				else if (distanceY < 0 && onFloor)
				{
					gravity = 0;
					CurrentState = State::CROUCH_DOWN;
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
		// 플레이어가 공격 가능한 범위안에 들어왔을 때
		if (distanceX_abs < maxAttackDistance)
		{
			// 공격 가능하다면
			if (isAttackCooldown())
			{
				// RUN -> ATTACK
				CurrentState = State::ATTACK;
			}
			// 공격 불가능하다면
			else
			{
				// RUN -> IDLE
				CurrentState = State::IDLE;
			}
		}

		collider->MoveWorldPos(dir * moveSpeed * DELTA);
	}
	else if (CurrentState == State::JUMP)
	{
		// 상승
		if (gravity < 0)
		{
			jump->frame.y = 0;
			isLanding = false;

		}
		// 하강
		else
		{
			jump->frame.y = 1;
			isLanding = true;

			// jump -> idle
			if (onFloor || onWall)
			{
				CurrentState = State::IDLE;
			}
		}
	}
	else if (CurrentState == State::ATTACK)
	{
		// 공격 프레임에 도달하면 실제 공격이 이루어짐
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
	else if (CurrentState == State::CROUCH_DOWN)
	{
		jump->frame.y = 1;
		jumpTime += DELTA;
		isLanding = false;

		if (jumpTime > 0.3f || onWall)
		{
			isLanding = true;
			jumpTime = 0.0f;
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::SPAWN)
	{
		spawn->color.w -= 0.2f * DELTA;
		
		if (spawn->frame.x > 5)
			idle->color.w = min(0.5f, idle->color.w + 0.5f * DELTA);

		// SPAWN 대기
		if (spawn->frame.x == spawn->maxFrame.x - 1)
		{
			idle->color.w = 0.5f;
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::DIE)
	{

	}

	// 중력 (바닥과 떨어져 있거나 스폰중이 아닐 때)
	if (!onWall && !onFloor && CurrentState != State::SPAWN)
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
	case State::CROUCH_DOWN:
		jump->Update();
		break;
	case State::ATTACK:
		attack->Update();
		break;
	case State::SPAWN:
		if (spawn->frame.x > 5)
			idle->Update();
		spawn->Update();
		break;
	}
	collider->Update();

	if (hp != maxHp)
	{
		ui_gauge_hp->scale.x = ui_gauge_hp->imageSize.x * 0.2f * ((float)hp / (float)maxHp);
		ui_gauge_hp->Update();
		ui_frame_hp->Update();
	}
}

void Monster::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	if (hp != maxHp)
	{
		ui_frame_hp->Render();
		ui_gauge_hp->Render();
	}

	if (onWall || onFloor)
		shadow->Update();
	
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
	case State::CROUCH_DOWN:
		jump->Render();
		break;
	case State::ATTACK:
		attack->Render();
		break;
	case State::SPAWN:
		if (spawn->frame.x > 5)
			idle->Render();
		spawn->Render();
		break;
	}


}

bool Monster::isAttackCooldown()
{
	float currentTime = TIMER->GetWorldTime();			// 현재시간
	float elapsedTime = currentTime - lastAttackTime;	// 경과시간

	if (elapsedTime >= timeTakenToAttackOnce)
	{
		attack->frame.x = 0;
		realAttack = true;

		// 공속계산
		lastAttackTime = currentTime;
		timeTakenToAttackOnce = 1.0f / attackSpeed;

		return true;
	}

	return false;
}

void Monster::Attack()
{


}

bool Monster::isDead() const
{
	if (CurrentState == State::DIE)
	{
		ObImage* dieEffect = new ObImage(L"monster_die.png");
		dieEffect->pivot = OFFSET_B;
		dieEffect->SetWorldPos(collider->GetWorldPos());
		dieEffect->maxFrame.x = 13;
		dieEffect->maxFrame.y = 1;
		dieEffect->scale.x = dieEffect->imageSize.x / dieEffect->maxFrame.x * 0.8f;
		dieEffect->scale.y = dieEffect->imageSize.y / dieEffect->maxFrame.y * 0.8f;
		dieEffect->color.w = 0.4f;
		dieEffect->ChangeAnim(ANIMSTATE::ONCE, 0.1f);

		GM->fx->AddEffects(dieEffect);

		return true;
	}
	else return false;
}

void Monster::actionsWhenDamaged(int damage, int knockBackFactor, int criticalChance)
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

	// 데미지 텍스트가 출력될 위치 계산
	Vector2 tempPos = collider->GetWorldPos() + Vector2(0, collider->scale.y * 0.75f);
	
	// 크리티컬 계산
	if (RANDOM->Int(1, 100) <= criticalChance)
	{
		damage *= 2;

		// 데미지 텍스트 출력
		GM->damageDP->AddText(tempPos, damage, 6);
	}
	else
	{
		GM->damageDP->AddText(tempPos, damage);
	}


	// 넉백 계수
	this->knockBackFactor = knockBackFactor;

	// 체력 감소
	this->hp = max(0, hp - damage);
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