#pragma once
class orangeHairRat : public Monster
{
private:

public:
	orangeHairRat();
	orangeHairRat(Vector2 spawnPos);
	~orangeHairRat();
	void Update() override;
	void Render() override;
	void Attack() override;
};

