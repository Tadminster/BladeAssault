#pragma once
class SoundDB
{
private:

public:
	SoundDB();
	~SoundDB();
	void Init();
	void Release(); //����
	void Update();
	void LateUpdate();//����
	void Render();
};

