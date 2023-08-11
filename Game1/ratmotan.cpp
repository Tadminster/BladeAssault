#include "stdafx.h"

#include "Projectile.h"
#include "ratmotan_atk.h"
#include "ratmotan_dashAtk.h"
#include "ratmotan_dashFinish.h"

#include "MonsterManager.h"

#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "ratmotan.h"

ratmotan::ratmotan()
{
	idle = new ObImage(L"ratmotan_idle.png");
	run = new ObImage(L"ratmotan_run.png");
	dash = new ObImage(L"ratmotan_dash.png");
	jump = new ObImage(L"ratmotan_jump.png");
	attack = new ObImage(L"ratmotan_powersmash.png");
	shadow = new ObImage(L"character_shadow.png");
	ui_frame_bossHp = new ObImage(L"gauge_boss_frame.png");
	ui_gauge_bossHp = new ObImage(L"gauge_boss_full.png");

	collider->pivot = OFFSET_B;
	collider->isFilled = false;
	collider->scale.x = 160;
	collider->scale.y = 200;

	//spawn->SetLocalPosX(-collider->scale.x * 0.1f);
	spawn->SetLocalPosY(-collider->scale.y * 0.5f);

	idle->pivot = OFFSET_B;
	idle->SetParentRT(*collider);
	idle->SetLocalPosY(-collider->scale.y * 0.4f);
	idle->maxFrame.x = 6;
	idle->maxFrame.y = 1;
	idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3.0f;
	idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3.0f;
	idle->color.w = 0.0f;
	idle->ChangeAnim(ANIMSTATE::LOOP, 0.15f, true);

	run->pivot = OFFSET_B;
	run->SetParentRT(*collider);
	run->SetLocalPosY(-collider->scale.y * 0.4f);
	run->maxFrame.x = 6;
	run->maxFrame.y = 1;
	run->scale.x = run->imageSize.x / run->maxFrame.x * 3.0f;
	run->scale.y = run->imageSize.y / run->maxFrame.y * 3.0f;
	run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	dash->pivot = OFFSET_B;
	dash->SetParentRT(*collider);
	dash->SetLocalPosY(-collider->scale.y * 0.4f);
	dash->maxFrame.x = 8;
	dash->maxFrame.y = 1;
	dash->scale.x = dash->imageSize.x / dash->maxFrame.x * 3.0f;
	dash->scale.y = dash->imageSize.y / dash->maxFrame.y * 3.0f;
	dash->ChangeAnim(ANIMSTATE::ONCE, 0.15f, true);

	jump->pivot = OFFSET_B;
	jump->SetParentRT(*collider);
	jump->SetLocalPosY(-collider->scale.y * 0.4f);
	jump->maxFrame.x = 2;
	jump->maxFrame.y = 2;
	jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3.0f;
	jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3.0f;
	jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	attack->pivot = OFFSET_B;
	attack->SetParentRT(*collider);
	attack->SetLocalPosY(-collider->scale.y * 0.4f);
	attack->maxFrame.x = 13;
	attack->maxFrame.y = 1;
	attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3.0f;
	attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3.0f;
	attack->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	shadow->pivot = OFFSET_B;
	shadow->SetParentRT(*collider);
	shadow->SetLocalPosY(-collider->scale.y * 0.4f);
	shadow->maxFrame.x = 1;
	shadow->maxFrame.y = 1;
	shadow->scale.x = shadow->imageSize.x / shadow->maxFrame.x * 4.0f;
	shadow->scale.y = shadow->imageSize.y / shadow->maxFrame.y * 4.0f;
	shadow->color.w = 0.2f;
	shadow->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	ui_frame_hp->scale = Vector2(0, 0);
	ui_gauge_hp->scale = Vector2(0, 0);

	ui_frame_bossHp->space = SPACE::SCREEN;
	ui_frame_bossHp->pivot = OFFSET_L;

	ui_frame_bossHp->SetWorldPos(Vector2(-app.GetWidth() * 0.26f, app.GetHeight() * 0.35f));
	ui_frame_bossHp->scale.x = ui_frame_bossHp->imageSize.x * 2.0f;
	ui_frame_bossHp->scale.y = ui_frame_bossHp->imageSize.y * 2.0f;

	ui_gauge_bossHp->space = SPACE::SCREEN;
	ui_gauge_bossHp->pivot = OFFSET_L;
	ui_gauge_bossHp->SetParentRT(*ui_frame_bossHp);
	ui_gauge_bossHp->scale.x = ui_gauge_bossHp->imageSize.x * 2.0f;
	ui_gauge_bossHp->scale.y = ui_gauge_bossHp->imageSize.y * 2.0f;

	// Boss Name
	textBox_bossName.left = app.GetHalfWidth() * 0.92f;
	textBox_bossName.top = app.GetHalfHeight() * 0.1f;
	textBox_bossName.right = textBox_bossName.left + 1000;
	textBox_bossName.bottom = textBox_bossName.top + 1000;

	name = "ratmotan";
	CurrentState = State::SPAWN;
	dir = LEFT;

	hp = 1000;
	maxHp = 1000;
	damage = 30;
	attackSpeed = 0.2f;
	attackFrame = 6;
	attackRange = 1;
	moveSpeed = 140;
	jumpSpeed = 1000.0f;
	maxAttackDistance = 900;

	timeTakenToAttackOnce = 1.0f / attackSpeed;
}

