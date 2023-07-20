#pragma once
class kill_barehand_atk : public Projectile
{
private:
	//class ObCircle* explosionCol;

public:
	kill_barehand_atk(
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

