#pragma once
class Scene7_undercity3 : public Scene_proto
{
private:
	ObRect* nextMap;

	Vector2			startPostion;

public:
	Scene7_undercity3();
	~Scene7_undercity3();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void SummonMonster() override;
};