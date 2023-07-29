#pragma once
class DamageText
{
private:
	ObImage* text;

	Vector2 spawnPos;
	string damage;
	float traveledDistance;
	float speed;
	float range;

public:
	// @brief 데미지 표시 생성자
	// @param spawnPos 데미지 표시 생성 위치
	// @param value 데미지 표시할 값
	// @param value 0~9: 해당 숫자, 10: ,(콤마)
	// @param color 데미지 표시할 색상
	// @param color 0: 빨강, 1: 주황, 2: 노랑, 3: 초록, 4: 파랑, 5: 보라
	DamageText(Vector2 spawnPos, int value, int color);
	~DamageText();
	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	// @brief 탄이 이동한 거리가 range를 넘었는지 확인
	bool                hasTraveledTooFar() const;
};

