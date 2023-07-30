#pragma once
class greenHairRat : public Monster
{
private:

public:
	greenHairRat();
	greenHairRat(Vector2 spawnPos);
	~greenHairRat();
	void Update() override;
	void Render() override;
	void Attack() override;
};

