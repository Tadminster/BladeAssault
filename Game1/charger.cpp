#include "stdafx.h"
#include "Item.h"
#include "charger.h"

charger::charger() : Item()
{
	grade = ItemGrade::RARE;

	icon = new ObImage(L"gear_icon_charger.png");
	icon->pivot = OFFSET_B;
	icon->SetParentRT(*collider);
	icon->scale.x = icon->imageSize.x * 2.0f;
	icon->scale.y = icon->imageSize.y * 2.0f;
	icon->SetLocalPosY(collider->scale.y * 0.75f);

	// grade에 따라 아이템의 이름과 배경 색이 바뀜
	if (grade == ItemGrade::NORMAL)
	{
		options = new ObImage(L"grade_outline_normal_330_430.png");
		itemNameColor = Color(0.6f, 0.6f, 0.6f, 0.5f);
	}
	else if (grade == ItemGrade::RARE)
	{
		options = new ObImage(L"grade_outline_rare_330_430.png");
		itemNameColor = Color(0.0f, 1.0f, 1.0f, 0.5f);
	}
	else if (grade == ItemGrade::EPIC)
	{
		options = new ObImage(L"grade_outline_epic_330_430.png");
		itemNameColor = Color(1.0f, 0.0f, 1.0f, 0.5f);
	}
	else if (grade == ItemGrade::LEGENDARY)
	{
		options = new ObImage(L"grade_outline_legendary_330_430.png");
		itemNameColor = Color(1.0f, 0.8f, 0.0f, 0.5f);
	}

	options->pivot = OFFSET_B;
	options->SetParentRT(*collider);
	options->scale.x = options->imageSize.x;
	options->scale.y = options->imageSize.y;
	options->SetLocalPosY(collider->scale.y * 0.8f);

	text_name = L"충전기";
	text_explanation = L"차징 효율과 차징 공격력이 15% 증가합니다.";

	// 아이템의 능력치
	chargingTimeScale = 0.15f;
	chargingDamageScale = 0.15f;
}
