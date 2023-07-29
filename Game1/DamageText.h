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
	// @param value 데미지 표시할 값 0~9: number, 10: comma
	// @param color 데미지 표시할 색상 0: white, 1: solid red, 2: red, 3: sky, 4: puple, 5: green 6: yellow
	// @exception param value가 0~10이 아닐 경우 0으로 초기화
	// @exception param color가 0~6이 아닐 경우 0으로 초기화
	DamageText(Vector2 spawnPos, int value, int color = 0);
	~DamageText();
	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	// @brief 탄이 이동한 거리가 range를 넘었는지 확인
	bool                hasTraveledTooFar() const;
};

