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
	//시계프레임
public:
	Player();
	virtual ~Player();
	void Init(Vector2 spawn);
	void Control();
	void Update() override;
	void Render() override;
	void LookTarget(Vector2 target);
	/*float GetHp() { return gauge2->scale.x; }
	Bullet* GetBullet(int i) const { return bullet[i]; }
	void Damage(float dmg) { gauge2->scale.x -= dmg; }*/
	//const Bullet** GetBullet() { return bullet; }
};

//class Sloider : public Player
//{
//
//};