ratmotan::~ratmotan()
{
	delete dash;
	delete ui_frame_bossHp;
	delete ui_gauge_bossHp;
}

void ratmotan::Update()
{
	lastPos = collider->GetWorldPos();

	// 체력바 게이지 설정
	ui_gauge_bossHp->scale.x = ui_gauge_bossHp->imageSize.x * 2.0f * ((float)hp / (float)maxHp);

	// 사망 처리
	if (hp == 0 && CurrentState != State::DIE)
	{
		// 사운드 출력
		SOUND->Stop("ratmotan_die");
		SOUND->Play("ratmotan_die");

		// 상태변경
		CurrentState = State::DIE;
	}

	Vector2 target = GM->player->GetCollider()->GetWorldPos();
	// 공격 중이나 점프 중이 아니면
	if (CurrentState != State::ATTACK && CurrentState != State::JUMP && CurrentState != State::DASH)
	{
		// 방향 계산
		if (target.x - collider->GetWorldPos().x > 0)
			dir = RIGHT;
		else
			dir = LEFT;
	}
	// 스킨 방향 설정
	if (dir == LEFT)
	{
		idle->reverseLR = true;
		run->reverseLR = true;
		jump->reverseLR = true;
		attack->reverseLR = true;
		dash->reverseLR = true;
	}
	else if (dir == RIGHT)
	{
		idle->reverseLR = false;
		run->reverseLR = false;
		jump->reverseLR = false;
		attack->reverseLR = false;
		dash->reverseLR = false;
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
			// 플레이어와 비슷한 높이에 있다면 공격시도
			if (isAttackCooldown())
			{
				// IDLE -> ATTACK
				CurrentState = State::ATTACK;
			}

			// 점프가 가능하다면
			else if (isJumpColldown())
			{
				// IDEL -> JUMP
				Jump();
			}

			// 대시가 가능하다면
			else if (isDashColldown())
			{
				// IDEL -> Dash
				Dash();
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
	else if (CurrentState == State::DASH)
	{
		if (dash->frame.x > 5)
		{
			collider->MoveWorldPos(dir * dashSpeed * DELTA);

			if (realDashAttack)
			{
				realDashAttack = false;
				DashAttack();
			}
		}

		// DASH->IDLE
		if (onWallSide)
		{
			DashFinish();
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::JUMP)
	{
		collider->MoveWorldPos(dir * moveSpeed * 2.0f * DELTA);

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
				CurrentState = State::ATTACK;
				Attack();
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
			Shockwave();
		}

		if (attack->frame.x >= attackFrame)
		{
			CAM->position.x += (RANDOM->Int(0, 1) ? 2 : -2);
			CAM->position.y += (RANDOM->Int(0, 1) ? 2 : -2);
		}

		// ATTACK -> IDLE
		if (attack->frame.x == attack->maxFrame.x - 1)
		{
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
	case State::DASH:
		dash->Update();
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
	ui_frame_bossHp->Update();
	ui_gauge_bossHp->Update();
}

void ratmotan::Render()
{
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
	case State::DASH:
		dash->Render();
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

	ui_gauge_bossHp->Render();
	ui_frame_bossHp->Render();

	// HP
	DWRITE->RenderText(
		L"렛모탄",
		textBox_bossName,
		35.0f,
		L"Commando",
		Color(1, 1, 1, 1),
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

}

void ratmotan::Attack()
{
	// 발사 위치 계산
	Vector2 spawnPos = collider->GetWorldPos();

	// 탄생성
	ratmotan_atk* proj = new ratmotan_atk
	(
		spawnPos,										// 생성위치
		dir,										    // 각도
		5,   											// 발사체 속도
		1,          									// 사거리
		damage,											// 공격력
		99,												// 관통력
		1												// 폭발범위
	);

	//벡터에 탄 push
	GM->monster->GetProjectiles().emplace_back(proj);

	SOUND->Stop("ratmotan_jumpAttack");
	SOUND->Play("ratmotan_jumpAttack");
}

void ratmotan::Shockwave()
{
	GM->monster->SpawnMonster("shockwaveGenerator", collider->GetWorldPos() + dir * collider->scale.x * 0.5f);
}

bool ratmotan::isDashColldown()
{
	float currentTime = TIMER->GetWorldTime();			// 현재시간
	float elapsedTime = currentTime - lastDashTime; 	// 경과시간

	if (elapsedTime >= dashCooldown)
	{
		// 마지막 대쉬시간 기록
		lastDashTime = currentTime;

		return true;
	}

	return false;
}

void ratmotan::Dash()
{
	dash->frame.x = 0;
	realDashAttack = true;
	dash->ChangeAnim(ANIMSTATE::ONCE, 0.15f);
	CurrentState = State::DASH;
}

void ratmotan::DashAttack()
{
	// 발사 위치 계산
	Vector2 spawnPos = collider->GetWorldPos();

	// 탄생성
	ratmotan_dashAtk* proj = new ratmotan_dashAtk
	(
		spawnPos,										// 생성위치
		dir,										    // 각도
		dashSpeed,   									// 발사체 속도
		2000,          									// 사거리
		damage * 1.5f,									// 공격력
		99,												// 관통력
		1												// 폭발범위
	);

	//벡터에 탄 push
	GM->monster->GetProjectiles().emplace_back(proj);

	SOUND->Stop("ratmotan_dashAttack");
	SOUND->Play("ratmotan_dashAttack");
}

void ratmotan::DashFinish()
{
	// 발사 위치 계산
	Vector2 spawnPos = collider->GetWorldPos() + dir * collider->scale.x * 0.4f;

	// 탄생성
	ratmotan_dashFinish* proj = new ratmotan_dashFinish
	(
		spawnPos,										// 생성위치
		dir,										    // 각도
		3,			  									// 발사체 속도
		2,          									// 사거리
		damage * 2.0f,									// 공격력
		99,												// 관통력
		1												// 폭발범위
	);

	//벡터에 탄 push
	GM->monster->GetProjectiles().emplace_back(proj);

	SOUND->Stop("ratmotan_dashCollision");
	SOUND->Play("ratmotan_dashCollision");
}

bool ratmotan::isJumpColldown()
{
	float currentTime = TIMER->GetWorldTime();			// 현재시간
	float elapsedTime = currentTime - lastJumpTime;	// 경과시간

	if (elapsedTime >= jumpCooldown)
	{
		// 점프 후 공격을 위해 attack 프레임 설정
		attack->frame.x = attackFrame - 1;

		// 마지막 점프시간 기록
		lastJumpTime = currentTime;

		return true;
	}

	return false;
}

void ratmotan::Jump()
{
	collider->SetWorldPosY(collider->GetWorldPos().y + 5);
	gravity = -jumpSpeed;
	SOUND->Stop("ratmotan_jumpStart");
	SOUND->Play("ratmotan_jumpStart");
	CurrentState = State::JUMP;
}
