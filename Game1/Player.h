#pragma once
enum class PlayerState
{
	IDLE,
	RUN,
	JUMP,
	CROUCH,
	CROUCH_DOWN,
};

class Player
{
protected:
	ObRect* collider;
	ObImage* idle;
	ObImage* run;
	ObImage* jump;
	ObImage* crouch;

	PlayerState  state;
	Vector2		dir;
	Vector2		lastPos;

	float		speed;
	float		jumpSpeed;
	float		jumpTime;

	int			jumpCount;
	int			jumpCountMax;

public:
	float		gravity;
	bool		onFloor;
	bool		onWall;
	bool		onWallSlide;
	bool		isLanding;
	//bool		isJumping;
	
public:
	Player();
	virtual ~Player();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	void GoBack();
	void Control();
	void OnFloorAction();
	void OnWallAction();
	void OnWallSlideAction();


	// Get
	PlayerState GetState() { return state; }
	ObRect* GetCollider() { return collider; };
	Vector2 GetFoot();
	Vector2 GetHead();
	Vector2 GetDirection() { return dir; }

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};