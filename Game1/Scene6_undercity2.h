#pragma once
class Scene6_undercity2 : public Scene_proto
{
private:
	ObRect* nextMap;

	Vector2			startPostion;

public:
	Scene6_undercity2();
	~Scene6_undercity2();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void SummonMonster() override;
};