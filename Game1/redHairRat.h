#pragma once
class redHairRat : public Monster
{
private:

public:
	redHairRat();
	redHairRat(Vector2 spawnPos);
	~redHairRat();
	//void Init(Vector2 spawnPos) override;
	void Update() override;
	void Render() override;
	void Attack() override;
};

