#include "stdafx.h"
#include "HUD.h"
#include "Creature.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "DamageDisplayManager.h"
#include "EffectManager.h"
#include "Scene_proto.h"
#include "Scene2_inGame.h"

Scene2_inGame::Scene2_inGame()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();
	nextMap = new ObRect();

	lightCeiling = new ObImage(L"hankroom_light.png");
	lightRoom = new ObImage(L"squareGlow.png");
	
	GM->hud = new HUD();
	GM->player = new Player_kill();
	GM->monster = new MonsterManager();
	GM->damageDP = new DamageDisplayManager();
	GM->fx = new EffectManager();

	tileMap[0]->file = "scene2_hankroom_0.txt";
	tileMap[1]->file = "scene2_hankroom_1.txt";
	tileMap[2]->file = "scene2_hankroom_2.txt";

	lightCeiling->SetWorldPos(Vector2(935, 770));
	lightCeiling->maxFrame.x = 1;
	lightCeiling->maxFrame.y = 1;
	lightCeiling->scale.x = lightCeiling->imageSize.x / lightCeiling->maxFrame.x * 1.6;
	lightCeiling->scale.y = lightCeiling->imageSize.y / lightCeiling->maxFrame.y * 1.6;
	lightCeiling->reverseLR = true;
	lightCeiling->color.w = 0.5;

	lightRoom->pivot = OFFSET_LB;
	lightRoom->SetWorldPos(Vector2(573, 515));
	lightRoom->maxFrame.x = 1;
	lightRoom->maxFrame.y = 1;
	lightRoom->scale.x = lightRoom->imageSize.x / lightRoom->maxFrame.x * 4.5;
	lightRoom->scale.y = lightRoom->imageSize.y / lightRoom->maxFrame.y * 2.4;
	lightRoom->color.w = 0.5;

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	nextMap->pivot = OFFSET_LB;
	nextMap->SetWorldPos(Vector2(1275, 550));
	nextMap->scale = Vector2(50, 150);
	nextMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	nextMap->isFilled = true;

	startPostion = Vector2(850, 550);

	isLightDown = true;
	isLightOn = true;
	LightOffTime = 0.0f;
}

Scene2_inGame::~Scene2_inGame()
{
	//Scene_proto::~Scene_proto();
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];
	delete nextMap;

	delete lightCeiling;
	delete lightRoom;
}

void Scene2_inGame::Init()
{
	GM->player->Init();
	GM->player->SetPosition(startPostion);
}

void Scene2_inGame::Release()
{
}

void Scene2_inGame::Update()
{

	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());
	ImGui::Text("player_posX : %f\n", GM->player->GetCollider()->GetWorldPos().x);
	ImGui::Text("player_posY : %f\n", GM->player->GetCollider()->GetWorldPos().y);

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 전등 빛
	{
		// 불빛 세기 조절
		if (lightCeiling->color.w == 0.5f)
			isLightDown = true;
		else if (lightCeiling->color.w <= 0.35f)
			isLightDown = false;

		float randomBrightness = RANDOM->Float(0.0f, 0.3f);
		if (isLightDown)
			lightCeiling->color.w = max(0.35f, lightCeiling->color.w - randomBrightness * DELTA);
		else
			lightCeiling->color.w = min(0.5f, lightCeiling->color.w + randomBrightness * DELTA);

		// 전등 ON/OFF 조절
		if (isLightOn)
		{
			int randomLightOff = RANDOM->Int(0, 3500);
			if (!randomLightOff) isLightOn = false;
		}
		else
		{
			int randomLightOn = RANDOM->Int(0, 2000);
			if (!randomLightOn) isLightOn = true;
		}

		lightRoom->color.w = lightCeiling->color.w * 0.03;
	}


	if (nextMap->Intersect(GM->player->GetCollider()))
	{
		if (localtime > 1.0f)
			SCENE->ChangeScene("sc3");
	}


	for (auto& map : tileMap)
		map->Update();
	lightRoom->Update();
	lightCeiling->Update();
	nextMap->Update();
	GM->monster->Update();
	GM->player->Update();
	GM->hud->Update();

	Scene_proto::Update();
}

void Scene2_inGame::LateUpdate()
{
	Scene_proto::LateUpdate();
}

void Scene2_inGame::Render()
{
	tileMap[0]->Render();
	tileMap[1]->Render();
	if (GM->DEBUG_MODE)
	{
		tileMap[2]->Render();
		nextMap->Render();
	}
	
	if (isLightOn)
	{
		lightRoom->Render();
		lightCeiling->Render();
	}
	GM->monster->Render();
	GM->player->Render();
	GM->hud->Render();

	Scene_proto::Render();
}

void Scene2_inGame::ResizeScreen()
{
	GM->hud->Init();
}