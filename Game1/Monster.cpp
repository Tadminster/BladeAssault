#include "stdafx.h"
#include "Creature.h"
#include "Player.h"
#include "DamageDisplayManager.h"
#include "EffectManager.h"
#include "Monster.h"

Monster::Monster()
{
	ui_frame_hp = new ObImage(L"ui_frame_mosterHp.png");
	ui_gauge_hp = new ObImage(L"ui_gauge_monsterHp.png");

	spawn = new ObImage(L"monster_spawn.png");

	ui_frame_hp->pivot = OFFSET_L;
	ui_frame_hp->SetParentRT(*collider);
	ui_frame_hp->scale.x = ui_frame_hp->imageSize.x * 0.2f;
	ui_frame_hp->scale.y = ui_frame_hp->imageSize.y * 0.3f;

	ui_gauge_hp->pivot = OFFSET_L;
	ui_gauge_hp->SetParentRT(*collider);
	ui_gauge_hp->scale.x = ui_gauge_hp->imageSize.x * 0.2f;
	ui_gauge_hp->scale.y = ui_gauge_hp->imageSize.y * 0.3f;

	spawn->pivot = OFFSET_B;
	spawn->SetParentRT(*collider);
	spawn->maxFrame.x = 14;
	spawn->maxFrame.y = 1;
	spawn->scale.x = spawn->imageSize.x / spawn->maxFrame.x * 1.2f;
	spawn->scale.y = spawn->imageSize.y / spawn->maxFrame.y * 1.2f;
	spawn->ChangeAnim(ANIMSTATE::ONCE, 0.1f);

	onFloor = false;
	isLanding = true;
}

Monster::~Monster()
{
	delete ui_frame_hp;
	delete ui_gauge_hp;
}


void Monster::Update()
{

	lastPos = collider->GetWorldPos();


	// ��� ó��
	if (hp == 0 && CurrentState != State::DIE)
	{
		// ���� ���
		SOUND->Stop("rat_die");
		SOUND->Play("rat_die");

		// ���º���
		CurrentState = State::DIE;
	}

	Vector2 target = GM->player->GetCollider()->GetWorldPos();
	// ���� ���
	if (target.x - collider->GetWorldPos().x > 0)
		dir = RIGHT;
	else
		dir = LEFT;

	// ��Ų ���� ����
	if (dir == LEFT)
	{
		idle->reverseLR = true;
		run->reverseLR = true;
		jump->reverseLR = true;
		attack->reverseLR = true;
	}
	else if (dir == RIGHT)
	{
		idle->reverseLR = false;
		run->reverseLR = false;
		jump->reverseLR = false;
		attack->reverseLR = false;
	}

	// ���� ���¿� ���� �۵�
	if (dmgTaken == MonsterDamageTaken::NORMAL)
	{
		// �÷� ����ȭ
		if (idle->color.x != 0.5)
		{
			idle->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			run->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			jump->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
			attack->color = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
		}
	}
	else if (dmgTaken == MonsterDamageTaken::DAMAGED)
	{
		// �̴Ͼ��̳� ����Ʈ �ϰ�� �˹�
		//if (type == MONSTER_TYPE::MINION || type == MONSTER_TYPE::ELITE)
		knockBack();

		// 0.05�� �Ŀ� �븻 ���·�
		if (timeOfDamage + 0.05f < TIMER->GetWorldTime())
		{
			knockBackFactor = 0;
			dmgTaken = MonsterDamageTaken::NORMAL;
		}
	}

	float distance = Vector2::Distance(collider->GetWorldPos(), GM->player->GetCollider()->GetWorldPos());
	int distanceX = GM->player->GetCollider()->GetWorldPos().x - collider->GetWorldPos().x;
	int distanceY = GM->player->GetCollider()->GetWorldPos().y - collider->GetWorldPos().y;
	int distanceX_abs = abs(distanceX);
	int distanceY_abs = abs(distanceY);

	if (CurrentState == State::IDLE)
	{
		// ���Ͱ� ���� ������ �Ÿ� �ȿ� �ִٸ�
		if (distanceX_abs < maxAttackDistance)
		{
			// ���Ϳ� �÷��̾��� ���� ��
			if (distanceY_abs < 200)
			{
				// �÷��̾�� ����� ���̿� �ִٸ� ���ݽõ�
				if (isAttackCooldown())
				{
					// IDLE -> ATTACK
					CurrentState = State::ATTACK;
				}
			}
			else
			{
				// �÷��̾ �� ���� �ִٸ� ����
				if (distanceY > 0)
				{
					Jump();
				}
				// �÷��̾ �� ���� �ִٸ� �ϰ�
				else if (distanceY < 0 && onFloor)
				{
					gravity = 0;
					CurrentState = State::CROUCH_DOWN;
				}
			}
		}
		// IDLE -> RUN
		else if (distanceX_abs < app.GetHalfWidth())
		{
			CurrentState = State::RUN;
		}
	}
	else if (CurrentState == State::RUN)
	{
		// �÷��̾ ���� ������ �����ȿ� ������ ��
		if (distanceX_abs < maxAttackDistance)
		{
			// ���� �����ϴٸ�
			if (isAttackCooldown())
			{
				// RUN -> ATTACK
				CurrentState = State::ATTACK;
			}
			// ���� �Ұ����ϴٸ�
			else
			{
				// RUN -> IDLE
				CurrentState = State::IDLE;
			}
		}

		collider->MoveWorldPos(dir * moveSpeed * DELTA);
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
				CurrentState = State::IDLE;
			}
		}
	}
	else if (CurrentState == State::ATTACK)
	{
		// ���� �����ӿ� �����ϸ� ���� ������ �̷����
		if (attack->frame.x == attackFrame && realAttack)
		{
			realAttack = false;
			Attack();
		}

		// ATTACK -> IDLE
		if (attack->frame.x == attack->maxFrame.x - 1)
		{
			CurrentState = State::IDLE;
		}
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
	else if (CurrentState == State::SPAWN)
	{
		spawn->color.w -= 0.2f * DELTA;
		
		if (spawn->frame.x > 5)
			idle->color.w = min(0.5f, idle->color.w + 0.5f * DELTA);

		// SPAWN ���
		if (spawn->frame.x == spawn->maxFrame.x - 1)
		{
			idle->color.w = 0.5f;
			CurrentState = State::IDLE;
		}
	}
	else if (CurrentState == State::DIE)
	{

	}

	// �߷� (�ٴڰ� ������ �ְų� �������� �ƴ� ��)
	if (!onWall && !onFloor && CurrentState != State::SPAWN)
	{
		gravity += 1500.0f * DELTA;
		collider->MoveWorldPos(DOWN * gravity * DELTA);
	}

	// ������Ʈ
	shadow->Update();
	switch (CurrentState)
	{
	case State::IDLE:
		idle->Update();
		break;
	case State::RUN:
		run->Update();
		break;
	case State::JUMP:
		jump->Update();
		break;
	case State::CROUCH_DOWN:
		jump->Update();
		break;
	case State::ATTACK:
		attack->Update();
		break;
	case State::SPAWN:
		if (spawn->frame.x > 5)
			idle->Update();
		spawn->Update();
		break;
	}
	collider->Update();

	if (hp != maxHp)
	{
		ui_gauge_hp->scale.x = ui_gauge_hp->imageSize.x * 0.2f * ((float)hp / (float)maxHp);
		ui_gauge_hp->Update();
		ui_frame_hp->Update();
	}
}

