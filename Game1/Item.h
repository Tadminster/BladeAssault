#pragma once

enum ItemGrade
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
	int		maxHp;					// 최대 체력
	int		hp;						// 체력
	int		maxMp;					// 최대 마나
	int		mp;						// 마나

	int		damage;					// 모든 기본 공격력
	float	damageScale;			// 모든 공격력 스케일
	float	normalDamageScale;		// 일반 공격력 스케일
	float	skillDamageScale;		// 스킬 공격력 스케일
	float	chargingDamageScale;	// 차징 공격력 스케일
	float	fullLifeDamageScale;	// 체력이 100%일 때 공격력 스케일


	int		criticalChance;			// 치명타 확률
	int		criticalDamage;			// 치명타 피해량
	int		defence;				// 방어력
	float	attackSpeed;			// 공격 속도
	float	moveSpeed;				// 이동 속도

	float skillCooldownScale;		// 스킬 쿨타임 스케일
	float dashCooldownScale;		// 대쉬 쿨타임 스케일

	bool	isLowLifeNoManaCost;	// 낮은 생명력일 때 마나 소모 없음

public:
	Item();
	virtual ~Item();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	// Get
	ObRect* GetCollider() { return collider; };
	ItemGrade GetGrade() { return grade; }

	// Set
	void SetPosition(Vector2 pos) { collider->SetWorldPos(pos); }
};

