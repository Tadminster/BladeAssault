#include "stdafx.h"
#include "DamageDisplayManager.h"
#include "Projectile.h"
#include "Creature.h"
#include "Player.h"

Player::Player()
{
	idle = nullptr;
	run = nullptr;
	dash = nullptr;
	jump = nullptr;
	crouch = nullptr;
	attack = nullptr;
	damaged = nullptr;
	shadow = nullptr;
	die = nullptr;

	jumpTime = 0.0f;
	moveSpeed = 350.0f;

	jumpCount = 0;
	jumpCountMax = 2;

	dashWeight = 0.0f;
	dashRemainingCooldown = 0.0f;
	dashCooldown = 2.0f;

	criticalChance = 10;
}

Player::~Player()
{
	Creature::~Creature();
	delete dash;
	delete crouch;
	delete damaged;
	delete die;
	delete charging;
	delete skill;
}

void Player::Init()
{
	PrevState = State::IDLE;
	CurrentState = State::STANDBY;
	lastDir = RIGHT;

	gravity = 0.0f;

	onFloor = false;
	isLanding = true;
	isCharging = false;
	damageTaken = false;
}

void Player::Update()
{
	ImGui::Text("gravity : %f\n", GM->player->gravity);
	ImGui::Text("playerState : %d\n", GM->player->CurrentState);
	ImGui::Text("chargingTime : %f\n", chargingTime);

	lastPos = collider->GetWorldPos();
	collider->Update();

	// 컨트롤
	Control();

	// 스킨 방향 설정
	if (dir == LEFT)
	{
		idle->reverseLR = true;
		run->reverseLR = true;
		dash->reverseLR = true;
		jump->reverseLR = true;
		crouch->reverseLR = true;
		attack->reverseLR = true;
		damaged->reverseLR = true;
		die->reverseLR = false;
		skill->reverseLR = true;

	}
	else if (dir == RIGHT)
	{
		idle->reverseLR = false;
		run->reverseLR = false;
		dash->reverseLR = false;
		jump->reverseLR = false;
		crouch->reverseLR = false;
		attack->reverseLR = false;
		damaged->reverseLR = false;
		die->reverseLR = true;
		skill->reverseLR = false;
	}

	// 사망 처리
	if (hp == 0 && CurrentState != State::DIE)
	{
		CurrentState = State::DIE;
	}

	// 상태 업데이트
	if (CurrentState == State::IDLE)
	{
		// 상태가 IDLE인데, 바닥에 있지 않으면
		if (!onFloor && !onWall)
		{
			// jump 상태로 변경
			jump->frame.y = 1;
			CurrentState = State::JUMP;
		}
	}
	else if (CurrentState == State::RUN)
	{
		collider->MoveWorldPos(dir * moveSpeed * DELTA);
	}
	else if (CurrentState == State::DASH)
	{
		// dash 가중치, 시간 계산용
		dashWeight += DELTA * 3.0f;

		// dash 가중치가 1.0f 이상이거나 벽에 붙어있으면
		// dash -> PrevState
		if (dashWeight >= 1.0f || onWallSlide)
		{
			CurrentState = PrevState;
		}


		// dash
		collider->SetWorldPos(Vector2::Lerp(collider->GetWorldPos(), dashTargetPos, DELTA * 10.0f));

		// 선형보간으로 이동

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
				jumpCount = 0;
				CurrentState = State::IDLE;
			}
		}

		collider->MoveWorldPos(dir* moveSpeed* DELTA);
	}
	else if (CurrentState == State::CROUCH)
	{
		// 웅크리고 있을 땐 충돌체 크기 줄이기
		if (collider->scale.y != 70)
			collider->scale.y = 70;
	}
	else if (CurrentState == State::CROUCH_DOWN)
	{
		jump->frame.y = 1;
		jumpTime += DELTA;
		isLanding = false;
			
		// 하강 후 0.3s 이상 경과 && 바닥에 닿았으면 
		if (jumpTime > 0.3f || onWall)
		{
			// 착지
			isLanding = true;
			jumpTime = 0.0f;

			// crouch down -> idle
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::ATTACK)
	{
		// 공격 중 이동은 감속 (0.5배)
		collider->MoveWorldPos(dir * moveSpeed * 0.5f * DELTA);

		// 프레임이 끝나면 attack -> PrevState
		if (attack->frame.x == attack->maxFrame.x - 1)
		{
			CurrentState = PrevState;
		}
	}
	else if (CurrentState == State::CHARGING)
	{
		chargingTime = min(chargingTimeMax, chargingTime + DELTA);

		// 차징 중 프레임 변경
		if (isCharging && charging->frame.x == chargingEndFrame)
		{
			charging->frame.x = chargingStartFrame;
		}

		// 프레임이 끝나면 charging -> idle
		if (charging->frame.x == charging->maxFrame.x - 1)
		{
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::SKILL)
	{

		// 프레임이 끝나면 charging -> idle
		if (skill->frame.x == skill->maxFrame.x - 1)
		{
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::DAMAGED)
	{
		// 데미지를 입고 있는 상태일 때 감속
		collider->MoveWorldPos(dir * moveSpeed * 0.5f * DELTA);

		// 데미지 입은 후 0.1초 후에 damaged -> PrevState
		if (timeOfDamaged + 0.1f < TIMER->GetWorldTime())
		{
			CurrentState = PrevState;
		}
	}
	else if (CurrentState == State::SPAWN)
	{
		// SPAWN 대기
		if (spawn->frame.x == spawn->maxFrame.x - 1)
		{
			CurrentState = State::IDLE;
		}
	}

	// 대쉬 남은 재사용 대기시간 감소
	if (dashRemainingCooldown > 0.0f)
		dashRemainingCooldown -= DELTA;

	// 스킬 남은 재사용 대기시간 감소	
	if (skillRemainingCooldown > 0.0f)
		skillRemainingCooldown -= DELTA;

	// 1. 바닥과 떨어져 있을 때
	// 2. SPAWN 이나 STANDBY 상태가 아닐 때
	// 중력적용
	if (!onWall && !onFloor 
		&& CurrentState != State::SPAWN
		&& CurrentState != State::STANDBY)
	{
		gravity += 1500.0f * DELTA;
		collider->MoveWorldPos(DOWN * gravity * DELTA);
	}

	// 탄이 몬스터와 충돌하면
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr) { return pr->hasCollideWithMonster(); }
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

	// 플레이어의 탄 업데이트
	for (auto& proj : projectiles)
		proj->Update();

	if (onWall || onFloor)
		shadow->Update();

	// 기타 업데이트
	collider->Update();
	if (CurrentState == State::IDLE)
		idle->Update();
	else if (CurrentState == State::RUN)
		run->Update();
	else if (CurrentState == State::DASH)
		dash->Update();
	else if (CurrentState == State::JUMP)
		jump->Update();
	else if (CurrentState == State::CROUCH)
		crouch->Update();
	else if (CurrentState == State::CROUCH_DOWN)
		jump->Update();
	else if (CurrentState == State::ATTACK)
		attack->Update();
	else if (CurrentState == State::CHARGING)
		charging->Update();
	else if (CurrentState == State::SKILL)
		skill->Update();
	else if (CurrentState == State::DAMAGED)
		damaged->Update();
	else if (CurrentState == State::SPAWN)
		spawn->Update();
	else if (CurrentState == State::DIE)
		die->Update();
	else if (CurrentState == State::STANDBY)
		idle->Update();
}

void Player::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();


	// 바닥에 있을 때만 그림자를 그린다
	if (onWall || onFloor)
		shadow->Render();

	if (CurrentState == State::IDLE)
		idle->Render();
	else if (CurrentState == State::RUN)
		run->Render();
	else if (CurrentState == State::DASH)
		dash->Render();
	else if (CurrentState == State::JUMP)
		jump->Render();
	else if (CurrentState == State::CROUCH)
		crouch->Render();
	else if (CurrentState == State::CROUCH_DOWN)
		jump->Render();
	else if (CurrentState == State::ATTACK)
		attack->Render();
	else if (CurrentState == State::CHARGING)
		charging->Render();
	else if (CurrentState == State::SKILL)
		skill->Render();
	else if (CurrentState == State::DAMAGED)
		damaged->Render();
	else if (CurrentState == State::SPAWN)
		spawn->Render();
	else if (CurrentState == State::DIE)
		die->Render();
	else if (CurrentState == State::STANDBY)
		idle->Render();

	for (auto& proj : projectiles)
		proj->Render();
}



