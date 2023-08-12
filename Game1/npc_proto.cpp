#include "stdafx.h"
#include "npc_proto.h"

npc_proto::npc_proto(Vector2 spawnPos)
{
	collider = new ObRect();
	collider->pivot = OFFSET_B;
	collider->isFilled = false;
	collider->SetLocalPos(spawnPos);
}

npc_proto::~npc_proto()
{
	delete collider;
	delete skin;
}

void npc_proto::Update()
{
	collider->Update();
	skin->Update();
}

void npc_proto::Render()
{
	if (GM->DEBUG_MODE)
		collider->Render();

	skin->Render();
}
