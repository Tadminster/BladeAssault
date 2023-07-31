#pragma once
class Scene3_jazzBar : public Scene_proto
{
private:
	ObRect*			nextMap[2];
	ObRect*			stairLeft;
	ObRect*			stairRight;

public:
	Scene3_jazzBar();
	~Scene3_jazzBar();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void SummonMonster() override;
};