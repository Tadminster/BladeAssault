#pragma once
enum class PlayerState
{
	IDLE,
	RUN,
};

class Player
{
	ObRect* collider;
	ObImage* idle;
	ObImage* run;

	PlayerState  state;
	float		speed;
	Vector2		dir;

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