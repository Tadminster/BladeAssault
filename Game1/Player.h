#pragma once
enum class PlayerState
{
	IDLE,
	RUN,
	JUMP,
	CROUCH
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
	float		jumpPosY;

public:
	float		gravity;
	bool		onFloor;
	bool		onWall;
	bool		onWallSlide;
	bool		isDown;
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

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};