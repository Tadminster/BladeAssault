#include "stdafx.h"

#include "Projectile.h"
#include "kill_barehand_atk.h"
#include "kill_barehand_ChargingAtk.h"

#include "Creature.h"
#include "Player.h"
#include "Player_Kill.h"



Player_kill::Player_kill()
{
	idle = new ObImage(L"kill_barehand_idle.png");
	run = new ObImage(L"kill_barehand_run.png");
	dash = new ObImage(L"kill_barehand_dash.png");
	jump = new ObImage(L"kill_barehand_jump.png");
	crouch = new ObImage(L"kill_barehand_crouch.png");
	attack = new ObImage(L"kill_barehand_sub_attack.png");
	charging = new ObImage(L"kill_barehand_charging.png");
	damaged = new ObImage(L"kill_barehand_damaged.png");
	spawn = new ObImage(L"kill_barehand_spawn.png");
	die = new ObImage(L"kill_barehand_die.png");
	shadow = new ObImage(L"character_shadow.png");
	chargingFx = new ObImage(L"kill_barehand_chargingFx.png");
	//hasAxis = true;

	collider->pivot = OFFSET_B;
	collider->isFilled = false;
	collider->scale.x = 60;
	collider->scale.y = 100;

	idle->pivot = OFFSET_B;
	idle->SetParentRT(*collider);
	idle->maxFrame.x = 6;
	idle->maxFrame.y = 1;
	idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3;
	idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3;
	idle->SetLocalPosY(-collider->scale.y * 0.3f);
	idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	run->pivot = OFFSET_B;
	run->SetParentRT(*collider);
	run->maxFrame.x = 8;
	run->maxFrame.y = 1;
	run->scale.x = run->imageSize.x / run->maxFrame.x * 3;
	run->scale.y = run->imageSize.y / run->maxFrame.y * 3;
	run->SetLocalPosY(-collider->scale.y * 0.3f);
	run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	dash->pivot = OFFSET_B;
	dash->SetParentRT(*collider);
	dash->maxFrame.x = 5;
	dash->maxFrame.y = 1;
	dash->scale.x = dash->imageSize.x / dash->maxFrame.x * 3;
	dash->scale.y = dash->imageSize.y / dash->maxFrame.y * 3;
	dash->SetLocalPosY(-collider->scale.y * 0.3f);
	dash->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	jump->pivot = OFFSET_B;
	jump->SetParentRT(*collider);
	jump->maxFrame.x = 2;
	jump->maxFrame.y = 2;
	jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3;
	jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3;
	jump->SetLocalPosY(-collider->scale.y * 0.3f);
	jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	crouch->pivot = OFFSET_B;
	crouch->SetParentRT(*collider);
	crouch->maxFrame.x = 6;
	crouch->maxFrame.y = 1;
	crouch->scale.x = crouch->imageSize.x / crouch->maxFrame.x * 3;
	crouch->scale.y = crouch->imageSize.y / crouch->maxFrame.y * 3;
	crouch->SetLocalPosY(-collider->scale.y * 0.3f);
	crouch->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	attack->pivot = OFFSET_B;
	attack->SetParentRT(*collider);
	attack->maxFrame.x = 4;
	attack->maxFrame.y = 1;
	attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3;
	attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3;
	attack->SetLocalPosY(-collider->scale.y * 0.3f);
	attack->ChangeAnim(ANIMSTATE::ONCE, 0.085f, true);

	charging->pivot = OFFSET_B;
	charging->SetParentRT(*collider);
	charging->maxFrame.x = 7;
	charging->maxFrame.y = 1;
	charging->scale.x = charging->imageSize.x / charging->maxFrame.x * 3;
	charging->scale.y = charging->imageSize.y / charging->maxFrame.y * 3;
	charging->SetLocalPosY(-collider->scale.y * 0.3f);
	charging->ChangeAnim(ANIMSTATE::LOOP, 0.085f, true);

	chargingFx->pivot = OFFSET_B;
	chargingFx->SetParentRT(*collider);
	chargingFx->maxFrame.x = 16;
	chargingFx->maxFrame.y = 1;
	chargingFx->scale.x = chargingFx->imageSize.x / chargingFx->maxFrame.x;
	chargingFx->scale.y = chargingFx->imageSize.y / chargingFx->maxFrame.y;
	chargingFx->color.w = 0.35f;
	chargingFx->SetLocalPosY(-collider->scale.y * 0.62f);
	chargingFx->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	damaged->pivot = OFFSET_B;
	damaged->SetParentRT(*collider);
	damaged->SetLocalPosY(-collider->scale.y);
	damaged->maxFrame.x = 1;
	damaged->maxFrame.y = 1;
	damaged->scale.x = damaged->imageSize.x / damaged->maxFrame.x * 2.6;
	damaged->scale.y = damaged->imageSize.y / damaged->maxFrame.y * 2.6;
	damaged->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	spawn->pivot = OFFSET_B;
	spawn->SetParentRT(*collider);
	spawn->SetLocalPosY(-collider->scale.y * 0.7f);
	spawn->maxFrame.x = 13;
	spawn->maxFrame.y = 1;
	spawn->scale.x = spawn->imageSize.x / spawn->maxFrame.x * 3;
	spawn->scale.y = spawn->imageSize.y / spawn->maxFrame.y * 3;
	spawn->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	die->pivot = OFFSET_B;
	die->SetParentRT(*collider);
	die->SetLocalPosY(-collider->scale.y * 0.3f);
	die->maxFrame.x = 11;
	die->maxFrame.y = 1;
	die->scale.x = die->imageSize.x / die->maxFrame.x * 3;
	die->scale.y = die->imageSize.y / die->maxFrame.y * 3;
	die->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	shadow->pivot = OFFSET_B;
	shadow->SetParentRT(*collider);
	shadow->SetLocalPosY(-idle->scale.y * 0.2f);
	shadow->maxFrame.x = 1;
	shadow->maxFrame.y = 1;
	shadow->scale.x = shadow->imageSize.x / shadow->maxFrame.x * 2.4;
	shadow->scale.y = shadow->imageSize.y / shadow->maxFrame.y * 2.4;
	shadow->color.w = 0.2f;
	shadow->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	chargingTime = 0.0f;
	chargingTimeMax = 3.0f;
	chargingStartFrame = 1;
	chargingEndFrame = 4;

	hp = 150;
	maxHp = 150;
	mp = 120;
	maxMp = 120;

	damage = 10;
	attackRange = 500;
	attackSpeed = 3.0f;
	jumpSpeed = 900.0f;

}