void Player::Control()
{
	dir = Vector2();

	if (GM->DEBUG_MODE)
	{
		if (INPUT->KeyDown(VK_OEM_PLUS) && CurrentState != State::DIE)
		{
			float heal = maxHp * 0.1f;
			hp = min(maxHp, hp + heal);
			GM->damageDP->AddText(collider->GetWorldPos() + UP * collider->scale.y * 0.75f, heal, 5);
		}

		if (INPUT->KeyDown(VK_OEM_MINUS))
		{
			float damage = maxHp * 0.1;
			hp = max(0, hp - damage);
			damageTaken = true;
			GM->damageDP->AddText(collider->GetWorldPos() + UP * collider->scale.y * 0.75f, damage, 1);
		}
	}


	// 상태 업데이트
	if (CurrentState == State::IDLE)
	{


		// idle -> run
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
			CurrentState = State::RUN;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
			CurrentState = State::RUN;
		}

		// idle -> jump
		if (INPUT->KeyDown('W'))
		{
			Jump();
		}

		// idle -> crouch
		if (INPUT->KeyPress('S'))
		{
			CurrentState = State::CROUCH;
		}

		// idle -> dash
		if (INPUT->KeyDown(VK_SPACE))
		{
			Dash();
		}

		// idle -> attack
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			Attack();
		}

		// charging attack
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			chargingTime += DELTA;
			if (chargingTime > 0.5f)
			{
				Charging();
			}
		}

		// idle -> skill
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			Skill();
		}
	}
	else if (CurrentState == State::RUN)
	{
		// runing
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
		}

		// run -> idle
		if (!(INPUT->KeyPress('A') || INPUT->KeyPress('D')))
		{
			CurrentState = State::IDLE;
			run->frame.x = 0;
		}

		// run -> jump
		if (INPUT->KeyDown('W'))
		{
			Jump();
		}

		// run -> dash
		if (INPUT->KeyDown(VK_SPACE))
		{
			Dash();
		}

		// run -> attack
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			Attack();
		}

		// run -> skill
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			Skill();
		}
	}
	else if (CurrentState == State::JUMP)
	{
		// jump 중 이동
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
		}

		// jump -> dash
		if (INPUT->KeyDown(VK_SPACE))
		{
			Dash();
		}

		// jump -> double jump
		if (INPUT->KeyDown('W') && jumpCount < jumpCountMax)
		{
			jumpCount++;
			gravity = -900;
		}

		// jump -> attack
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			Attack();
		}

		// jump -> skill
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			Skill();
		}
	}
	else if (CurrentState == State::CROUCH)
	{
		// crouch -> idle
		if (!INPUT->KeyPress('S'))
		{
			collider->scale.y = 100;
			CurrentState = State::IDLE;
		}

		// crouch -> run
		if (INPUT->KeyPress('A') || INPUT->KeyPress('D'))
		{
			collider->scale.y = 100;
			CurrentState = State::RUN;
		}

		// crouch -> jump
		if (INPUT->KeyDown('W'))
		{
			collider->scale.y = 100;
			Jump();
		}

		// crouch -> down
		if (INPUT->KeyDown(VK_SHIFT))
		{
			collider->scale.y = 100;
			jumpCount = 1;
			gravity = 0;
			CurrentState = State::CROUCH_DOWN;
		}
	}
	else if (CurrentState == State::ATTACK)
	{


		// attack 중 이동
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
		}

		// attack -> dash
		if (INPUT->KeyDown(VK_SPACE))
		{
			Dash();
		}

		// attack -> jump
		if (INPUT->KeyDown('W'))
		{
			Jump();
		}

	}
	else if (CurrentState == State::CHARGING)
	{
		// charging -> idle
		if (INPUT->KeyUp(VK_LBUTTON))
		{

			ChargingAttack();
		}

		// charging -> run
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
			CurrentState = State::RUN;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
			CurrentState = State::RUN;
		}

		// charging -> jump
		if (INPUT->KeyDown('W'))
		{
			Jump();
		}
	}
	else if (CurrentState == State::SKILL)
	{
		// skill 중 이동
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
		}
	}
	else if (CurrentState == State::DAMAGED)
	{
		// damaged 중 이동
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
		}
	}
	else if (CurrentState == State::STANDBY)
	{
		// stnadby -> walk
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
			CurrentState = State::RUN;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
			CurrentState = State::RUN;
		}

		// stnadby -> jump
		if (INPUT->KeyDown('W'))
		{
			Jump();
		}

		// stnadby -> crouch
		if (INPUT->KeyPress('S'))
		{
			CurrentState = State::CROUCH;
		}
	}

	if (dir == LEFT) lastDir = LEFT;
	else if (dir == RIGHT) lastDir = RIGHT;
}

