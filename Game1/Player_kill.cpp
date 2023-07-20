#include "stdafx.h"
#include "Player.h"
#include "Player_Kill.h"
#include "Projectile.h"
#include "kill_barehand_atk.h"


Player_kill::Player_kill()
{
	idle = new ObImage(L"kill_barehand_idle.png");
	run = new ObImage(L"kill_barehand_run.png");
	dash = new ObImage(L"kill_barehand_dash.png");
	jump = new ObImage(L"kill_barehand_jump.png");
	crouch = new ObImage(L"kill_barehand_crouch.png");
	attack = new ObImage(L"kill_barehand_sub_attack.png");
	//hasAxis = true;
}

Player_kill::~Player_kill()
{
	Player::~Player();
}

void Player_kill::Init()
{
	collider->isFilled = false;
	collider->scale.x = 60;
	collider->scale.y = 100;

	idle->SetParentRT(*collider);
	idle->SetLocalPosY(20);
	idle->maxFrame.x = 6;
	idle->maxFrame.y = 1;
	idle->scale.x = idle->imageSize.x / idle->maxFrame.x * 3;
	idle->scale.y = idle->imageSize.y / idle->maxFrame.y * 3;
	idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	run->SetParentRT(*collider);
	run->SetLocalPosY(20);
	run->maxFrame.x = 8;
	run->maxFrame.y = 1;
	run->scale.x = run->imageSize.x / run->maxFrame.x * 3;
	run->scale.y = run->imageSize.y / run->maxFrame.y * 3;
	run->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	dash->SetParentRT(*collider);
	dash->SetLocalPosY(20);
	dash->maxFrame.x = 5;
	dash->maxFrame.y = 1;
	dash->scale.x = dash->imageSize.x / dash->maxFrame.x * 3;
	dash->scale.y = dash->imageSize.y / dash->maxFrame.y * 3;
	dash->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

	jump->SetParentRT(*collider);
	jump->SetLocalPosY(20);
	jump->maxFrame.x = 2;
	jump->maxFrame.y = 2;
	jump->scale.x = jump->imageSize.x / jump->maxFrame.x * 3;
	jump->scale.y = jump->imageSize.y / jump->maxFrame.y * 3;
	jump->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	crouch->SetParentRT(*collider);
	crouch->SetLocalPosY(20);
	crouch->maxFrame.x = 6;
	crouch->maxFrame.y = 1;
	crouch->scale.x = crouch->imageSize.x / crouch->maxFrame.x * 3;
	crouch->scale.y = crouch->imageSize.y / crouch->maxFrame.y * 3;
	crouch->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

	attack->SetParentRT(*collider);
	attack->SetLocalPosY(20);
	attack->maxFrame.x = 4;
	attack->maxFrame.y = 1;
	attack->scale.x = attack->imageSize.x / attack->maxFrame.x * 3;
	attack->scale.y = attack->imageSize.y / attack->maxFrame.y * 3;
	attack->ChangeAnim(ANIMSTATE::ONCE, 0.085f, true);

	// �ɷ�ġ
	Player::Init();

	AttackSpeed = 1.0f;
}


void Player_kill::Update()
{
	Player::Update();
}

void Player_kill::Render()
{
	Player::Render();
}

void Player_kill::Attack()
{

	static float lastShotTime = 0;
	static float timeSinceLastTime = 0;
	cout << "lastShotTime: " << lastShotTime << endl;
	cout << "timeSinceLastTime: " << timeSinceLastTime << endl;

	float currentTime = TIMER->GetWorldTime();
	float elapsedTime = currentTime - lastShotTime;

	if (elapsedTime >= timeSinceLastTime)
	{
		Player::Attack();

		// ź����
		kill_barehand_atk* proj = new kill_barehand_atk
		(
			collider->GetWorldPos(),						// ������ġ
			lastDir,										// ����
			500,											// �߻�ü �ӵ�
			500,											// ��Ÿ�
			10,												// ���ݷ�
			1,												// �����
			1												// ���߹���
		);

		//���Ϳ� ź push
		projectiles.emplace_back(proj);

		// ���Ӱ��
		lastShotTime = currentTime;
		timeSinceLastTime = 1.0f / AttackSpeed;
	}
}
