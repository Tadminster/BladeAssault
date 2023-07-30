#include "stdafx.h"
#include "EffectManager.h"

void EffectManager::Init()
{
}

void EffectManager::Release()
{
}

void EffectManager::Update()
{
	// 프레임이 끝난 이펙트들을 삭제
	effects.erase(
		std::remove_if
		(
			effects.begin(),
			effects.end(),
			[](ObImage* effect) 
				{ 
					if (effect->frame.x == effect->maxFrame.x)
					{
						delete effect;
						return true; 
					}
					else return false;
				}
		),
		effects.end()
	);

	for (auto& effect : effects)
		effect->Update();
}

void EffectManager::LateUpdate()
{
}

void EffectManager::Render()
{
	for (auto& effect : effects)
		effect->Render();
}

void EffectManager::AddEffects(ObImage* image)
{
	this->effects.emplace_back(image);
}
