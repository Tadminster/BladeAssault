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
	int		maxHp;					// �ִ� ü��
	int		hp;						// ü��
	int		maxMp;					// �ִ� ����
	int		mp;						// ����

	int		damage;					// ��� �⺻ ���ݷ�
	float	damageScale;			// ��� ���ݷ� ������
	float	normalDamageScale;		// �Ϲ� ���ݷ� ������
	float	skillDamageScale;		// ��ų ���ݷ� ������
	float	chargingDamageScale;	// ��¡ ���ݷ� ������
	float	fullLifeDamageScale;	// ü���� 100%�� �� ���ݷ� ������


	int		criticalChance;			// ġ��Ÿ Ȯ��
	int		criticalDamage;			// ġ��Ÿ ���ط�
	int		defence;				// ����
	float	attackSpeed;			// ���� �ӵ�
	float	moveSpeed;				// �̵� �ӵ�

	float skillCooldownScale;		// ��ų ��Ÿ�� ������
	float dashCooldownScale;		// �뽬 ��Ÿ�� ������

	bool	isLowLifeNoManaCost;	// ���� ������� �� ���� �Ҹ� ����

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

