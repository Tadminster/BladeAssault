#include "stdafx.h"
#include "Sonic.h"

Sonic::Sonic()
{
	run = new ObImage(L"run.bmp");
	run->scale.x = run->imageSize.x * 2.0f / 4.0f;
	run->scale.y = run->imageSize.y * 2.0f;
	run->maxFrame.x = 4;
	run->pivot = OFFSET_B;

	spin = new ObImage(L"spin.bmp");
	spin->scale.x = spin->imageSize.x * 2.0f / 5.0f;
	spin->scale.y = spin->imageSize.y * 2.0f;
	spin->maxFrame.x = 5;
	spin->pivot = OFFSET_B;

	col = new ObRect();
	col->scale = run->scale;
	col->scale.x -= 20.0f;
	col->isFilled = false;
	col->pivot = OFFSET_B;
	col->hasAxis = true;
	spin->SetParentRT(*col);
	run->SetParentRT(*col);
	
	//col->rotation.y = PI;

	score = 0;
	hp = 3;
	
	trialTime = 0.0f;
	playerTrail.resize(10);
	//for (int i = 0; i < 30; i++)
	for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
	{
		*it = nullptr;
	}


}

Sonic::~Sonic()
{
	delete spin;
	delete run;
	delete col;
}

void Sonic::Init()
{
	col->SetWorldPos(Vector2(-300.0f, -200.0f));
	state = SonicState::RUN;
	run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	jumpCount = 0;
	gravity = 0.0f;
	CAM->position.x = 0.0f;
	score = 0;
	hp = 3;
}

void Sonic::Update()
{
	col->MoveWorldPos(RIGHT * 300.0f * DELTA);
	CAM->position += RIGHT * 300.0f * DELTA;
	gravity += 300.0f * DELTA;
	col->MoveWorldPos(DOWN * gravity * DELTA);

	//한번에 한 조건문만 만족하도록 else 묶기
	if (state == SonicState::RUN)
	{
		//spin->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		col->scale.y = run->scale.y;

		//run -> jump
		if (INPUT->KeyDown(VK_UP))
		{
			isFlying = true;
			state = SonicState::JUMP;
			gravity = -300.0f;
			col->MoveWorldPos(DOWN * gravity * DELTA);
			col->Update();
			spin->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
			jumpCount = 1;
		}
		//run -> spin
		if (INPUT->KeyDown(VK_DOWN))
		{
			state = SonicState::SPIN;
			spin->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}
	else if (state == SonicState::SPIN)
	{
		
		col->scale.y = spin->scale.y;

		//spin -> run
		if (INPUT->KeyUp(VK_DOWN))
		{
			state = SonicState::RUN;
		}

	}
	else if (state == SonicState::JUMP)
	{
		col->scale.y = spin->scale.y;
		
		if (INPUT->KeyDown(VK_UP)and jumpCount == 1)
		{
			gravity = -300.0f;
			col->MoveWorldPos(DOWN * gravity * DELTA);
			col->Update();
			jumpCount++;
		}

		//jump -> run
		if (not isFlying)
		{
			//col->SetWorldPosY(-200.0f);
			state = SonicState::RUN;
		}
	}


	//cout << "SCORE:" <<score<< endl;
	//cout << "HP:" <<hp<< endl;

	col->Update();
	run->Update();
	spin->Update();

	if (overPower > 0.0f)
	{
		overPower -= DELTA;
		//                          -1 ~ 0
		run->color.w = RANDOM->Float(0.0f, 0.5f);
		spin->color.w = RANDOM->Float(0.0f, 0.5f);
	}
	else
	{
		run->color.w = 0.5f;
		spin->color.w =0.5f;
	}


	if (TIMER->GetTick(trialTime, 0.2))
	{
		delete playerTrail.front();
		playerTrail.pop_front();
		ObImage* temp;
		if (state == SonicState::RUN)
		{
			temp = new ObImage(L"run.bmp");
			temp->scale.x = temp->imageSize.x * 2.0f / 4.0f;
			temp->scale.y = temp->imageSize.y * 2.0f;
			temp->maxFrame.x = 4;
			temp->pivot = OFFSET_B;
			temp->SetWorldPos(run->GetWorldPos());
			temp->frame.x = run->frame.x;
			playerTrail.push_back(temp);
		}
		else if(state == SonicState::SPIN)
		{
			ObRect* temp;
			temp = new ObRect();
			temp->scale.x = run->scale.x;
			temp->scale.y = run->scale.y;
			temp->pivot = OFFSET_B;
			temp->SetWorldPos(run->GetWorldPos());
			playerTrail.push_back(temp);
		}
		else
		{
			temp = new ObImage(L"spin.bmp");
			temp->scale.x = temp->imageSize.x * 2.0f / 5.0f;
			temp->scale.y = temp->imageSize.y * 2.0f;
			temp->maxFrame.x = 5;
			temp->pivot = OFFSET_B;
			temp->SetWorldPos(spin->GetWorldPos());
			temp->frame.x = spin->frame.x;
			playerTrail.push_back(temp);
		}
		//temp->color.w = RANDOM->Float(0.0f, 0.5f);
		
	}
	for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
	{
		if (*it)
		(*it)->Update();
	}
}

void Sonic::Render()
{
	for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
	{
		if(*it)
		(*it)->Render();
	}
	col->Render();

	switch (state)
	{
	case SonicState::RUN:
		run->Render();
		break;
	case SonicState::SPIN: case SonicState::JUMP:
		spin->Render();
	}
	
}

void Sonic::OnFloor()
{
	isFlying = false;
	gravity = 0.0f;
	col->SetWorldPosY(-200.0f);
	col->Update();
}
