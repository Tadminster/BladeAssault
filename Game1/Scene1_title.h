#pragma once
class Scene1_title : public Scene
{
private:
	class ObImage* titleLogo;
	class ObImage* titleBg;
	//class ObImage* skin_btnStart;
	//class ObImage* skin_btnExit;
	class ObRect* btnStart;
	class ObRect* btnExit;

	RECT textBox_start;
	RECT textBox_exit;

	bool onBtn_1{ false };
	bool onBtn_2{ false };

	// Ÿ��Ʋ �ΰ� �ִϸ��̼�
	float titleAnimTime = 0.0f;

public:
	Scene1_title();
	~Scene1_title();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
	
	void ResizeText(int type);
	void OnClick();
};

