#pragma once


class Player_kill : public Player
{
private:

public:
	Player_kill();
	~Player_kill() override;
	void Init() override;
	void Update() override;
	void Render() override;
};