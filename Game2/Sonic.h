#pragma once

enum class SonicState
{
	RUN,
	JUMP,
	SPIN
};

class Sonic
{
private:
	ObImage*	run;
	ObImage*	spin;
	ObRect*		col;
	SonicState  state;
	float		gravity;
	bool		isFlying;
	int			jumpCount;
	float		overPower;

	float			trialTime;
	deque<GameObject*>	playerTrail;


public:
	int         hp;
	int			score;
	Sonic();
	~Sonic();

	void Init();
	void Update();
	void Render();
	Vector2 GetPos() { return col->GetWorldPos(); };
	ObRect* GetCollider() { return col; };
	void OnFloor();
	void Damage()
	{ 
		if (overPower <= 0.0f)
		{
			hp--;  overPower = 1.5f;
		}
	}
};

