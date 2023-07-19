#include "stdafx.h"
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
}

Player::~Player()
{
	delete collider;
	delete idle;
	delete run;
	delete dash;
	delete jump;
	delete crouch;
}

void Player::Init()
{
	Currentstate = PlayerState::IDLE;
	dashDir = RIGHT;

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
}

void Player::Update()
{
	ImGui::Text("gravity : %f\n", GM->player->gravity);
	ImGui::Text("playerState : %d\n", GM->player->Currentstate);

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
	}
	else if (dir == RIGHT)
	{
		idle->reverseLR = false;
		run->reverseLR = false;
		dash->reverseLR = false;
		jump->reverseLR = false;
		crouch->reverseLR = false;
		attack->reverseLR = false;
	}

	// 상태 업데이트
	if (Currentstate == PlayerState::IDLE)
	{
	}
	else if (Currentstate == PlayerState::RUN)
	{
		collider->MoveWorldPos(dir * speed * DELTA);
	}
	else if (Currentstate == PlayerState::DASH)
	{
		static float weight = 0;
		weight += DELTA * 3;
		if (weight >= 1.0f || onWallSlide)
		{
			weight = 0;
			Currentstate = PrevState;
		}

		collider->SetWorldPos(Vector2::Lerp(collider->GetWorldPos(), dashTargetPos, 0.01f));
	}
	else if (Currentstate == PlayerState::JUMP)
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
				Currentstate = PlayerState::IDLE;
			}
		}

		collider->MoveWorldPos(dir * speed * DELTA);
	}
	else if (Currentstate == PlayerState::CROUCH)
	{
	}
	else if (Currentstate == PlayerState::CROUCH_DOWN)
	{
		jump->frame.y = 1;
		jumpTime += DELTA;
		isLanding = false;

		if (jumpTime > 0.3f || onWall)
		{
			isLanding = true;
			jumpTime = 0.0f;
			Currentstate = PlayerState::IDLE;
		}
	}
	else if (Currentstate == PlayerState::ATTACK)
	{
		collider->MoveWorldPos(dir * speed * 0.5 * DELTA);

		if (attack->frame.x == attack->maxFrame.x - 1)
		{
			Currentstate = PrevState;
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


	collider->Update();
	if (Currentstate == PlayerState::IDLE)
		idle->Update();
	else if (Currentstate == PlayerState::RUN)
		run->Update();
	else if (Currentstate == PlayerState::DASH)
		dash->Update();
	else if (Currentstate == PlayerState::JUMP)
		jump->Update();
	else if (Currentstate == PlayerState::CROUCH)
		crouch->Update();
	else if (Currentstate == PlayerState::CROUCH_DOWN)
		jump->Update();
	else if (Currentstate == PlayerState::ATTACK)
		attack->Update();
}

void Player::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	if (Currentstate == PlayerState::IDLE)
		idle->Render();
	else if (Currentstate == PlayerState::RUN)
		run->Render();
	else if (Currentstate == PlayerState::DASH)
		dash->Render();
	else if (Currentstate == PlayerState::JUMP)
		jump->Render();
	else if (Currentstate == PlayerState::CROUCH)
		crouch->Render();
	else if (Currentstate == PlayerState::CROUCH_DOWN)
		jump->Render();
	else if (Currentstate == PlayerState::ATTACK)
		attack->Render();
}



void Player::Control()
{
	dir = Vector2();

	// 상태 업데이트
	if (Currentstate == PlayerState::IDLE)
	{
		// idle -> walk
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
			Currentstate = PlayerState::RUN;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
			Currentstate = PlayerState::RUN;
		}

		// idle -> jump
		if (INPUT->KeyDown('W'))
		{
			Jump();
		}

		// idle -> crouch
		if (INPUT->KeyPress('S'))
		{
			Currentstate = PlayerState::CROUCH;
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
	else if (Currentstate == PlayerState::RUN)
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
			Currentstate = PlayerState::IDLE;
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
	else if (Currentstate == PlayerState::JUMP)
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
	else if (Currentstate == PlayerState::CROUCH)
	{
		// crouch -> idle
		if (!INPUT->KeyPress('S'))
			Currentstate = PlayerState::IDLE;

		// crouch -> run
		if (INPUT->KeyPress('A') || INPUT->KeyPress('D'))
			Currentstate = PlayerState::RUN;

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
			Currentstate = PlayerState::CROUCH_DOWN;
		}
	}
	else if (Currentstate == PlayerState::ATTACK)
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

	if (dir == LEFT) dashDir = LEFT;
	else if (dir == RIGHT) dashDir = RIGHT;
}

void Player::Attack()
{
	attack->frame.x = 0;
	PrevState = Currentstate;
	Currentstate = PlayerState::ATTACK;
}

void Player::Dash()
{
	// 대시쿨타임이 충족되지 않았으면 리턴
	if (dashCooldown > 0) return;
	
	dashCooldown = dashDealay;
	dash->frame.x = 0;
	dashTargetPos.x = collider->GetWorldPos().x + (dashDir.x * 300);
	dashTargetPos.y = collider->GetWorldPos().y + 5;
	
	PrevState = Currentstate;
	if (PrevState == PlayerState::ATTACK)
		if (onFloor || onWall) PrevState = PlayerState::IDLE;
		else PrevState = PlayerState::JUMP;
	Currentstate = PlayerState::DASH;
}

void Player::Jump()
{
	collider->SetWorldPosY(collider->GetWorldPos().y + 5);
	gravity = -900;
	Currentstate = PlayerState::JUMP;
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