void Monster::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	if (hp != maxHp)
	{
		ui_frame_hp->Render();
		ui_gauge_hp->Render();
	}

	if (onWall || onFloor)
		shadow->Update();
	
		switch (CurrentState)
	{
	case State::IDLE:
		idle->Render();
		break;
	case State::RUN:
		run->Render();
		break;
	case State::JUMP:
		jump->Render();
		break;
	case State::CROUCH_DOWN:
		jump->Render();
		break;
	case State::ATTACK:
		attack->Render();
		break;
	case State::SPAWN:
		if (spawn->frame.x > 5)
			idle->Render();
		spawn->Render();
		break;
	}


}

bool Monster::isAttackCooldown()
{
	float currentTime = TIMER->GetWorldTime();			// ����ð�
	float elapsedTime = currentTime - lastAttackTime;	// ����ð�

	if (elapsedTime >= timeTakenToAttackOnce)
	{
		attack->frame.x = 0;
		realAttack = true;

		// ���Ӱ��
		lastAttackTime = currentTime;
		timeTakenToAttackOnce = 1.0f / attackSpeed;

		return true;
	}

	return false;
}

void Monster::Attack()
{


}

bool Monster::isDead() const
{
	if (CurrentState == State::DIE)
	{
		ObImage* dieEffect = new ObImage(L"monster_die.png");
		dieEffect->pivot = OFFSET_B;
		dieEffect->SetWorldPos(collider->GetWorldPos());
		dieEffect->maxFrame.x = 13;
		dieEffect->maxFrame.y = 1;
		dieEffect->scale.x = dieEffect->imageSize.x / dieEffect->maxFrame.x * 0.8f;
		dieEffect->scale.y = dieEffect->imageSize.y / dieEffect->maxFrame.y * 0.8f;
		dieEffect->color.w = 0.4f;
		dieEffect->ChangeAnim(ANIMSTATE::ONCE, 0.1f);

		GM->fx->AddEffects(dieEffect);

		return true;
	}
	else return false;
}

void Monster::actionsWhenDamaged(int damage, int knockBackFactor, int criticalChance)
{
	// ���¸� ������ �������� ����
	dmgTaken = MonsterDamageTaken::DAMAGED;
	// ������ ���� �ð� ���
	timeOfDamage = TIMER->GetWorldTime();
	// ��Ų �÷� ����
	{
		idle->color = Vector4(1, 1, 1, 0.5);
		run->color = Vector4(1, 1, 1, 0.5);
		jump->color = Vector4(1, 1, 1, 0.5);
		attack->color = Vector4(1, 1, 1, 0.5);
	}

	// ������ �ؽ�Ʈ�� ��µ� ��ġ ���
	Vector2 tempPos = collider->GetWorldPos() + Vector2(0, collider->scale.y * 0.75f);
	
	// ũ��Ƽ�� ���
	if (RANDOM->Int(1, 100) <= criticalChance)
	{
		damage *= 2;

		// ������ �ؽ�Ʈ ���
		GM->damageDP->AddText(tempPos, damage, 6);
	}
	else
	{
		GM->damageDP->AddText(tempPos, damage);
	}


	// �˹� ���
	this->knockBackFactor = knockBackFactor;

	// ü�� ����
	this->hp = max(0, hp - damage);
}

void Monster::knockBack()
{
	// �˹� ���� ���
	Vector2 knockBackDir;
	if (GM->player->GetCollider()->GetWorldPos().x < this->collider->GetWorldPos().x)
		knockBackDir = RIGHT;
	else
		knockBackDir = LEFT;

	this->collider->MoveWorldPos(knockBackDir * knockBackFactor * DELTA);
}