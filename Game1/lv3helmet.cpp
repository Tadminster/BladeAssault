#include "stdafx.h"
#include "Item.h"
#include "lv3helmet.h"

lv3helmet::lv3helmet() : Item()
{
	grade = ItemGrade::LEGENDARY;

	icon = new ObImage(L"gear_icon_lv3helmet.png");
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

	text_name = L"3뚝";
	text_explanation = L"방어력이 3 증가하고, 추가로 적의 공격으로 입는 피해를 10% 감소합니다.";

	// 아이템의 능력치
	defence = 3;
	damageRedution = 0.1f;
}
