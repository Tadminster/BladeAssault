#pragma once

class Main : public Scene
{
private:
	class Scene1_title* sc1_title;
	class Scene2_inGame* sc2_inGame;
	class Scene3_jazzBar* sc3_jazzBar;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
