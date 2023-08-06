#pragma once
class ratmotan : public Monster
{
private:

public:
	ratmotan();
	//ratmotan(Vector2 spawnPos);
	~ratmotan();
	void Update() override;
	void Render() override;
	void Attack() override;
};

