#pragma once

class Main : public Scene
{
private:
	class Scene1_title* sc1_title;
	class Scene2_inGame* sc2_inGame;
	class Scene3_jazzBar* sc3_jazzBar;
	class Scene4_armory* sc4_armory;
	class Scene5_undercity1* sc5_undercity1;
	class Scene6_undercity2* sc6_undercity2;
	class Scene7_undercity3* sc7_undercity3;
	class Scene8_undercity4* sc8_undercity4;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