void Player::Attack()
{
	attack->frame.x = 0;
	chargingTime = 0.0f;
	PrevState = CurrentState;
	CurrentState = State::ATTACK;
}



void Player::Charging()
{
	charging->frame.x = 0;
	isCharging = true;
	CurrentState = State::CHARGING;
}

void Player::ChargingAttack()
{
	isCharging = false;
	chargingTime = 0.0f;
}

void Player::Skill()
{
	skill->frame.x = 0;
	PrevState = CurrentState;
	CurrentState = State::SKILL;
}

void Player::SkillAttack()
{
}

void Player::Dash()
{
	// 대시쿨타임이 충족되지 않았으면 리턴
	if (dashRemainingCooldown > 0) return;

	dashRemainingCooldown = dashCooldown;
	dash->frame.x = 0;
	dashWeight = 0.0f;
	dashTargetPos.x = collider->GetWorldPos().x + lastDir.x * 300;
	dashTargetPos.y = collider->GetWorldPos().y + 5;

	PrevState = CurrentState;
	if (PrevState == State::ATTACK)
		if (onFloor || onWall) PrevState = State::IDLE;
		else PrevState = State::JUMP;
	CurrentState = State::DASH;
}

void Player::actionsWhenDamaged(int damage)
{
	// 대시 중에는 데미지를 받지 않음
	if (CurrentState == State::DASH)
		return;

	// 상태를 데미지 받음으로 변경
	if (CurrentState == State::IDLE || CurrentState == State::RUN)
		CurrentState = State::DAMAGED;
	
	// 데미지 받음 FX 출력을 위한
	damageTaken = true;

	// 스킨 컬러 변경
	//damaged->color = Vector4(0.1, 0.1, 0.1, 0.5);
	
	// 데미지 받은 시간 기록
	timeOfDamaged = TIMER->GetWorldTime();

	// 방어력 만큼 데미지 차감
	damage = max(0, damage - defence);

	// 체력 감소
	hp = max(hp - damage, 0);
	
	// 데미지 텍스트 출력
	Vector2 tempSpawnPos = collider->GetWorldPos() + Vector2(0, collider->scale.y * 0.5f);
	GM->damageDP->AddText(tempSpawnPos, damage, 2);
}
