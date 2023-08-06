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

	// 체력에 따른 상태값 설정을 위한
	if (hp == maxHp)
	{
		isFullLife = true;
	}
	else
	{
		isFullLife = false;

		// 체력이 30% 이하인지	
		if (hp <= maxHp * 0.3f)
		{
			isLowLife = true;
		}
		else
		{
			isLowLife = false;
		}
	}

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

	// 체력 재생
	if (secTimer > 1.0f)
	{
		secTimer = 0.0f;

		// 낮은 생명력 && 응급처치키트를 가지고 있으면
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
		collider->MoveWorldPos(dir * moveSpeed * moveSpeedScale * DELTA);
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

		collider->MoveWorldPos(dir * moveSpeed * DELTA);
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
		collider->MoveWorldPos(dir * moveSpeed * moveSpeedScale * 0.5f * DELTA);

		// 프레임이 끝나면 attack -> PrevState
		if (attack->frame.x == attack->maxFrame.x - 1)
		{
			CurrentState = PrevState;
		}
	}
	else if (CurrentState == State::CHARGING)
	{
		chargingTime = min(chargingTimeMax, chargingTime + DELTA * chargingTimeScale);

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
		collider->MoveWorldPos(dir * moveSpeed * moveSpeedScale * 0.5f * DELTA);

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
	// 회피 확률
	if (RANDOM->Int(1, 100) <= dodgeChance)
	{
		// 회피 성공
		// 회피 FX 출력을 위한
		return;
	}

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

	// 선인장 아이템 보유시
	if (hasCactus)
	{
		// 주변에 데미지 반사
		DamageReflection(damage);
	}

	// 주사기 아이템 보유시
	if (hasSyringe)
	{
		// 주사위를 굴려 5% 확률로
		if (RANDOM->Int(1, 100) <= 5)
		{
			// 체력 회복
			hp = min(maxHp, hp + 10);
			GM->damageDP->AddText(collider->GetWorldPos(), 10, 5);
		}
	}

	// 방어력 만큼 데미지 차감
	damage = max(0, damage - defence);

	// 방어효율 만큼 데미지 차감
	damage *= damageRedution;

	// 체력 감소
	hp = max(hp - damage, 0);

	// 데미지 텍스트 출력
	Vector2 tempSpawnPos = collider->GetWorldPos() + Vector2(0, collider->scale.y * 0.5f);
	GM->damageDP->AddText(tempSpawnPos, damage, 2);
}

void Player::DamageReflection(float reflectDamage)
{
	// 데미지 반사
	static float lastReflectTime = 0;
	static float timeSinceLastReflectTime = 0;

	float currentTime = TIMER->GetWorldTime();
	float elapsedTime = currentTime - lastReflectTime;

	if (elapsedTime >= timeSinceLastReflectTime)
	{
		// 발사 위치 계산
		Vector2 spawnPos = collider->GetWorldPos() + Vector2(0, collider->scale.y * 0.5f);

		// 공격력 계산
		float totalDamage = ((reflectDamage * 2.0f) + this->damage) * damageScale;
		if (isFullLife) totalDamage *= fullLifeDamageScale;
		else if (isLowLife) totalDamage *= lowLifeDamageScale;

		// 탄생성
		player_damageReflection* proj = new player_damageReflection
		(
			spawnPos,										// 생성위치
			dir,										    // 각도
			5,   											// 발사체 속도
			1, 												// 사거리
			totalDamage,									// 공격력
			1,												// 관통력
			1												// 폭발범위
		);

		//벡터에 탄 push
		projectiles.emplace_back(proj);

		// 공속계산
		lastReflectTime = currentTime;
		timeSinceLastReflectTime = 1.0f / attackSpeed;
	}
}

void Player::ShowPlayerStat()
{
	if (!ImGui::CollapsingHeader(u8"플레이어"))
		return;



	// 모든 플레이어 정보 출력
	//if (ImGui::TreeNode(u8"디버그"))
	//{
		ImGui::Text(u8"좌표X: %f\n", collider->GetWorldPos().x);
		ImGui::Text(u8"좌표Y: %f\n", collider->GetWorldPos().y); 
		ImGui::Text(u8"상태 : %d\n", CurrentState);
		ImGui::Text(u8"중력: %f\n\n", gravity);
	//}

	//if (ImGui::TreeNode(u8"상태"))
	//{
		ImGui::Text(u8"체력: %d / %d \n", hp, maxHp);
		ImGui::Text(u8"마나: %d / %d \n\n", mp, maxMp);

		ImGui::Text(u8"공격력: %d \n", damage);
		ImGui::Text(u8"방어력: %d \n", defence);
		ImGui::Text(u8"회피율: %d \n", dodgeChance);
		ImGui::Text(u8"피해 감소: %f \n\n", damageRedution);

		ImGui::Text(u8"공격 속도: %f \n", attackSpeed);
		ImGui::Text(u8"공격 속도 스케일: %f \n", attackSpeedScale);
		ImGui::Text(u8"이동 속도: %f \n", moveSpeed);
		ImGui::Text(u8"이동 속도 스케일: %f \n\n", moveSpeedScale);

		ImGui::Text(u8"치명타 확률: %d % \n", criticalChance);
		ImGui::Text(u8"치명타 피해량: %f \n\n", criticalDamage);

		ImGui::Text(u8"모든 공격력 스케일: %f \n", damageScale);
		ImGui::Text(u8"일반 공격력 스케일: %f \n", normalDamageScale);
		ImGui::Text(u8"풀라이프 공격력 스케일: %f \n", fullLifeDamageScale);
		ImGui::Text(u8"로우라이프 공격력 스케일: %f \n", lowLifeDamageScale);
		ImGui::Text(u8"공격 범위 스케일: %f \n\n", attackRangeScale);
		
		ImGui::Text(u8"스킬 공격력 스케일: %f \n", skillDamageScale);
		ImGui::Text(u8"스킬 쿨타임 스케일: %f \n\n", skillCooldownScale);
		
		ImGui::Text(u8"대쉬 쿨타임 스케일: %f \n\n", dashCooldownScale);

		ImGui::Text(u8"차징시간 : %f\n", chargingTime);
		ImGui::Text(u8"차징 시간 스케일: %f \n", chargingTimeScale);
		ImGui::Text(u8"차징 공격력 스케일: %f \n", chargingDamageScale);
	//}

	//if (ImGui::TreeNode(u8"기타"))
	//{
		ImGui::Text(u8"풀라이프 : %d\n", isFullLife);
		ImGui::Text(u8"로우라이프 : %d\n\n", isLowLife);

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
