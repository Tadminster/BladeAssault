#pragma once
class orangeHairRat_atk : public Projectile
{
private:
	//class ObCircle* explosionCol;

public:
	orangeHairRat_atk(
		Vector2 spawnPos,
		Vector2 dir,
		float speed,
		float range,
		float damage,
		int penetration,
		float explosionRange);

	void Update() override;
	void Render() override;
	void AfterEffect() override;
};

