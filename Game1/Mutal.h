#pragma once

class Unit
{
protected:
	Vector2 moveDir;
	Vector2 target;
public:
	ObCircle* col;
	virtual void Move(Vector2 TargetPos);
	virtual void Attack(Vector2 TargetPos);
	virtual void SetPos(Vector2 TargetPos);
	virtual void Spread(Unit* targetOb);
};





class Mutal : public Unit
{
private:
	ObImage* img;
	int dir[16];
	float moveSpeed;
	int index;
public:
	Mutal();

	void Update();
	void Render();

	void Move(Vector2 TargetPos) override;
};

