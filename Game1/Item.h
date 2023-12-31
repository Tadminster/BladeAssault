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

	int		criticalChance		= 0;		// 치명타 확률
	float	criticalDamage		= 0;		// 치명타 피해량 스케일
	int		defence				= 0;		// 방어력

	int		damage				= 0;		// 모든 기본 공격력
	float	damageScale			= 0.0f;		// 모든 공격력 스케일
	float	normalDamageScale	= 0.0f;		// 일반 공격력 스케일
	float	skillDamageScale	= 0.0f;		// 스킬 공격력 스케일
	float	chargingDamageScale = 0.0f;		// 차징 공격력 스케일
	float	chargingTimeScale	= 0.0f;		// 차징 시간 스케일
	float	fullLifeDamageScale = 0.0f;		// 체력이 100%일 때 공격력 스케일
	float	lowLifeDamageScale	= 0.0f;		// 체력이 30% 이하일 때 공격력 스케일
	float   attackRangeScale	= 0.0f;		// 공격 범위 스케일

	float 	damageRedution		= 0.0f;		// 피해 감소
	int		dodgeChance			= 0;		// 회피율

	float	attackSpeed			= 0.0f;		// 공격 속도
	float	attackSpeedScale	= 0.0f;		// 공격 속도 스케일

	float	moveSpeed			= 0.0f;		// 이동 속도
	float   moveSpeedScale		= 0.0f;		// 이동 속도 스케일

	float	skillCooldownScale	= 0.0f;		// 스킬 쿨타임 스케일
	float	dashCooldownScale	= 0.0f;		// 대쉬 쿨타임 스케일

	bool	hasCandle			= false;	// 캔들 소유 여부 (낮은 체력일 때 스킬 사용시 마나 소모가 없음)
	bool    hasFirstAidKit		= false;	// 구급상자 소유 여부 (낮은 체력일 때 HP 재생)
	bool	hasCactus			= false;	// 선인장 소유 여부 (피격시 데미지 반사)
	bool	hasSyringe			= false;	// 주사기 소유 여부 (피격시 HP 재생)
	bool	hasHeatedClub		= false;	// 히팅클럽 소유 여부 (낮은 체력일 때 데미지 증가)

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

