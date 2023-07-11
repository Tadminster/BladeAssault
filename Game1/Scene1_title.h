#pragma once
class Scene1_title : public Scene
{
private:
	class ObImage* bg_title;
	//class ObImage* skin_btnStart;
	//class ObImage* skin_btnExit;
	class ObRect* btnStart;
	class ObRect* btnExit;

	RECT textBox_start;
	RECT textBox_exit;

public:
	Scene1_title();
	~Scene1_title();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;


	void OnClick();
};

