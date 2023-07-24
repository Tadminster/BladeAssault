#include "stdafx.h"
#include "Creature.h"

Creature::Creature()
{
	collider = new ObRect();
}

Creature::~Creature()
{
	delete collider;
	delete idle;
	delete run;
	delete jump;
	delete attack;
	delete shadow;
}

void Creature::Init()
{
}

void Creature::Update()
{
}

void Creature::Render()
{
}

void Creature::Jump()
{
	collider->SetWorldPosY(collider->GetWorldPos().y + 5);
	gravity = -jumpSpeed;
	CurrentState = State::JUMP;
}

void Creature::Attack()
{
}

void Creature::OnFloorAction()
{
	onFloor = true;
	gravity = 0;
}

void Creature::OnWallAction()
{
	onWall = true;
	gravity = 0;
}

void Creature::OnWallSlideAction()
{
	collider->SetWorldPosX(lastPos.x);
	collider->Update();
}

Vector2 Creature::GetFoot()
{
	//29 38
	//Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
	//Utility::IntersectRectRect()

//                              중앙에서나갈위치    발중앙위치 보정
	return collider->GetWorldPos() + (dir + DOWN) * Vector2(collider->scale.x * 0.5f, 0);
}

Vector2 Creature::GetHead()
{
	//29 38
	//Utility::RECT r(GetWorldPos()+ Vector2(0, 10), Vector2(15, 10));
	//Utility::IntersectRectRect()

//                              중앙에서나갈위치    발중앙위치 보정
	return collider->GetWorldPos() + (dir + UP) * Vector2(collider->scale.x * 0.5f, collider->scale.y);
}

void Creature::GoBack()
{
	gravity = 0;
	collider->SetWorldPos(lastPos);
	collider->Update();
}
