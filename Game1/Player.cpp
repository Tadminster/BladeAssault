#include "stdafx.h"
#include "Projectile.h"
#include "Player.h"

Player::Player()
{
	collider = new ObRect();
	idle = nullptr;
	run = nullptr;
	dash = nullptr;
	jump = nullptr;
	crouch = nullptr;
	attack = nullptr;
	damaged = nullptr;
	shadow = nullptr;
	die = nullptr;
}

Player::~Player()
{
	delete collider;
	delete idle;
	delete run;
	delete dash;
	delete jump;
	delete crouch;
	delete attack;
	delete damaged;
	delete shadow;
	delete die;
}

void Player::Init()
{
	CurrentState = PlayerState::IDLE;
	
	lastDir = RIGHT;

	speed = 350.0f;
	jumpSpeed = 700;
	jumpTime = 0.0f;

	gravity = 0.0f;
	onFloor = false;
	isLanding = true;

	jumpCount = 0;
	jumpCountMax = 2;

	dashCooldown = 0.0f;
	dashDealay = 2.0;

	damageTaken = false;
}

void Player::Update()
{
	ImGui::Text("gravity : %f\n", GM->player->gravity);
	ImGui::Text("playerState : %d\n", GM->player->CurrentState);

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
	}

	// 사망 처리
	if (hp == 0 && CurrentState != PlayerState::DIE)
	{
		CurrentState = PlayerState::DIE;
	}

	// 상태 업데이트
	if (CurrentState == PlayerState::IDLE)
	{

	}
	else if (CurrentState == PlayerState::RUN)
	{
		collider->MoveWorldPos(dir * speed * DELTA);
	}
	else if (CurrentState == PlayerState::DASH)
	{
		static float weight = 0;
		weight += DELTA * 3;
		if (weight >= 1.0f || onWallSlide)
		{
			weight = 0;
			CurrentState = PrevState;
		}

		collider->SetWorldPos(Vector2::Lerp(collider->GetWorldPos(), dashTargetPos, 0.004f));
	}
	else if (CurrentState == PlayerState::JUMP)
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
				CurrentState = PlayerState::IDLE;
			}
		}

		collider->MoveWorldPos(dir * speed * DELTA);
	}
	else if (CurrentState == PlayerState::CROUCH)
	{
	}
	else if (CurrentState == PlayerState::CROUCH_DOWN)
	{
		jump->frame.y = 1;
		jumpTime += DELTA;
		isLanding = false;

		if (jumpTime > 0.3f || onWall)
		{
			isLanding = true;
			jumpTime = 0.0f;
			CurrentState = PlayerState::IDLE;
		}
	}
	else if (CurrentState == PlayerState::ATTACK)
	{
		collider->MoveWorldPos(dir * speed * 0.5 * DELTA);

		if (attack->frame.x == attack->maxFrame.x - 1)
		{
			CurrentState = PrevState;
		}
	}
	else if (CurrentState == PlayerState::DAMAGED)
	{
		collider->MoveWorldPos(dir * speed * 0.5 * DELTA);

		if (timeOfDamaged + 0.1f < TIMER->GetWorldTime())
		{
			CurrentState = PrevState;
		}
	}

	// 대쉬 쿨타임
	if (dashCooldown > 0.0f)
		dashCooldown -= DELTA;

	// 중력
	//if (!onFloor)
	if (!onWall && !onFloor)
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
	if (CurrentState == PlayerState::IDLE)
		idle->Update();
	else if (CurrentState == PlayerState::RUN)
		run->Update();
	else if (CurrentState == PlayerState::DASH)
		dash->Update();
	else if (CurrentState == PlayerState::JUMP)
		jump->Update();
	else if (CurrentState == PlayerState::CROUCH)
		crouch->Update();
	else if (CurrentState == PlayerState::CROUCH_DOWN)
		jump->Update();
	else if (CurrentState == PlayerState::ATTACK)
		attack->Update();
	else if (CurrentState == PlayerState::DAMAGED)
		damaged->Update();
	else if (CurrentState == PlayerState::DIE)
		die->Update();
}

void Player::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();


	// 바닥에 있을 때만 그림자를 그린다
	if (onWall || onFloor)
		shadow->Render();

	if (CurrentState == PlayerState::IDLE)
		idle->Render();
	else if (CurrentState == PlayerState::RUN)
		run->Render();
	else if (CurrentState == PlayerState::DASH)
		dash->Render();
	else if (CurrentState == PlayerState::JUMP)
		jump->Render();
	else if (CurrentState == PlayerState::CROUCH)
		crouch->Render();
	else if (CurrentState == PlayerState::CROUCH_DOWN)
		jump->Render();
	else if (CurrentState == PlayerState::ATTACK)
		attack->Render();
	else if (CurrentState == PlayerState::DAMAGED)
		damaged->Render();
	else if (CurrentState == PlayerState::DIE)
		die->Render();

	for (auto& proj : projectiles)
		proj->Render();
}



