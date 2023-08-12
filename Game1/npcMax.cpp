#include "stdafx.h"
#include "npcProto.h"
#include "npcMax.h"

npcMax::npcMax(Vector2 spawnPos) : npcProto(spawnPos)
{
	skin = new ObImage(L"npc_max.png");

	collider->scale.x = 100;
	collider->scale.y = 200;

	skin->pivot = OFFSET_B;
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 7;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 2.4f;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 2.4f;
	skin->SetLocalPosX(collider->scale.x * 0.25f);
	skin->SetLocalPosY(collider->scale.y * 0.55f);
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.15f);
}