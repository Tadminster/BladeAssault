#pragma once


enum class PlayerState
{
	IDLE,
	WALK,
	ROLL,
	//DAMAGE
};


class Player : public ObRect
{
	class Bullet* bullet[30];
	ObImage* walk;
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
	void Update() override;
	void Render() override;
	void LookTarget(Vector2 target);
	Vector2 GetFoot();
	void GoBack();
};

//class Sloider : public Player
//{
//
//};