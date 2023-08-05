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

	ChestState state	= ChestState::LOCKED;
	bool isOpen			= false;
	bool isCleared		= false;

	// µî±Þ È®·ü (normal, rare, epic, lengendary)
	int gradeRate[4];

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
	bool GetIsCleared() { return isCleared; }

	// Set
	void SetPosition(Vector2 pos) { collider->SetWorldPos(pos); }
	void SetCleared() { isCleared = true; }
};