#include "stdafx.h"
#include "npcProto.h"
#include "npcDarcy.h"

npcDarcy::npcDarcy(Vector2 spawnPos) : npcProto(spawnPos)
{
	skin = new ObImage(L"npc_darcy.png");

	collider->scale.x = 100;
	collider->scale.y = 200;

	skin->pivot = OFFSET_B;
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 6;
	skin->maxFrame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 2.6f;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 2.6f;
	//skin->SetLocalPosY(-collider->scale.y * 0.1f);
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}