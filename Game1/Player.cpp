#include "stdafx.h"
#include "DamageDisplayManager.h"
#include "Projectile.h"
#include "player_damageReflection.h"
#include "Creature.h"
#include "Player.h"

Player::Player()
{
	jumpTime = 0.0f;
	moveSpeed = 350.0f;
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
	ShowPlayerStat();

	lastPos = collider->GetWorldPos();
	collider->Update();

	// ü�¿� ���� ���°� ������ ����
	if (hp == maxHp)
	{
		isFullLife = true;
	}
	else
	{
		isFullLife = false;

		// ü���� 30% ��������	
		if (hp <= maxHp * 0.3f)
		{
			isLowLife = true;
		}
		else
		{
			isLowLife = false;
		}
	}

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

	// ��� ó��
	if (hp == 0 && CurrentState != State::DIE)
	{
		CurrentState = State::DIE;
	}

	// ü�� ���
	if (secTimer > 1.0f)
	{
		secTimer = 0.0f;

		// ���� ����� && ����óġŰƮ�� ������ ������
		if (isLowLife && hasFirstAidKit)
		{
			hp += 2;
			GM->damageDP->AddText(collider->GetWorldPos() + UP * collider->scale.y * 0.75f, 2, 5);
		}
	}
	else
	{
		secTimer += DELTA;
	}

	// ���� ������Ʈ
	if (CurrentState == State::IDLE)
	{
		// ���°� IDLE�ε�, �ٴڿ� ���� ������
		if (!onFloor && !onWall)
		{
			// jump ���·� ����
			jump->frame.y = 1;
			CurrentState = State::JUMP;
		}
	}
	else if (CurrentState == State::RUN)
	{
		collider->MoveWorldPos(dir * moveSpeed * moveSpeedScale * DELTA);
	}
	else if (CurrentState == State::DASH)
	{
		// dash ����ġ, �ð� ����
		dashWeight += DELTA * 3.0f;

		// dash ����ġ�� 1.0f �̻��̰ų� ���� �پ�������
		// dash -> PrevState
		if (dashWeight >= 1.0f || onWallSlide)
		{
			CurrentState = PrevState;
		}


		// dash
		collider->SetWorldPos(Vector2::Lerp(collider->GetWorldPos(), dashTargetPos, DELTA * 10.0f));

		// ������������ �̵�

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

		collider->MoveWorldPos(dir * moveSpeed * DELTA);
	}
	else if (CurrentState == State::CROUCH)
	{
		// ��ũ���� ���� �� �浹ü ũ�� ���̱�
		if (collider->scale.y != 70)
			collider->scale.y = 70;
	}
	else if (CurrentState == State::CROUCH_DOWN)
	{
		jump->frame.y = 1;
		jumpTime += DELTA;
		isLanding = false;

		// �ϰ� �� 0.3s �̻� ��� && �ٴڿ� ������� 
		if (jumpTime > 0.3f || onWall)
		{
			// ����
			isLanding = true;
			jumpTime = 0.0f;

			// crouch down -> idle
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::ATTACK)
	{
		// ���� �� �̵��� ���� (0.5��)
		collider->MoveWorldPos(dir * moveSpeed * moveSpeedScale * 0.5f * DELTA);

		// �������� ������ attack -> PrevState
		if (attack->frame.x == attack->maxFrame.x - 1)
		{
			CurrentState = PrevState;
		}
	}
	else if (CurrentState == State::CHARGING)
	{
		chargingTime = min(chargingTimeMax, chargingTime + DELTA * chargingTimeScale);

		// ��¡ �� ������ ����
		if (isCharging && charging->frame.x == chargingEndFrame)
		{
			charging->frame.x = chargingStartFrame;
		}

		// �������� ������ charging -> idle
		if (charging->frame.x == charging->maxFrame.x - 1)
		{
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::SKILL)
	{

		// �������� ������ charging -> idle
		if (skill->frame.x == skill->maxFrame.x - 1)
		{
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::DAMAGED)
	{
		// �������� �԰� �ִ� ������ �� ����
		collider->MoveWorldPos(dir * moveSpeed * moveSpeedScale * 0.5f * DELTA);

		// ������ ���� �� 0.1�� �Ŀ� damaged -> PrevState
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

	// �뽬 ���� ���� ���ð� ����
	if (dashRemainingCooldown > 0.0f)
		dashRemainingCooldown -= DELTA;

	// ��ų ���� ���� ���ð� ����	
	if (skillRemainingCooldown > 0.0f)
		skillRemainingCooldown -= DELTA;

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
		// skill �� �̵�
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
		// damaged �� �̵�
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
	// �����Ÿ���� �������� �ʾ����� ����
	if (dashRemainingCooldown > 0) return;

	dashRemainingCooldown = dashCooldown * dashCooldownScale;
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

void Player::activateItem(Item* item)
{
	this->maxHp += item->maxHp;
	this->maxMp += item->maxMp;
	hp = min(this->maxHp, this->hp + item->hp);
	mp = min(this->maxMp, this->mp + item->mp);

	this->damage += item->damage;
	this->defence += item->defence;

	this->attackRangeScale += item->attackRangeScale;

	this->damageScale += item->damageScale;
	this->normalDamageScale += item->normalDamageScale;
	this->skillDamageScale += item->skillDamageScale;
	this->chargingDamageScale += item->chargingDamageScale;
	this->chargingTimeScale += item->chargingTimeScale;
	this->fullLifeDamageScale += item->fullLifeDamageScale;
	this->lowLifeDamageScale += item->lowLifeDamageScale;

	this->damageRedution -= item->damageRedution;
	this->dodgeChance += item->dodgeChance;

	this->criticalChance += item->criticalChance;
	this->criticalDamage += item->criticalDamage;

	this->attackSpeed += item->attackSpeed;
	this->moveSpeed += item->moveSpeed;

	this->skillCooldownScale = max(0.0f, this->skillCooldownScale - item->skillCooldownScale);
	this->dashCooldownScale = max(0.0f, this->skillCooldownScale - item->dashCooldownScale);

	this->hasCandle = item->hasCandle;
	this->hasFirstAidKit = item->hasFirstAidKit;
	this->hasCactus = item->hasCactus;
	this->hasSyringe = item->hasSyringe;
	this->hasHeatedClub = item->hasHeatedClub;
}

void Player::actionsWhenDamaged(float damage)
{
	// ȸ�� Ȯ��
	if (RANDOM->Int(1, 100) <= dodgeChance)
	{
		// ȸ�� ����
		// ȸ�� FX ����� ����
		return;
	}

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

	// ������ ������ ������
	if (hasCactus)
	{
		// �ֺ��� ������ �ݻ�
		DamageReflection(damage);
	}

	// �ֻ�� ������ ������
	if (hasSyringe)
	{
		// �ֻ����� ���� 5% Ȯ����
		if (RANDOM->Int(1, 100) <= 5)
		{
			// ü�� ȸ��
			hp = min(maxHp, hp + 10);
			GM->damageDP->AddText(collider->GetWorldPos(), 10, 5);
		}
	}

	// ���� ��ŭ ������ ����
	damage = max(0, damage - defence);

	// ���ȿ�� ��ŭ ������ ����
	damage *= damageRedution;

	// ü�� ����
	hp = max(hp - damage, 0);

	// ������ �ؽ�Ʈ ���
	Vector2 tempSpawnPos = collider->GetWorldPos() + Vector2(0, collider->scale.y * 0.5f);
	GM->damageDP->AddText(tempSpawnPos, damage, 2);
}

void Player::DamageReflection(float reflectDamage)
{
	// ������ �ݻ�
	static float lastReflectTime = 0;
	static float timeSinceLastReflectTime = 0;

	float currentTime = TIMER->GetWorldTime();
	float elapsedTime = currentTime - lastReflectTime;

	if (elapsedTime >= timeSinceLastReflectTime)
	{
		// �߻� ��ġ ���
		Vector2 spawnPos = collider->GetWorldPos() + Vector2(0, collider->scale.y * 0.5f);

		// ���ݷ� ���
		float totalDamage = ((reflectDamage * 2.0f) + this->damage) * damageScale;
		if (isFullLife) totalDamage *= fullLifeDamageScale;
		else if (isLowLife) totalDamage *= lowLifeDamageScale;

		// ź����
		player_damageReflection* proj = new player_damageReflection
		(
			spawnPos,										// ������ġ
			dir,										    // ����
			5,   											// �߻�ü �ӵ�
			1, 												// ��Ÿ�
			totalDamage,									// ���ݷ�
			1,												// �����
			1												// ���߹���
		);

		//���Ϳ� ź push
		projectiles.emplace_back(proj);

		// ���Ӱ��
		lastReflectTime = currentTime;
		timeSinceLastReflectTime = 1.0f / attackSpeed;
	}
}

void Player::ShowPlayerStat()
{
	if (!ImGui::CollapsingHeader(u8"�÷��̾�"))
		return;



	// ��� �÷��̾� ���� ���
	//if (ImGui::TreeNode(u8"�����"))
	//{
		ImGui::Text(u8"��ǥX: %f\n", collider->GetWorldPos().x);
		ImGui::Text(u8"��ǥY: %f\n", collider->GetWorldPos().y); 
		ImGui::Text(u8"���� : %d\n", CurrentState);
		ImGui::Text(u8"�߷�: %f\n\n", gravity);
	//}

	//if (ImGui::TreeNode(u8"����"))
	//{
		ImGui::Text(u8"ü��: %d / %d \n", hp, maxHp);
		ImGui::Text(u8"����: %d / %d \n\n", mp, maxMp);

		ImGui::Text(u8"���ݷ�: %d \n", damage);
		ImGui::Text(u8"����: %d \n", defence);
		ImGui::Text(u8"ȸ����: %d \n", dodgeChance);
		ImGui::Text(u8"���� ����: %f \n\n", damageRedution);

		ImGui::Text(u8"���� �ӵ�: %f \n", attackSpeed);
		ImGui::Text(u8"���� �ӵ� ������: %f \n", attackSpeedScale);
		ImGui::Text(u8"�̵� �ӵ�: %f \n", moveSpeed);
		ImGui::Text(u8"�̵� �ӵ� ������: %f \n\n", moveSpeedScale);

		ImGui::Text(u8"ġ��Ÿ Ȯ��: %d % \n", criticalChance);
		ImGui::Text(u8"ġ��Ÿ ���ط�: %f \n\n", criticalDamage);

		ImGui::Text(u8"��� ���ݷ� ������: %f \n", damageScale);
		ImGui::Text(u8"�Ϲ� ���ݷ� ������: %f \n", normalDamageScale);
		ImGui::Text(u8"Ǯ������ ���ݷ� ������: %f \n", fullLifeDamageScale);
		ImGui::Text(u8"�ο������ ���ݷ� ������: %f \n", lowLifeDamageScale);
		ImGui::Text(u8"���� ���� ������: %f \n\n", attackRangeScale);
		
		ImGui::Text(u8"��ų ���ݷ� ������: %f \n", skillDamageScale);
		ImGui::Text(u8"��ų ��Ÿ�� ������: %f \n\n", skillCooldownScale);
		
		ImGui::Text(u8"�뽬 ��Ÿ�� ������: %f \n\n", dashCooldownScale);

		ImGui::Text(u8"��¡�ð� : %f\n", chargingTime);
		ImGui::Text(u8"��¡ �ð� ������: %f \n", chargingTimeScale);
		ImGui::Text(u8"��¡ ���ݷ� ������: %f \n", chargingDamageScale);
	//}

	//if (ImGui::TreeNode(u8"��Ÿ"))
	//{
		ImGui::Text(u8"Ǯ������ : %d\n", isFullLife);
		ImGui::Text(u8"�ο������ : %d\n\n", isLowLife);

		ImGui::Text("onFloor : %d\n", onFloor);
		ImGui::Text("onWall : %d\n", onWall);
		ImGui::Text("onWallside : %d\n", onWallSlide);
		ImGui::Text(u8"isCharging : %d\n", isCharging);
		ImGui::Text(u8"isLanding : %d\n\n", isLanding);

		ImGui::Text(u8"hasFirstAidKit : %d\n", hasFirstAidKit);
		ImGui::Text(u8"hasCactus : %d\n", hasCactus);
		ImGui::Text(u8"hasSyringe : %d\n", hasSyringe);
		ImGui::Text(u8"hasHeatedClub : %d\n", hasHeatedClub);
		ImGui::Text(u8"hasCandle : %d\n", hasCandle);
	//}
}
