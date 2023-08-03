#include "stdafx.h"
#include "Item.h"
#include "leatherBelt.h"
#include "championBelt.h"
#include "reinforcedChampionBelt.h"
#include "Chest.h"
#include "ItemManager.h"
#include "commonChest.h"

commonChest::commonChest()
{
    locked = new ObImage(L"chest_common_locked.png");
    unlocking = new ObImage(L"chest_common_unlocking.png");
    unlocked = new ObImage(L"chest_common_unlocked.png");


    locked->pivot = OFFSET_B;
    locked->SetParentRT(*collider);
    locked->maxFrame.x = 1;
    locked->maxFrame.y = 1;
    locked->scale.x = locked->imageSize.x / locked->maxFrame.x * 2.0f;
    locked->scale.y = locked->imageSize.y / locked->maxFrame.y * 2.0f;

    unlocking->pivot = OFFSET_B;
    unlocking->SetParentRT(*collider);
    unlocking->maxFrame.x = 9;
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

    gradeRate[ItemGrade::NORMAL] = 70;
    gradeRate[ItemGrade::RARE] = 20;
    gradeRate[ItemGrade::EPIC] = 10;
    gradeRate[ItemGrade::LEGENDARY] = 0;
}