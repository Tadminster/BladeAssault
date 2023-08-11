#pragma once
class shockwaveGenerator : public Monster
{
private:
	float lifeTime{0};

public:
	shockwaveGenerator();
	~shockwaveGenerator();
	void Update() override;
	void Render() override;
	void Attack() override;

	bool isDead() const override;
};

