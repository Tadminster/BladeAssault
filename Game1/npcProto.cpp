#include "stdafx.h"
#include "npcProto.h"

npcProto::npcProto(Vector2 spawnPos)
{
	collider = new ObRect();
	collider->pivot = OFFSET_B;
	collider->isFilled = false;
	collider->SetLocalPos(spawnPos);
}

npcProto::~npcProto()
{
	delete collider;
	delete skin;
}

void npcProto::Update()
{
	collider->Update();
	skin->Update();
}

void npcProto::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	skin->Render();
}
