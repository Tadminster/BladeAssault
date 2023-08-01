#pragma once

enum class ItemGrade
{
	NORMAL,
	RARE,
	LEGENDARY,
	EPIC
};

class Item
{
protected:
	class ObRect* Item;
	class ObImage* locked;
	class ObImage* unlocking;
	class ObImage* unlocked;
	class ObImage* presskey;

	ItemGrade grade;
	bool isOpen;
	bool isSpawn;

public:
	Item();
	~Item();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Open();
	virtual void Spawn();

	// Get
	ObRect* GetCollider() { return collider; };
	ItemGrade GetState() { return grade; }
};

