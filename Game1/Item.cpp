#include "stdafx.h"
#include "Creature.h"
#include "Player.h"
#include "ItemManager.h"
#include "Item.h"

Item::Item(Vector2 dropPos)
{
	collider = new ObRect();
	collider->pivot = OFFSET_B;
	collider->scale = Vector2(100, 150);
	collider->SetWorldPos(dropPos);
	collider->isFilled = false;

	presskey = new ObImage(L"chest_Selection.png");
	presskey->pivot = OFFSET_B;
	presskey->SetParentRT(*GM->player->GetCollider());
	presskey->SetLocalPosY(-collider->scale.y * 0.35f);
	presskey->scale.x = presskey->imageSize.x;
	presskey->scale.y = presskey->imageSize.y;

	collider->Update();



	// 아이템이름 rect
	Vector2 itemName_pos = Vector2(collider->GetWorldPos().x, collider->GetWorldPos().y + collider->scale.y * 3.0f);
	rect_itemName.left = Utility::WorldToScreen(itemName_pos).x;
	rect_itemName.left = Utility::WorldToScreen(itemName_pos).y;
	rect_itemName.top = itemName_pos.y;
	rect_itemName.right = rect_itemName.left + 1000;
	rect_itemName.bottom = rect_itemName.top + 1000;

	// 아이템설명 rect
	Vector2 itemExplanation_pos = Vector2(collider->GetWorldPos().x - collider->scale.x, collider->GetWorldPos().y + collider->scale.y * 2.5f);
	rect_itemExplanation.left = Utility::WorldToScreen(itemExplanation_pos).x;
	rect_itemExplanation.top = Utility::WorldToScreen(itemExplanation_pos).y;
	rect_itemExplanation.right = rect_itemExplanation.left + 1000;
	rect_itemExplanation.bottom = rect_itemExplanation.top + 1000;

	maxHp = 0;
	maxMp = 0;
	hp = 0;
	mp = 0;
	damage = 0;
	damageScale = 0.0f;
	criticalChance = 0;
	defence = 0;
	attackSpeed = 0.0f;
	moveSpeed = 0.0f;

	cout << "발동1";
}

Item::~Item()
{
	delete collider;
	delete icon;
	delete options;

	TEXTURE->DeleteTexture(L"chest_PressE.png");
}

void Item::Init()
{
}

void Item::Update()
{
	collider->Update();
	icon->Update();

	// 아이템이름 rect
	Vector2 itemName_pos = Vector2(collider->GetWorldPos().x - collider->scale.x, collider->GetWorldPos().y + collider->scale.y * 3.0f);
	rect_itemName.left = Utility::WorldToScreen(itemName_pos).x;
	rect_itemName.top = Utility::WorldToScreen(itemName_pos).y;
	rect_itemName.right = rect_itemName.left + 1000;
	rect_itemName.bottom = rect_itemName.top + 1000;

	// 아이템설명 rect
	Vector2 itemExplanation_pos = Vector2(collider->GetWorldPos().x - collider->scale.x, collider->GetWorldPos().y + collider->scale.y * 2.5f);
	rect_itemExplanation.left = Utility::WorldToScreen(itemExplanation_pos).x;
	rect_itemExplanation.top = Utility::WorldToScreen(itemExplanation_pos).y;
	rect_itemExplanation.right = rect_itemExplanation.left + options->imageSize.x * 0.6f;
	rect_itemExplanation.bottom = rect_itemExplanation.top + 1000;
	
	// collider에 player가 닿으면
	if (collider->Intersect(GM->player->GetCollider()))
	{
		// icon의 color를 원래색으로
		if (icon->color.x != 0.5f)
		{
			icon->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
		}

		if (INPUT->KeyDown('F'))
		{
			// 아이템의 능력치를 적용
			GM->player->activateItem(this);

			// 모든 아이템을 활성화(파괴하기 위해)시킴
			GM->item->ActivateAllItem();
			return;
		}

		// options를 update
		options->Update();
		presskey->Update();
	}
	// 닿지 않았으면
	else
	{
		// icon의 color를 어두운색으로
		if (icon->color.x == 0.5f)
		{
			icon->color = Color(0.3f, 0.3f, 0.3f, 0.5f);
		}
	}


}

void Item::Render()
{
	// 디버그 모드일 때 collider를 render
	if (GM->DEBUG_MODE)
		collider->Render();
	
	// collider에 player가 닿으면 options를 render
	if (collider->Intersect(GM->player->GetCollider()))
	{
		options->Render();
		presskey->Render();



		// name
		DWRITE->RenderText(
			text_name,
			rect_itemName,
			25.0f,
			L"Commando",
			itemNameColor,
			DWRITE_FONT_WEIGHT_EXTRA_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

		// name
		DWRITE->RenderText(
			text_explanation,
			rect_itemExplanation,
			20.0f,
			L"Commando",
			Color(1, 1, 1, 1),
			DWRITE_FONT_WEIGHT_EXTRA_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
	}
	icon->Render();
}
