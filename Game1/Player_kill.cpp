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

	skill->pivot = OFFSET_B;
	skill->SetParentRT(*collider);
	skill->maxFrame.x = 31;
	skill->maxFrame.y = 1;
	skill->scale.x = skill->imageSize.x / skill->maxFrame.x * 3.2;
	skill->scale.y = skill->imageSize.y / skill->maxFrame.y * 3.2;
	skill->SetLocalPosY(-collider->scale.y * 0.5f);
	skill->ChangeAnim(ANIMSTATE::ONCE, 0.065f, true);

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

	chargingTime = 0.0f;			// ��¡
	chargingTimeMax = 3.0f;			// ��¡ �ִ� �ð�
	chargingStartFrame = 1;		
	chargingEndFrame = 4;

	skillCooldown = 4.0f;			// ��ų ��Ÿ��
	skillRemainingCooldown = 0.0f;	// ��ų ���� ��Ÿ��
	skillManaCost = 30;				// ��ų ���� �Ҹ�

	hp = 150;
	maxHp = 150;
	mp = 120;
	maxMp = 120;

	damage = 10;					// ĳ������ ���� ���ݷ�
	defence = 0;					// ĳ������ ���� ����
	attackRange = 500;				// �⺻ ���� ��Ÿ�
	attackSpeed = 3.0f;				// �⺻ ���� �ӵ�
	jumpSpeed = 900.0f;

	isSkill1 = false;
	isSkill2 = false;
	isSkill3 = false;
}


void Player_kill::Update()
{

	// ��Ų ���� ����
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
		// ī�޶� ��鸲 ȿ��
		if (skill->frame.x > 5 && skill->frame.x < 24)
		{
			CAM->position.x += (RANDOM->Int(0, 1) ? 2 : -2);
			CAM->position.y += (RANDOM->Int(0, 1) ? 2 : -2);
		}

		// ù��° ����
		if (skill->frame.x == 6 && isSkill1)
		{
			isSkill1 = false;
			SkillAttack();
		}
		// �ι�° ����
		else if (skill->frame.x == 11 && isSkill2)
		{
			isSkill2 = false;
			SkillAttack();
		}
		// ����° ����
		else if (skill->frame.x == 16 && isSkill3)
		{
			isSkill3 = false;
			SkillAttack();
		}

		// ������ �����ӿ� �����ϸ� skill -> idle
		if (skill->frame.x == skill->maxFrame.x - 1)
		{
			CurrentState = State::IDLE;
		}
	}

	if (CurrentState == State::CHARGING)
		chargingFx->Update();

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

		// �߻� ��ġ ���
		Vector2 spawnPos = collider->GetWorldPos() + lastDir * collider->scale.x + (UP * collider->scale.y * 0.65);

		// ź����
		kill_barehand_atk* proj = new kill_barehand_atk
		(
			spawnPos,										// ������ġ
			lastDir,										// ����
			700,											// �߻�ü �ӵ�
			attackRange,									// ��Ÿ�
			damage,											// ���ݷ�
			1,												// �����
			1												// ���߹���
		);

		//���Ϳ� ź push
		projectiles.emplace_back(proj);

		// ���Ӱ��
		lastShotTime = currentTime;
		timeSinceLastTime = 1.0f / attackSpeed;
	}
}

void Player_kill::ChargingAttack()
{
	// �߻� ��ġ ���
	Vector2 spawnPos = collider->GetWorldPos() + lastDir * collider->scale.x + (UP * collider->scale.y * 0.65);

	// ź����
	kill_barehand_ChargingAtk* proj = new kill_barehand_ChargingAtk
	(
		spawnPos,										// ������ġ
		lastDir,										// ����
		3,												// �߻�ü �ӵ�
		1,												// ��Ÿ�
		damage * (chargingTime + 1),					// ���ݷ�
		99,												// �����
		1												// ���߹���
	);

	// chargingTime = 0.0f;
	Player::ChargingAttack();

	//���Ϳ� ź push
	projectiles.emplace_back(proj);
}

void Player_kill::Skill()
{
	// ������ ���ų� ��ų ���� ���ð��� �������� ��ų ��� �Ұ�
	if (mp < skillManaCost || skillRemainingCooldown > 0.0f) return;

	mp -= skillManaCost;
	skillRemainingCooldown = skillCooldown;
	isSkill1 = true;
	isSkill2 = true;
	isSkill3 = true;
	Player::Skill();
}

void Player_kill::SkillAttack()
{
	// �߻� ��ġ ���
	Vector2 spawnPos = collider->GetWorldPos() + (lastDir * collider->scale.x * 0.5);
	cout << spawnPos.x << endl;
	cout << spawnPos.y << endl;
	// Scale ���
	float scale = skill->frame.x / 11.0f;

	// ź����
	kill_barehand_skill* proj = new kill_barehand_skill
	(
		scale,											// ��ų ũ��
		spawnPos,										// ������ġ
		lastDir,										// ����
		1.5f,											// �߻�ü �ӵ�
		1,												// ��Ÿ�
		damage * 3.5f,									// ���ݷ�
		99,												// �����
		1												// ���߹���
	);

	// chargingTime = 0.0f;
	Player::ChargingAttack();

	//���Ϳ� ź push
	projectiles.emplace_back(proj);
}
