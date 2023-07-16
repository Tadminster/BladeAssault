#pragma once
enum class PlayerState
{
	IDLE,
	RUN,
	JUMP
};

class Player
{
protected:
	ObRect* collider;
	ObImage* idle;
	ObImage* run;
	ObImage* jump;

	PlayerState  state;
	Vector2		dir;
	Vector2		lastPos;

	float		speed;
	float		jumpSpeed;
	float		jumpTime;

public:
	float		gravity;
	bool		onFloor;
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


	// Get
	ObRect* GetCollider() { return collider; };
	Vector2 GetFoot();
	Vector2 GetHead();

	// Set
	void	SetPosition(Vector2 position) { collider->SetWorldPos(position); }
};