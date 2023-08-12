#pragma once
class npc_proto
{
protected:
	ObRect*		collider;
	ObImage*	skin;

public:
	npc_proto() = default;
	explicit npc_proto(Vector2 spawnPos);
	~npc_proto();
	virtual void Update();
	virtual void Render();
};

