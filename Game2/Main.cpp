#include "stdafx.h"
#include "Main.h"
#include "Sonic.h"
#include "Bono.h"
#include "Score.h"

Main::Main()
{
	bg = new ObImage(L"Oven1.png");
	
	//bg2 = new ObImage(L"bono.jpg");
	bg2 = new ObImage(L"Oven2.png");
	//bg2->ChangeSampler(D3D11_FILTER_MIN_MAG_MIP_POINT,
	//	D3D11_TEXTURE_ADDRESS_CLAMP);

	for (int i = 0; i < BONOMAX; i++)
	{
		bono[i] = new Bono();
		
	}

	for (int i = 0; i < SCOREMAX; i++)
	{
		score[i] = new Score();
		score[i]->soundKey = "Coin" + to_string(i);
		SOUND->AddSound("Coin.wav", score[i]->soundKey);
	}
	
	sonic = new Sonic();

	bg->scale.x = app.GetWidth();
	bg->scale.y = app.GetHeight();

	bg2->scale.x = app.GetWidth();
	bg2->scale.y = app.GetHeight();

	bg->imageSize.x *= 2.0f;
	bg->imageSize.y *= 2.0f;

	bg2->imageSize.x *= 2.0f;
	bg2->imageSize.y *= 2.0f;

	bg->uv.z = app.GetWidth() / bg->imageSize.x;
	bg2->uv.z = app.GetWidth() / bg2->imageSize.x;


	bg->space = SPACE::SCREEN;
	bg2->space = SPACE::SCREEN;
	SOUND->AddSound("FireBall.wav","FireBall");
	SOUND->AddSound("GameOver.wav","GameOver",true);

	SOUND->Play("GameOver");

	//투명 이미지출력
}

Main::~Main()
{
	delete bg;
	delete bg2;
	delete sonic;
	TEXTURE->DeleteTexture(L"Oven1.png");
	TEXTURE->DeleteTexture(L"Oven2.png");
	SOUND->DeleteSound("GameOver");
	SOUND->DeleteSound("FireBall");
}
void Main::Init()
{
	//0 ~ 5
	socreSpawnY = 0;
	sonic->Init();
	for (int i = 0; i < BONOMAX; i++)
	{
		bono[i]->Init(Vector2(-500.0 + 100.0f * i, -200.0f), true);
	}
	for (int i = 0; i < SCOREMAX; i++)
	{
		socreSpawnY += RANDOM->Int(-1, 1);
		socreSpawnY = Utility::Saturate(socreSpawnY, 0, 6);
		//-200 ~ 100
		score[i]->Init(Vector2(200.0f + 50.0f * i, -200.0f + socreSpawnY * 50.0f), true);
	}

}

void Main::Release()
{
}

void Main::Update()

{

	if (ImGui::SliderFloat2("screenPos", (float*)&LIGHT->screenPos, -1000, 1000.0f));
	if (ImGui::SliderFloat("radius", &LIGHT->radius, 0.0f, 2000.0f));
	if (ImGui::ColorEdit3("inColor", (float*)&LIGHT->lightColor));
	if (ImGui::ColorEdit3("outColor", (float*)&LIGHT->outColor));
	if (ImGui::Button("select"))
	{
		LIGHT->select = not LIGHT->select;
	}

	LIGHT->screenPos = Utility::WorldToScreen(sonic->GetPos());

	bg->uv.x += DELTA * 100.0f / bg->imageSize.x;
	bg->uv.z += DELTA * 100.0f / bg->imageSize.x;

	bg2->uv.x += DELTA * 300.0f / bg2->imageSize.x;
	bg2->uv.z += DELTA * 300.0f / bg2->imageSize.x;
	if (INPUT->KeyPress(VK_SPACE))
	{
		//초당 한장 지나가는속도 -> 초당 1픽셀 속도 * 300

		

	}
	
		
	bg->Update();
	bg2->Update();
	sonic->Update();

	for (int i = 0; i < BONOMAX; i++)
	{
		bono[i]->Update();
	}
	for (int i = 0; i < SCOREMAX; i++)
	{
		score[i]->Update();
	}


	//cout << sonic->GetPos().y << endl;
}

