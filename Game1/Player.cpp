#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	collider = new ObRect();
	idle = nullptr;
	run = nullptr;
	jump = nullptr;
	crouch = nullptr;
}

Player::~Player()
{
	delete collider;
	delete idle;
	delete run;
	delete jump;
	delete crouch;
}

void Player::Init()
{
	state = PlayerState::IDLE;
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
	ImGui::Text("playerState : %d\n", GM->player->state);

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
	}
	else if (dir == RIGHT)
	{
		idle->reverseLR = false;
		run->reverseLR = false;
		dash->reverseLR = false;
		jump->reverseLR = false;
		crouch->reverseLR = false;
	}

	// 상태 업데이트
	if (state == PlayerState::IDLE)
	{
	}
	else if (state == PlayerState::RUN)
	{
		collider->MoveWorldPos(dir * speed * DELTA);
	}
	else if (state == PlayerState::DASH)
	{
		static float weight = 0;
		weight += DELTA * 3;
		if (weight >= 1.0f || onWallSlide)
		{
			weight = 0;
			state = PlayerState::JUMP;
		}

		collider->SetWorldPos(Vector2::Lerp(collider->GetWorldPos(), dashTargetPos, 0.01f));
	}
	else if (state == PlayerState::JUMP)
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
				state = PlayerState::IDLE;
			}
		}

		collider->MoveWorldPos(dir * speed * DELTA);
	}
	else if (state == PlayerState::CROUCH)
	{
	}
	else if (state == PlayerState::CROUCH_DOWN)
	{
		jump->frame.y = 1;
		jumpTime += DELTA;
		isLanding = false;

		if (jumpTime > 0.3f || onWall)
		{
			isLanding = true;
			jumpTime = 0.0f;
			state = PlayerState::IDLE;
		}
	}

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
	if (state == PlayerState::IDLE)
		idle->Update();
	else if (state == PlayerState::RUN)
		run->Update();
	else if (state == PlayerState::DASH)
		dash->Update();
	else if (state == PlayerState::JUMP)
		jump->Update();
	else if (state == PlayerState::CROUCH)
		crouch->Update();
	else if (state == PlayerState::CROUCH_DOWN)
		jump->Update();;
}

void Player::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	if (state == PlayerState::IDLE)
		idle->Render();
	else if (state == PlayerState::RUN)
		run->Render();
	else if (state == PlayerState::DASH)
		dash->Render();
	else if (state == PlayerState::JUMP)
		jump->Render();
	else if (state == PlayerState::CROUCH)
		crouch->Render();
	else if (state == PlayerState::CROUCH_DOWN)
		jump->Render();
}



void Player::Control()
{
	dir = Vector2();

	// 상태 업데이트
	if (state == PlayerState::IDLE)
	{
		// idle -> walk
		if (INPUT->KeyPress('A'))
		{
			dir = LEFT;
			state = PlayerState::RUN;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = RIGHT;
			state = PlayerState::RUN;
		}

		// idle -> jump
		if (INPUT->KeyDown('W'))
		{
			Jump();
		}

		// idle -> crouch
		if (INPUT->KeyPress('S'))
		{
			state = PlayerState::CROUCH;
		}

		// idle -> dash
		if (INPUT->KeyDown(VK_SPACE))
		{
			Dash();
		}
	}
	else if (state == PlayerState::RUN)
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
			state = PlayerState::IDLE;
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
	}
	else if (state == PlayerState::JUMP)
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
	}
	else if (state == PlayerState::CROUCH)
	{
		// crouch -> idle
		if (!INPUT->KeyPress('S'))
			state = PlayerState::IDLE;

		// crouch -> run
		if (INPUT->KeyPress('A') || INPUT->KeyPress('D'))
			state = PlayerState::RUN;

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
			state = PlayerState::CROUCH_DOWN;
		}
	}

	if (dir == LEFT) dashDir = LEFT;
	else if (dir == RIGHT) dashDir = RIGHT;
}

void Player::Attack()
{
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		
	}
}

void Player::Dash()
{
	// 대시쿨타임이 충족되지 않았으면 리턴
	if (dashCooldown > 0) return;
	
	dashCooldown = dashDealay;
	dash->frame.x = 0;
	dashTargetPos.x = collider->GetWorldPos().x + (dashDir.x * 300);
	dashTargetPos.y = collider->GetWorldPos().y + 5;
	state = PlayerState::DASH;
}

void Player::Jump()
{
	collider->SetWorldPosY(collider->GetWorldPos().y + 5);
	gravity = -900;
	state = PlayerState::JUMP;
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