void Player::Control()
{
	dir = Vector2();

	if (GM->DEBUG_MODE)
	{
		if (INPUT->KeyDown(VK_OEM_PLUS) && CurrentState != PlayerState::DIE)
		{
			hp = min(maxHp, hp + maxHp * 0.1);
		}

		if (INPUT->KeyDown(VK_OEM_MINUS))
		{
			hp = max (0, hp - maxHp * 0.1);
			damageTaken = true;
		}
	}


	// 상태 업데이트
	if (CurrentState == PlayerState::IDLE)
	{
		// idle -> walk
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
			CurrentState = PlayerState::RUN;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
			CurrentState = PlayerState::RUN;
		}

		// idle -> jump
		if (INPUT->KeyDown('W'))
		{
			Jump();
		}

		// idle -> crouch
		if (INPUT->KeyPress('S'))
		{
			CurrentState = PlayerState::CROUCH;
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
	}
	else if (CurrentState == PlayerState::RUN)
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
			CurrentState = PlayerState::IDLE;
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
	}
	else if (CurrentState == PlayerState::JUMP)
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
	}
	else if (CurrentState == PlayerState::CROUCH)
	{
		// crouch -> idle
		if (!INPUT->KeyPress('S'))
			CurrentState = PlayerState::IDLE;

		// crouch -> run
		if (INPUT->KeyPress('A') || INPUT->KeyPress('D'))
			CurrentState = PlayerState::RUN;

		// crouch -> jump
		if (INPUT->KeyDown('W'))
		{
			Jump();
		}

		// crouch -> down
		if (INPUT->KeyDown(VK_SHIFT))
		{
			jumpCount = 1;
			gravity = 0;
			CurrentState = PlayerState::CROUCH_DOWN;
		}
	}
	else if (CurrentState == PlayerState::ATTACK)
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
	else if (CurrentState == PlayerState::DAMAGED)
	{
		// DAMAGED 중 이동
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
		}
	}

	if (dir == LEFT) lastDir = LEFT;
	else if (dir == RIGHT) lastDir = RIGHT;
}

void Player::Attack()
{
	attack->frame.x = 0;
	PrevState = CurrentState;
	CurrentState = PlayerState::ATTACK;
}

void Player::Dash()
{
	// 대시쿨타임이 충족되지 않았으면 리턴
	if (dashCooldown > 0) return;
	
	dashCooldown = dashDealay;
	dash->frame.x = 0;
	dashTargetPos.x = collider->GetWorldPos().x + (lastDir.x * 300);
	dashTargetPos.y = collider->GetWorldPos().y + 5;
	
	PrevState = CurrentState;
	if (PrevState == PlayerState::ATTACK)
		if (onFloor || onWall) PrevState = PlayerState::IDLE;
		else PrevState = PlayerState::JUMP;
	CurrentState = PlayerState::DASH;
}

void Player::Jump()
{
	collider->SetWorldPosY(collider->GetWorldPos().y + 5);
	gravity = -900;
	CurrentState = PlayerState::JUMP;
}

void Player::OnFloorAction()
{
	onFloor = true;
	gravity = 0;
}

void Player::OnWallAction()
{
	onWall = true;
	gravity = 0;
}

void Player::OnWallSlideAction()
{
	collider->SetWorldPosX(lastPos.x);
	collider->Update();
}

void Player::actionsWhenDamaged(int value)
{
	// 대시 중에는 데미지를 받지 않음
	if (CurrentState == PlayerState::DASH)
		return;

	// 상태를 데미지 받음으로 변경
	if (CurrentState == PlayerState::IDLE || CurrentState == PlayerState::RUN)
		CurrentState = PlayerState::DAMAGED;
	
	// 데미지 받음 FX 출력을 위한
	damageTaken = true;

	// 스킨 컬러 변경
	//damaged->color = Vector4(0.1, 0.1, 0.1, 0.5);
	
	// 데미지 받은 시간 기록
	timeOfDamaged = TIMER->GetWorldTime();

	// 데미지 차감
	int damage = min(value + defence, 0);
	// 체력 감소
	hp = max(hp + damage, 0);
}

void Player::GoBack()
{
	gravity = 0;
	collider->SetWorldPos(lastPos);
	collider->Update();
}

Vector2 Player::GetFoot()
{
	//29 38
	//Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
	//Utility::IntersectRectRect()

	//                              중앙에서나갈위치    발중앙위치 보정
	return collider->GetWorldPos() + (dir + DOWN) * Vector2(collider->scale.x * 0.5f, collider->scale.y * 0.5f);
}

Vector2 Player::GetHead()
{
	//29 38
	//Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
	//Utility::IntersectRectRect()

	//                              중앙에서나갈위치    발중앙위치 보정
	return collider->GetWorldPos() + (dir + UP) * Vector2(collider->scale.x * 0.5f, collider->scale.y * 0.5f);
}
