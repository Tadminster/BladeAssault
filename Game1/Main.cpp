#include "stdafx.h"
#include "Scene_proto.h"
#include "Scene1_title.h"
#include "Scene2_inGame.h"
#include "Scene3_jazzBar.h"
#include "Scene4_armory.h"
#include "Scene5_undercity1.h"
#include "Scene6_undercity2.h"
#include "Scene7_undercity3.h"
#include "Scene8_undercity4.h"
#include "Main.h"

Main::Main()
{
	sc1_title = new Scene1_title();
	sc2_inGame = new Scene2_inGame();
	sc3_jazzBar = new Scene3_jazzBar();
	sc4_armory = new Scene4_armory();
	sc5_undercity1 = new Scene5_undercity1();
	sc6_undercity2 = new Scene6_undercity2();
	sc7_undercity3 = new Scene7_undercity3();
	sc8_undercity4 = new Scene8_undercity4();
}

Main::~Main()
{
	SCENE->~SceneManager();
}

void Main::Init()
{
	SCENE->AddScene("sc1", sc1_title);
	SCENE->AddScene("sc2", sc2_inGame);
	SCENE->AddScene("sc3", sc3_jazzBar);
	SCENE->AddScene("sc4", sc4_armory);
	SCENE->AddScene("sc5", sc5_undercity1);
	SCENE->AddScene("sc6", sc6_undercity2);
	SCENE->AddScene("sc7", sc7_undercity3);
	SCENE->AddScene("sc8", sc8_undercity4);
	SCENE->ChangeScene("sc1");
}

void Main::Release()
{

}

void Main::Update()
{
	if (GM->DEBUG_MODE)
	{
		ImGui::Text("mouse_x, %f\n", INPUT->GetWorldMousePos().x);
		ImGui::Text("mouse_y, %f\n", INPUT->GetWorldMousePos().y);
	}

	GM->Update();
	SCENE->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();
}

void Main::Render()
{
	SCENE->Render();
}

void Main::ResizeScreen()
{
	SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game1");
	app.SetInstance(instance);
	app.InitWidthHeight(1200.0f, 800.0f);
	app.background = Color(0.3, 0.3, 0.3);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}