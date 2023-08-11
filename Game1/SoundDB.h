#pragma once
class SoundDB
{
private:

public:
	SoundDB();
	~SoundDB();
	void Init();
	void Release(); //해제
	void Update();
	void LateUpdate();//갱신
	void Render();
};

