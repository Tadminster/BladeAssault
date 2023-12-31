#include "stdafx.h"

#include "Projectile.h"
#include "kill_barehand_atk.h"
#include "kill_barehand_ChargingAtk.h"
#include "kill_barehand_skill.h"

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
	skill = new ObImage(L"kill_core_ignition_flare_blitz.png");
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
	idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3.0f;
	idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3.0f;
	idle->SetLocalPosY(-collider->scale.y * 0.3f);
	idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	run->pivot = OFFSET_B;
	run->SetParentRT(*collider);
	run->maxFrame.x = 8;
	run->maxFrame.y = 1;
	run->scale.x = run->imageSize.x / run->maxFrame.x * 3.0f;
	run->scale.y = run->imageSize.y / run->maxFrame.y * 3.0f;
	run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);
	run->SetLocalPosY(-collider->scale.y * 0.3f);

	dash->pivot = OFFSET_B;
	dash->SetParentRT(*collider);
	dash->maxFrame.x = 5;
	dash->maxFrame.y = 1;
	dash->scale.x = dash->imageSize.x / dash->maxFrame.x * 3.0f;
	dash->scale.y = dash->imageSize.y / dash->maxFrame.y * 3.0f;
	dash->SetLocalPosY(-collider->scale.y * 0.3f);
	dash->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	jump->pivot = OFFSET_B;
	jump->SetParentRT(*collider);
	jump->maxFrame.x = 2;
	jump->maxFrame.y = 2;
	jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3.0f;
	jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3.0f;
	jump->SetLocalPosY(-collider->scale.y * 0.3f);
	jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	crouch->pivot = OFFSET_B;
	crouch->SetParentRT(*collider);
	crouch->maxFrame.x = 6;
	crouch->maxFrame.y = 1;
	crouch->scale.x = crouch->imageSize.x / crouch->maxFrame.x * 3.0f;
	crouch->scale.y = crouch->imageSize.y / crouch->maxFrame.y * 3.0f;
	crouch->SetLocalPosY(-collider->scale.y * 0.3f);
	crouch->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	attack->pivot = OFFSET_B;
	attack->SetParentRT(*collider);
	attack->maxFrame.x = 4;
	attack->maxFrame.y = 1;
	attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3.0f;
	attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3.0f;
	attack->SetLocalPosY(-collider->scale.y * 0.3f);
	attack->ChangeAnim(ANIMSTATE::ONCE, 0.085f, true);

	charging->pivot = OFFSET_B;
	charging->SetParentRT(*collider);
	charging->maxFrame.x = 7;
	charging->maxFrame.y = 1;
	charging->scale.x = charging->imageSize.x / charging->maxFrame.x * 3.0f;
	charging->scale.y = charging->imageSize.y / charging->maxFrame.y * 3.0f;
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

	skill->pivot = OFFSET_B;
	skill->SetParentRT(*collider);
	skill->maxFrame.x = 31;
	skill->maxFrame.y = 1;
	skill->scale.x = skill->imageSize.x / skill->maxFrame.x * 3.2f;
	skill->scale.y = skill->imageSize.y / skill->maxFrame.y * 3.2f;
	skill->SetLocalPosY(-collider->scale.y * 0.5f);
	skill->ChangeAnim(ANIMSTATE::ONCE, 0.065f, true);

	damaged->pivot = OFFSET_B;
	damaged->SetParentRT(*collider);
	damaged->SetLocalPosY(-collider->scale.y);
	damaged->maxFrame.x = 1;
	damaged->maxFrame.y = 1;
	damaged->scale.x = damaged->imageSize.x / damaged->maxFrame.x * 2.6f;
	damaged->scale.y = damaged->imageSize.y / damaged->maxFrame.y * 2.6f;
	damaged->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	spawn->pivot = OFFSET_B;
	spawn->SetParentRT(*collider);
	spawn->SetLocalPosY(-collider->scale.y * 0.7f);
	spawn->maxFrame.x = 13;
	spawn->maxFrame.y = 1;
	spawn->scale.x = spawn->imageSize.x / spawn->maxFrame.x * 3.0f;
	spawn->scale.y = spawn->imageSize.y / spawn->maxFrame.y * 3.0f;
	spawn->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	die->pivot = OFFSET_B;
	die->SetParentRT(*collider);
	die->SetLocalPosY(-collider->scale.y * 0.3f);
	die->maxFrame.x = 11;
	die->maxFrame.y = 1;
	die->scale.x = die->imageSize.x / die->maxFrame.x * 3.0f;
	die->scale.y = die->imageSize.y / die->maxFrame.y * 3.0f;
	die->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	shadow->pivot = OFFSET_B;
	shadow->SetParentRT(*collider);
	shadow->SetLocalPosY(-idle->scale.y * 0.2f);
	shadow->maxFrame.x = 1;
	shadow->maxFrame.y = 1;
	shadow->scale.x = shadow->imageSize.x / shadow->maxFrame.x * 2.4f;
	shadow->scale.y = shadow->imageSize.y / shadow->maxFrame.y * 2.4f;
	shadow->color.w = 0.2f;
	shadow->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	chargingTime			= 0.0f;			// 차징
	chargingTimeMax			= 3.0f;			// 차징 최대 시간
	chargingStartFrame		= 1;
	chargingEndFrame		= 4;

	skillCooldown			= 4.0f;			// 스킬 쿨타임
	skillRemainingCooldown	= 0.0f;			// 스킬 남은 쿨타임
	skillManaCost			= 30;			// 스킬 마나 소모량

	hp						= 150;
	maxHp					= 150;
	mp						= 120;
	maxMp					= 120;

	damage					= 10;			// 캐릭터의 기준 공격력
	defence					= 0;			// 캐릭터의 기준 방어력
	attackRange				= 500;			// 기본 공격 사거리
	attackSpeed				= 3.0f;			// 기본 공격 속도
	jumpSpeed				= 900.0f;

	isSkill1				= false;
	isSkill2				= false;
	isSkill3				= false;
}


