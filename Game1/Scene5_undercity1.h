#pragma once
class Scene5_undercity1 : public Scene_proto
{
private:
	ObRect* nextMap;

	Vector2			startPostion;

public:
	Scene5_undercity1();
	~Scene5_undercity1();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void SummonMonster() override;
};