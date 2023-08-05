#pragma once
class player_damageReflection : public Projectile
{
private:
	//class ObCircle* explosionCol;

public:
	player_damageReflection(
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

