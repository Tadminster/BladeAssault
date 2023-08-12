#pragma once
class npcProto
{
protected:
	ObRect*		collider;
	ObImage*	skin;

public:
	npcProto() = default;
	explicit npcProto(Vector2 spawnPos);
	~npcProto();
	virtual void Update();
	virtual void Render();
};

