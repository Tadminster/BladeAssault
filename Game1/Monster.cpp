#include "stdafx.h"
#include "Monster.h"

Monster::Monster()
{
	collider = new ObRect();
	idle = nullptr;
	run = nullptr;
	jump = nullptr;
	attack = nullptr;
}

Monster::~Monster()
{
	delete collider;
	delete idle;
	delete run;
	delete jump;
	delete attack;
}

void Monster::Init(Vector2 spawnPos)
{
}

void Monster::Update()
{
	switch (status)
	{
	case MonsterState::IDLE:
		idle->Update();
		break;
	case MonsterState::RUN:
		run->Update();
		break;
	case MonsterState::JUMP:
		jump->Update();
		break;
	case MonsterState::ATTACK:
		attack->Update();
		break;
	}
	collider->Update();
}

void Monster::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	switch (status)
	{
	case MonsterState::IDLE:
		idle->Render();
		break;
	case MonsterState::RUN:
		run->Render();
		break;
	case MonsterState::JUMP:
		jump->Render();
		break;
	case MonsterState::ATTACK:
		attack->Render();
		break;
	}
}
