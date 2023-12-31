#include "stdafx.h"
#include "Item.h"
#include "leatherBelt.h"
#include "championBelt.h"
#include "reinforcedChampionBelt.h"
#include "Chest.h"
#include "ItemManager.h"
#include "uncommonChest.h"

uncommonChest::uncommonChest()
{
    locked = new ObImage(L"chest_uncommon_locked.png");
    unlocking = new ObImage(L"chest_uncommon_unlocking.png");
    unlocked = new ObImage(L"chest_uncommon_unlocked.png");


    locked->pivot = OFFSET_B;
    locked->SetParentRT(*collider);
    locked->maxFrame.x = 7;
    locked->maxFrame.y = 1;
    locked->scale.x = locked->imageSize.x / locked->maxFrame.x * 2.0f;
    locked->scale.y = locked->imageSize.y / locked->maxFrame.y * 2.0f;
    locked->ChangeAnim(ANIMSTATE::LOOP, 0.1f, true);

    unlocking->pivot = OFFSET_B;
    unlocking->SetParentRT(*collider);
    unlocking->maxFrame.x = 10;
    unlocking->maxFrame.y = 1;
    unlocking->scale.x = unlocking->imageSize.x / unlocking->maxFrame.x * 2.0f;
    unlocking->scale.y = unlocking->imageSize.y / unlocking->maxFrame.y * 2.0f;
    unlocking->ChangeAnim(ANIMSTATE::ONCE, 0.1f, true);

    unlocked->pivot = OFFSET_B;
    unlocked->SetParentRT(*collider);
    unlocked->maxFrame.x = 1;
    unlocked->maxFrame.y = 1;
    unlocked->scale.x = unlocked->imageSize.x / unlocked->maxFrame.x * 2.0f;
    unlocked->scale.y = unlocked->imageSize.y / unlocked->maxFrame.y * 2.0f;

    gradeRate[ItemGrade::NORMAL] = 20;
    gradeRate[ItemGrade::RARE] = 60;
    gradeRate[ItemGrade::EPIC] = 15;
    gradeRate[ItemGrade::LEGENDARY] = 5;
}