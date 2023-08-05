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
	int		maxHp				= 0;		// 최대 체력
	int		hp					= 0;		// 체력
	int		maxMp				= 0;		// 최대 마나
	int		mp					= 0;		// 마나

	int		damage				= 0;		// 모든 기본 공격력
	float	damageScale			= 0.0f;		// 모든 공격력 스케일
	float	normalDamageScale	= 0.0f;		// 일반 공격력 스케일
	float	skillDamageScale	= 0.0f;		// 스킬 공격력 스케일
	float	chargingDamageScale = 0.0f;		// 차징 공격력 스케일
	float	chargingTimeScale	= 0.0f;		// 차징 시간 스케일
	float	fullLifeDamageScale = 0.0f;		// 체력이 100%일 때 공격력 스케일

	float 	damageRedution		= 0.0f;		// 피해 감소
	int		dodgeChance			= 0;		// 회피율

	int		criticalChance		= 0;		// 치명타 확률
	int		criticalDamage		= 0;		// 치명타 피해량
	int		defence				= 0;		// 방어력
	float	attackSpeed			= 0.0f;		// 공격 속도

	float	moveSpeed			= 0.0f;		// 이동 속도
	float   moveSpeedScale		= 0.0f;		// 이동 속도 스케일

	float	skillCooldownScale	= 0.0f;		// 스킬 쿨타임 스케일
	float	dashCooldownScale	= 0.0f;		// 대쉬 쿨타임 스케일

	bool	hasCandle			= false;	// 캔들 보유 여부
	bool    hasFirstAidKit		= false;	// 응급 처치 키트 보유 여부
	bool	hasCactus			= false;	// 선인장 보유 여부

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

