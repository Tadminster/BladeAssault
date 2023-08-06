#include "stdafx.h"
#include "DamageText.h"
#include "DamageDisplayManager.h"

void DamageDisplayManager::Init()
{
}

void DamageDisplayManager::Release()
{
}

void DamageDisplayManager::Update()
{
	// texts size 출력
	ImGui::Text("texts size: %d", texts.size());

	// 데미지 표시가 일정거리 이상 벗어났으면 삭제
	texts.erase(
		std::remove_if
		(
			texts.begin(),
			texts.end(),
			[](DamageText* text) { return text->hasTraveledTooFar(); }
		),
		texts.end()
	);

	for (auto& text : texts)
	{
		text->Update();
	}
}

void DamageDisplayManager::LateUpdate()
{
	for (auto& text : texts)
	{
		text->LateUpdate();
	}
}

void DamageDisplayManager::Render()
{
	for (auto& text : texts)
	{
		text->Render();
	}
}

void DamageDisplayManager::AddText(Vector2 spawnPos, int damage, int color)
{
	spawnPos += Vector2(RANDOM->Int(-50, 50), RANDOM->Int(-50, 50));
	std::string damageValue = std::to_string(damage);
	int length = damageValue.length();

	for (int i = 0; i < length; i++)
	{
		Vector2 spawnPosTemp = Vector2(spawnPos.x + i * 15, spawnPos.y);
		int value = std::stoi(damageValue.substr(i, i + 1));
		this->texts.emplace_back(new DamageText(spawnPosTemp, value, color));
	}
}
