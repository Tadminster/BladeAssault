#pragma once
class npcHank : public npcProto
{
private:

public:
	explicit npcHank(Vector2 spawnPos);
	void Update() override;

	// 모션을 바꿀 때 사용하는 시간
	float motionChangeTime{ 0 };
};

