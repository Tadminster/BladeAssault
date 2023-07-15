#pragma once
enum class PlayerState
{
	IDLE,
	RUN,
	JUMP
};

class Player
{
	ObRect*		collider;
	ObImage*	idle;
	ObImage*	run;
	ObImage*	jump;

	PlayerState  state;
	Vector2		dir;
	Vector2		lastPos;

	float		speed;
	float		jumpSpeed;
	float		jumpTime;

public:
	bool		onFloor;
	bool		isJumping;

public:
	Player();
	virtual ~Player();
	void Init();
	void Update();
	void Render();

	void GoBack();
	void Control();

	ObRect* GetCollider() { return collider; };
	Vector2 GetFoot();

	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }

};