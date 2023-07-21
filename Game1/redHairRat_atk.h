#pragma once
class redHairRat_atk : public Projectile
{
private:
	//class ObCircle* explosionCol;

public:
	redHairRat_atk(
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

