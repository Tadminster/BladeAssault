#pragma once


enum class PlayerState
{
	IDLE,
	RUN,
	//DAMAGE
};


class Player
{
	ObRect* collider;
	ObImage* idle;
	ObImage* run;
	ObImage* roll;
	ObImage* walk_shadow;
	ObImage* roll_shadow;
	PlayerState  state;
	float		speed;
	Vector2		dir;
	int Frame[8];
	float rollTime;

	Vector2 lastPos;
public:
	Player();
	virtual ~Player();
	void Init(Vector2 spawn);
	void Control();
	void Update();
	void Render();
	void LookTarget(Vector2 target);
	Vector2 GetFoot();
	void GoBack();

	ObRect* GetCollider() { return collider; };
};

//class Sloider : public Player
//{
//
//};