void Player_kill::Update()
{
	Player::Update();
	
	// 스킨 방향 설정
	if (dir == LEFT)
	{
		charging->reverseLR = true;
		chargingFx->SetLocalPosX(-collider->scale.x);

	}
	else if (dir == RIGHT)
	{
		charging->reverseLR = false;
		chargingFx->SetLocalPosX(collider->scale.x);
	}

	if (CurrentState == State::CHARGING)
		chargingFx->Update();
}

void Player_kill::Render()
{
	Player::Render();

	if (CurrentState == State::CHARGING)
		chargingFx->Render();
}

void Player_kill::Attack()
{
	static float lastShotTime = 0;
	static float timeSinceLastTime = 0;

	float currentTime = TIMER->GetWorldTime();
	float elapsedTime = currentTime - lastShotTime;

	if (elapsedTime >= timeSinceLastTime)
	{
		Player::Attack();

		// 발사 위치 계산
		Vector2 spawnPos = collider->GetWorldPos() + lastDir * collider->scale.x + (UP * collider->scale.y * 0.65);

		// 탄생성
		kill_barehand_atk* proj = new kill_barehand_atk
		(
			spawnPos,										// 생성위치
			lastDir,										// 각도
			700,											// 발사체 속도
			attackRange,									// 사거리
			damage,											// 공격력
			1,												// 관통력
			1												// 폭발범위
		);

		//벡터에 탄 push
		projectiles.emplace_back(proj);

		// 공속계산
		lastShotTime = currentTime;
		timeSinceLastTime = 1.0f / attackSpeed;
	}
}

void Player_kill::ChargingAttack()
{
	Player::ChargingAttack();

	// 발사 위치 계산
	Vector2 spawnPos = collider->GetWorldPos() + lastDir * collider->scale.x + (UP * collider->scale.y * 0.65);

	// 탄생성
	kill_barehand_ChargingAtk* proj = new kill_barehand_ChargingAtk
	(
		spawnPos,										// 생성위치
		lastDir,										// 각도
		3,												// 발사체 속도
		1,												// 사거리
		damage,											// 공격력
		99,												// 관통력
		1												// 폭발범위
	);

	//벡터에 탄 push
	projectiles.emplace_back(proj);
}
