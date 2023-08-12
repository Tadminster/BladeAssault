#include "stdafx.h"
#include "npc_proto.h"
#include "hank.h"

hank::hank(Vector2 spawnPos) : npc_proto(spawnPos)
{
	skin = new ObImage(L"npc_hank.png");

	collider->scale.x = 100;
	collider->scale.y = 100;

	skin->pivot = OFFSET_B;
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 12;
	skin->maxFrame.y = 2;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 2.4f;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 2.4f;
	skin->SetLocalPosY(collider->scale.y * 0.75f);
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}