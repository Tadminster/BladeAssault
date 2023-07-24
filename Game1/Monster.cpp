#include "stdafx.h"
#include "Creature.h"
#include "Player.h"
#include "Monster.h"

Monster::Monster()
{
	idle = nullptr;
	run = nullptr;
	jump = nullptr;
	attack = nullptr;

	onFloor = false;
	isLanding = true;
}

Monster::Monster(Vector2 spawnPos)
{
}

Monster::~Monster()
{
	Creature::~Creature();
}

//void Monster::Init(Vector2 spawnPos)
//{
//}

void Monster::Update()
{

	lastPos = collider->GetWorldPos();

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
			idle->color = Vector4(0.5, 0.5, 0.5, 0.5);
			run->color = Vector4(0.5, 0.5, 0.5, 0.5);
			jump->color = Vector4(0.5, 0.5, 0.5, 0.5);
			attack->color = Vector4(0.5, 0.5, 0.5, 0.5);
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
	ImGui::Text("MonsterState: %d\n", CurrentState);
	ImGui::Text("distanceX: %d\n", distanceX);
	ImGui::Text("distanceY: %d\n", distanceY);


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
				else if (distanceY < 0)
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
		// RUN -> ATTACK
		if (distanceX_abs < 100)
		{
			if (isAttackCooldown())
			{
				CurrentState = State::ATTACK;
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
		// ���� �����ӿ� �����ϸ� �߻�
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

	// �߷�
	if (!onWall && !onFloor)
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

	}
	collider->Update();
}

void Monster::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	shadow->Render();
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
	}
}

bool Monster::isAttackCooldown()
{

	
	static float lastShotTime = 0;
	static float timeSinceLastTime = 0;

	float currentTime = TIMER->GetWorldTime();
	float elapsedTime = currentTime - lastShotTime;

	if (elapsedTime >= timeSinceLastTime)
	{
		attack->frame.x = 0;
		realAttack = true;


		// ���Ӱ��
		lastShotTime = currentTime;
		timeSinceLastTime = 1.0f / attackSpeed;

		return true;
	}

	return false;
}

void Monster::Attack()
{


}

void Monster::actionsWhenDamaged(Vector4 value)
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
	// ü�� ����
	this->hp = max(hp + value.x, 0);
	// �˹� ���
	knockBackFactor = value.y;
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