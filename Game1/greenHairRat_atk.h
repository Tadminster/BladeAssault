#pragma once
class greenHairRat_atk : public Projectile
{
private:
	float gravity;

public:
	greenHairRat_atk(
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

