#include "stdafx.h"
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

	dashCooldown = 0.0f;
	dashDealay = 2.0;
}

Player::~Player()
{
	Creature::~Creature();
	delete dash;
	delete crouch;
	delete damaged;
	delete die;
}

void Player::Init()
{
	CurrentState = State::STANDBY;
	lastDir = RIGHT;

	gravity = 0.0f;

	onFloor = false;
	isLanding = true;
	damageTaken = false;
}

void Player::Update()
{
	ImGui::Text("gravity : %f\n", GM->player->gravity);
	ImGui::Text("playerState : %d\n", GM->player->CurrentState);

	lastPos = collider->GetWorldPos();
	collider->Update();

	// ��Ʈ��
	Control();

	// ��Ų ���� ����
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

	// ��� ó��
	if (hp == 0 && CurrentState != State::DIE)
	{
		CurrentState = State::DIE;
	}

	// ���� ������Ʈ
	if (CurrentState == State::IDLE)
	{
		if (!onFloor && !onWall)
		{
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
		static float weight = 0;
		weight += DELTA * 3;
		if (weight >= 1.0f || onWallSlide)
		{
			weight = 0;
			CurrentState = PrevState;
		}

		collider->SetWorldPos(Vector2::Lerp(collider->GetWorldPos(), dashTargetPos, 0.015f));
	}
	else if (CurrentState == State::JUMP)
	{
		// ���
		if (gravity < 0)
		{
			jump->frame.y = 0;
			isLanding = false;

		}
		// �ϰ�
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
		if (collider->scale.y != 70)
			collider->scale.y = 70;
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
	else if (CurrentState == State::ATTACK)
	{
		collider->MoveWorldPos(dir * moveSpeed * 0.5 * DELTA);

		if (attack->frame.x == attack->maxFrame.x - 1)
		{
			CurrentState = PrevState;
		}
	}
	else if (CurrentState == State::CHARGING)
	{
		chargingTime = min(chargingTimeMax, chargingTime + DELTA);

	}
	else if (CurrentState == State::DAMAGED)
	{
		collider->MoveWorldPos(dir * moveSpeed * 0.5 * DELTA);

		if (timeOfDamaged + 0.1f < TIMER->GetWorldTime())
		{
			CurrentState = PrevState;
		}
	}
	else if (CurrentState == State::SPAWN)
	{
		// SPAWN ���
		if (spawn->frame.x == spawn->maxFrame.x - 1)
		{
			CurrentState = State::IDLE;
		}
	}

	// �뽬 ��Ÿ��
	if (dashCooldown > 0.0f)
		dashCooldown -= DELTA;

	// 1. �ٴڰ� ������ ���� ��
	// 2. SPAWN �̳� STANDBY ���°� �ƴ� ��
	// �߷�����
	if (!onWall && !onFloor 
		&& CurrentState != State::SPAWN
		&& CurrentState != State::STANDBY)
	{
		gravity += 1500.0f * DELTA;
		collider->MoveWorldPos(DOWN * gravity * DELTA);
	}

	// ź�� ���Ϳ� �浹�ϸ�
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr) { return pr->hasCollideWithMonster(); }
		),
		projectiles.end()
	);

	// ź�� �����Ÿ� �̻� ������� ����
	projectiles.erase(
		std::remove_if
		(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile* pr) { return pr->hasTraveledTooFar(); }
		),
		projectiles.end()
	);


	// �÷��̾��� ź ������Ʈ
	for (auto& proj : projectiles)
		proj->Update();

	if (onWall || onFloor)
		shadow->Update();

	// ��Ÿ ������Ʈ
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
		attack->Update();
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


	// �ٴڿ� ���� ���� �׸��ڸ� �׸���
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
		attack->Render();
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
			hp = min(maxHp, hp + maxHp * 0.1);
		}

		if (INPUT->KeyDown(VK_OEM_MINUS))
		{
			hp = max(0, hp - maxHp * 0.1);
			damageTaken = true;
		}
	}


	// ���� ������Ʈ
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
				ChargingAttack();
			}
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
	}
	else if (CurrentState == State::JUMP)
	{
		// jump �� �̵�
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


		// attack �� �̵�
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
			//attack->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
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
	else if (CurrentState == State::DAMAGED)
	{
		// DAMAGED �� �̵�
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
	chargingTime = 0;
	PrevState = CurrentState;
	CurrentState = State::ATTACK;
}

void Player::ChargingAttack()
{
	//attack->frame.x = 0;
	CurrentState = State::CHARGING;
}

void Player::Dash()
{
	// �����Ÿ���� �������� �ʾ����� ����
	if (dashCooldown > 0) return;

	dashCooldown = dashDealay;
	dash->frame.x = 0;
	dashTargetPos.x = collider->GetWorldPos().x + (lastDir.x * 300);
	dashTargetPos.y = collider->GetWorldPos().y + 5;

	PrevState = CurrentState;
	if (PrevState == State::ATTACK)
		if (onFloor || onWall) PrevState = State::IDLE;
		else PrevState = State::JUMP;
	CurrentState = State::DASH;
}

void Player::actionsWhenDamaged(int value)
{
	// ��� �߿��� �������� ���� ����
	if (CurrentState == State::DASH)
		return;

	// ���¸� ������ �������� ����
	if (CurrentState == State::IDLE || CurrentState == State::RUN)
		CurrentState = State::DAMAGED;
	
	// ������ ���� FX ����� ����
	damageTaken = true;

	// ��Ų �÷� ����
	//damaged->color = Vector4(0.1, 0.1, 0.1, 0.5);
	
	// ������ ���� �ð� ���
	timeOfDamaged = TIMER->GetWorldTime();

	// ������ ����
	int damage = min(value + defence, 0);
	// ü�� ����
	hp = max(hp + damage, 0);
}
