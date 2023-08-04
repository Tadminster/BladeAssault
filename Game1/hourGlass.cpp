#include "stdafx.h"
#include "Item.h"
#include "hourGlass.h"

hourGlass::hourGlass() : Item()
{
	grade = ItemGrade::LEGENDARY;

	icon = new ObImage(L"gear_icon_hourGlass.png");
	icon->pivot = OFFSET_B;
	icon->SetParentRT(*collider);
	icon->scale.x = icon->imageSize.x * 2.0f;
	icon->scale.y = icon->imageSize.y * 2.0f;
	icon->SetLocalPosY(collider->scale.y * 0.75f);

	// grade�� ���� �������� �̸��� ��� ���� �ٲ�
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

	text_name = L"�𷡽ð�";
	text_explanation = L"��� ���� ���ð��� 20% �����մϴ�.";

	// �������� �ɷ�ġ
	dashCooldownScale = 0.2f;
	skillCooldownScale = 0.2f;
}