void Main::LateUpdate()
{
	for (int i = 0; i < SCOREMAX; i++)
	{
		if (CAM->position.x - score[i]->GetPosX() > 600.0f)
		{
			
			socreSpawnY += RANDOM->Int(-1, 1);
			socreSpawnY = Utility::Saturate(socreSpawnY, 0, 6);
			score[i]->Init(Vector2(score[i]->GetPosX() + SCOREMAX * 50.0f, -200.0f + socreSpawnY * 50.0f), true);
		}
		//플레이어랑 부딪혔나요?
		if (score[i]->active)
		{
			if (score[i]->col->Intersect(sonic->GetCollider()))
			{
				sonic->score++;
				score[i]->active = false;
				score[i]->PlaySoundEffect();
				//sonic->Damage();
			}
		}

	}
	//바닥이 화면 밖으로 벗어났을때
	for (int i = 0; i < BONOMAX; i++)
	{
		if (CAM->position.x - bono[i]->GetPosX() > 600.0f)
		{
			bono[i]->Init(Vector2(bono[i]->GetPosX() + 1100.0f, -200.0f),
				RANDOM->Int(0, 5));
		}

		if (bono[i]->active)
		{
			if (bono[i]->col->Intersect(sonic->GetPos()))
			{
				sonic->OnFloor();
			}
		}



	}


	if (sonic->hp <= 0)
	{
		Init();
	}


	// l < x < r    b < y < t

	/*float l = target->GetWorldPivot().x - target->scale.x * 0.5f;
	float r = target->GetWorldPivot().x + target->scale.x * 0.5f;
	float b = target->GetWorldPivot().y - target->scale.y * 0.5f;
	float t = target->GetWorldPivot().y + target->scale.y * 0.5f;*/

	//if (l < INPUT->GetWorldMousePos().x and INPUT->GetWorldMousePos().x < r
	//	and b < INPUT->GetWorldMousePos().y and INPUT->GetWorldMousePos().y < t)
	//if(target->Intersect(INPUT->GetWorldMousePos()))
	//{
	//	/*Vector2  dir = INPUT->GetWorldMousePos() - target->GetWorldPivot();
	//	dir.Normalize();
	//	target->color.x = dir.x;
	//	target->color.y = dir.y;*/
	//	bg->color.x = 1.0f;
	//}
	//else
	//{
	//	bg->color.x = 0.5f;
	//}

	//if (INPUT->KeyDown(VK_LBUTTON))
	//{
	//	onClick = true;
	//	minus = INPUT->GetWorldMousePos();
	//}


	/*if (onClick)
	{
		target->scale.x = abs((minus - INPUT->GetWorldMousePos()).x);
		target->scale.y = abs((minus - INPUT->GetWorldMousePos()).y);
		target->SetWorldPos((minus + INPUT->GetWorldMousePos()) * 0.5f);
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			onClick = false;
		}
	}*/


}

void Main::Render()
{
	RECT rc;
	rc.left = Utility::WorldToScreen(sonic->GetPos()).x -50.0f;
	rc.top = Utility::WorldToScreen(sonic->GetPos()).y-200;
	rc.right = rc.left + 1000;
	rc.bottom = rc.top + 1000;
	DWRITE->RenderText(L"score:" + to_wstring(sonic->score), rc,40.0f
	,L"Arial",Color(0,0,0,1),DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
	

	bg->Render();
	bg2->Render();
	
	for (int i = 0; i < BONOMAX; i++)
	{
		bono[i]->Render();
	}
	for (int i = 0; i < SCOREMAX; i++)
	{
		score[i]->Render();
	}
	sonic->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1000.0f, 640.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}