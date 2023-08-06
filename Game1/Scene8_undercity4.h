#pragma once
class Scene8_undercity4 : public Scene_proto
{
private:
	ObRect* nextMap;

	Vector2			startPostion;

public:
	Scene8_undercity4();
	~Scene8_undercity4();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void SummonMonster() override;
};