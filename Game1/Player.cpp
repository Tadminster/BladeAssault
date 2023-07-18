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

	speed = 350.0f;
	jumpSpeed = 700;
	jumpTime = 0.0f;

	gravity = 0.0f;
	onFloor = false;
	isLanding = true;

	jumpCount = 0;
	jumpCountMax = 2;
}

void Player::Update()
{
	ImGui::Text("gravity : %f\n", GM->player->gravity);

	lastPos = collider->GetWorldPos();
	collider->Update();

	// 컨트롤
	Control();

	// 스킨 방향 설정
	if (dir == LEFT)
	{
		idle->reverseLR = true;
		run->reverseLR = true;
		jump->reverseLR = true;
		crouch->reverseLR = true;
	}
	else if (dir == RIGHT)
	{
		idle->reverseLR = false;
		run->reverseLR = false;
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


	// 중력
	//if (!onFloor)
	if (!onWall && !onFloor)
	{
		gravity += 1500.0f * DELTA;
		collider->MoveWorldPos(DOWN * gravity * DELTA);
	}

	collider->Update();
	idle->Update();
	run->Update();
	jump->Update();
	crouch->Update();
}

void Player::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	if (state == PlayerState::IDLE)
		idle->Render();
	else if (state == PlayerState::RUN)
		run->Render();
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
			collider->SetWorldPosY(collider->GetWorldPos().y + 5);
			gravity = -900;
			state = PlayerState::JUMP;
		}

		// idle -> crouch
		if (INPUT->KeyPress('S'))
		{
			state = PlayerState::CROUCH;
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
			collider->SetWorldPosY(collider->GetWorldPos().y + 5);
			gravity = -900;
			state = PlayerState::JUMP;
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
		
		// jump -> jump
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
			collider->SetWorldPosY(collider->GetWorldPos().y + 5);
			gravity = -900;
			state = PlayerState::JUMP;
		}

		// crouch -> down
		if (INPUT->KeyDown(VK_SHIFT))
		{
			jumpCount = 1;
			gravity = 0;
			state = PlayerState::CROUCH_DOWN;
		}
	}
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
	GoBack();
}

void Player::GoBack()
{
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
