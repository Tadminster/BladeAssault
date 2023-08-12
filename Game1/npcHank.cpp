#include "stdafx.h"
#include "npcProto.h"
#include "npcHank.h"

npcHank::npcHank(Vector2 spawnPos) : npcProto(spawnPos)
{
	skin = new ObImage(L"npc_hank.png");

	collider->scale.x = 100;
	collider->scale.y = 150;

	skin->pivot = OFFSET_B;
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 12;
	skin->maxFrame.y = 2;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x * 2.4f;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y * 2.4f;
	//skin->SetLocalPosY(collider->scale.y * 0.75f);
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}

void npcHank::Update()
{
	motionChangeTime += DELTA;

	if (motionChangeTime > 4.0f)
	{
		motionChangeTime = 0.0f;
		skin->frame.y = RANDOM->Int(0, 1);
	}

	npcProto::Update();
}
