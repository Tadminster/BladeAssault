#pragma once
class npcHank : public npcProto
{
private:

public:
	explicit npcHank(Vector2 spawnPos);
	void Update() override;

	// ����� �ٲ� �� ����ϴ� �ð�
	float motionChangeTime{ 0 };
};

