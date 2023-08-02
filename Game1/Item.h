#pragma once

enum class ItemGrade
{
	NORMAL,
	RARE,
	EPIC,
	LEGENDARY
};

class Item
{
protected:
	class ObRect* collider;
	class ObImage* icon;
	class ObImage* options;
	class ObImage* presskey;

	Color itemNameColor;

	RECT rect_itemName;
	RECT rect_itemExplanation;
	wstring  text_name;
	wstring  text_explanation;

	ItemGrade grade;

public:
	bool isActive = false;

	// 아이템의 능력치
	int maxHp;
	int hp;
	int maxMp;
	int mp;
	int damage;
	float damageScale;
	int criticalChance;
	int criticalDamage;
	int defence;
	float attackSpeed;
	float moveSpeed;

public:
	Item() = default;
	explicit Item(Vector2 dropPos);
	virtual ~Item();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	// Get
	ObRect* GetCollider() { return collider; };
	ItemGrade GetGrade() { return grade; }
};

