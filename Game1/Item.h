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

	// �������� �ɷ�ġ
	int		maxHp				= 0;		// �ִ� ü��
	int		hp					= 0;		// ü��
	int		maxMp				= 0;		// �ִ� ����
	int		mp					= 0;		// ����

	int		damage				= 0;		// ��� �⺻ ���ݷ�
	float	damageScale			= 0.0f;		// ��� ���ݷ� ������
	float	normalDamageScale	= 0.0f;		// �Ϲ� ���ݷ� ������
	float	skillDamageScale	= 0.0f;		// ��ų ���ݷ� ������
	float	chargingDamageScale = 0.0f;		// ��¡ ���ݷ� ������
	float	chargingTimeScale	= 0.0f;		// ��¡ �ð� ������
	float	fullLifeDamageScale = 0.0f;		// ü���� 100%�� �� ���ݷ� ������

	float 	damageRedution		= 0.0f;		// ���� ����
	int		dodgeChance			= 0;		// ȸ����

	int		criticalChance		= 0;		// ġ��Ÿ Ȯ��
	int		criticalDamage		= 0;		// ġ��Ÿ ���ط�
	int		defence				= 0;		// ����
	float	attackSpeed			= 0.0f;		// ���� �ӵ�

	float	moveSpeed			= 0.0f;		// �̵� �ӵ�
	float   moveSpeedScale		= 0.0f;		// �̵� �ӵ� ������

	float	skillCooldownScale	= 0.0f;		// ��ų ��Ÿ�� ������
	float	dashCooldownScale	= 0.0f;		// �뽬 ��Ÿ�� ������

	bool	hasCandle			= false;	// ĵ�� ���� ����
	bool    hasFirstAidKit		= false;	// ���� óġ ŰƮ ���� ����
	bool	hasCactus			= false;	// ������ ���� ����

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