void Player_kill::Update()
{

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

	if (CurrentState == State::SKILL)
	{
		// 카메라 흔들림 효과
		if (skill->frame.x > 5 && skill->frame.x < 24)
		{
			CAM->position.x += (RANDOM->Int(0, 1) ? 2 : -2);
			CAM->position.y += (RANDOM->Int(0, 1) ? 2 : -2);
		}

		// 첫번째 공격
		if (skill->frame.x == 6 && isSkill1)
		{
			isSkill1 = false;
			SkillAttack();
		}
		// 두번째 공격
		else if (skill->frame.x == 11 && isSkill2)
		{
			isSkill2 = false;
			SkillAttack();
		}
		// 세번째 공격
		else if (skill->frame.x == 16 && isSkill3)
		{
			isSkill3 = false;
			SkillAttack();
		}

		// 마지막 프레임에 도달하면 skill -> idle
		if (skill->frame.x == skill->maxFrame.x - 1)
		{
			CurrentState = State::IDLE;
		}
	}

	if (CurrentState == State::CHARGING)
	{
		SOUND->Play("kill_charging");
		chargingFx->Update();
	}
	else
	{
		SOUND->Stop("kill_charging");
	}

	Player::Update();
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

		// 공격력 계산
		float totalDamage = damage * (damageScale + normalDamageScale);
		if (isFullLife) totalDamage *= fullLifeDamageScale;
		else if (isLowLife) totalDamage *= lowLifeDamageScale;

		// 탄생성
		kill_barehand_atk* proj = new kill_barehand_atk
		(
			spawnPos,										// 생성위치
			lastDir,										// 각도
			700,											// 발사체 속도
			attackRange * attackRangeScale,					// 사거리
			totalDamage,									// 공격력
			1,												// 관통력
			1,												// 폭발범위
			criticalChance									// 치명타 확률
		);

		//벡터에 탄 push
		projectiles.emplace_back(proj);

		// 공속계산
		lastShotTime = currentTime;
		timeSinceLastTime = 1.0f / attackSpeed * attackSpeedScale;

		// 사운드 재생
		SOUND->Stop("kill_attack");
		SOUND->Play("kill_attack");
	}
}

void Player_kill::ChargingAttack()
{


	// 발사 위치 계산
	Vector2 spawnPos = collider->GetWorldPos() + lastDir * collider->scale.x + (UP * collider->scale.y * 0.65);

	// 공격력 계산
	float totalDamage = damage * (damageScale + chargingDamageScale) * chargingTime;
	if (isFullLife) totalDamage *= fullLifeDamageScale;
	else if (isLowLife) totalDamage *= lowLifeDamageScale;

	// 탄생성
	kill_barehand_ChargingAtk* proj = new kill_barehand_ChargingAtk
	(
		spawnPos,										// 생성위치
		lastDir,										// 각도
		3,												// 발사체 속도
		1,												// 사거리
		totalDamage,									// 공격력
		99,												// 관통력
		1,												// 폭발범위
		criticalChance									// 치명타 확률
	);

	// chargingTime = 0.0f;
	Player::ChargingAttack();

	//벡터에 탄 push
	projectiles.emplace_back(proj);


	SOUND->Stop("kill_chargeAttack");
	SOUND->Play("kill_chargeAttack");
}

void Player_kill::Skill()
{

	// 스킬 재사용 대기시간이 남았으면 스킬 사용 불가
	if (skillRemainingCooldown > 0.0f) return;

	// 양초가 있고, 낮은 상명력 상태
	if (isLowLife && hasCandle)
	{
		// 마나 소모없음
	}
	// 양초가 없으면 잔여 마나 체크
	else
	{
		// 마나가 없으면 스킬 사용 불가
		if (mp < skillManaCost)
		{
			return;
		}

		// 있으면 마나 감소
		mp -= skillManaCost;
	}

	skillRemainingCooldown = skillCooldown * skillCooldownScale;
	isSkill1 = true;
	isSkill2 = true;
	isSkill3 = true;
	Player::Skill();
}

void Player_kill::SkillAttack()
{
	// 발사 위치 계산
	Vector2 spawnPos = collider->GetWorldPos() + (lastDir * collider->scale.x * 0.5);

	// Scale 계산
	float skillScale = skill->frame.x / 11.0f;

	// 공격력 계산
	float totalDamage = damage * (damageScale + skillDamageScale) * 3.0f * skillScale;
	if (isFullLife) totalDamage *= fullLifeDamageScale;
	else if (isLowLife) totalDamage *= lowLifeDamageScale;

	// 탄생성
	kill_barehand_skill* proj = new kill_barehand_skill
	(
		skillScale,										// 스킬 크기
		spawnPos,										// 생성위치
		lastDir,										// 각도
		1.5f,											// 발사체 속도
		1,												// 사거리
		totalDamage,									// 공격력
		99,												// 관통력
		1,												// 폭발범위
		criticalChance									// 치명타 확률
	);

	// chargingTime = 0.0f;
	Player::ChargingAttack();

	//벡터에 탄 push
	projectiles.emplace_back(proj);

	// 사운드 재생
	SOUND->Stop("kill_skill");
	SOUND->Play("kill_skill");
}
