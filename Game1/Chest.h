#pragma once
enum class ChestState
{
	LOCKED,
	UNlOCKING,
	UNLOCKED
};

class Chest
{
protected:
	class ObRect* collider;
	class ObImage* locked;
	class ObImage* unlocking;
	class ObImage* unlocked;
	class ObImage* presskey;

	ChestState state;
	bool isOpen;
	bool isSpawn;

public:
	Chest();
	virtual ~Chest();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void CreateItem();

	// Get
	ObRect* GetCollider() { return collider; };
	ChestState GetState() { return state; }
	bool GetIsOpen() { return isOpen; }
	//bool GetIsSpawn() { return isSpawn; }

	// Set
	void SetPosition(Vector2 pos) { collider->SetWorldPos(pos); }
};

