#include "stdafx.h"
#include "Item.h"
#include "dart.h"

dart::dart() : Item()
{
	grade = ItemGrade::NORMAL;

	icon = new ObImage(L"gear_icon_dart.png");
	icon->pivot = OFFSET_B;
	icon->SetParentRT(*collider);
	icon->scale.x = icon->imageSize.x * 2.0f;
	icon->scale.y = icon->imageSize.y * 2.0f;
	icon->SetLocalPosY(collider->scale.y * 0.75f);

	// grade�� ���� �������� �̸��� ��� ���� �ٲ�
	if (grade == ItemGrade::NORMAL)
	{
		options = new ObImage(L"grade_outline_normal_330_430.png");
		itemNameColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
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
		itemNameColor = Color(1.0f, 1.0f, 0.0f, 0.5f);
	}

	options->pivot = OFFSET_B;
	options->SetParentRT(*collider);
	options->scale.x = options->imageSize.x;
	options->scale.y = options->imageSize.y;
	options->SetLocalPosY(collider->scale.y * 0.8f);

	text_name = L"��Ʈ";
	text_explanation = L"��� ������ ġ��Ÿ ���ط��� 15% �����մϴ�.";

	// �������� �ɷ�ġ
	criticalDamage = 0.15f;
}
