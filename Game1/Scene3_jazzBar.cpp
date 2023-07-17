#include "stdafx.h"
#include "Player.h"
#include "Player_kill.h"
#include "Scene3_jazzBar.h"

Scene3_jazzBar::Scene3_jazzBar()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	lightCeiling = new ObImage(L"hankroom_light.png");
	lightRoom = new ObImage(L"squareGlow.png");
}

Scene3_jazzBar::~Scene3_jazzBar()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];

	delete lightCeiling;
	delete lightRoom;
}

void Scene3_jazzBar::Init()
{

	tileMap[0]->file = "scene3_jazzbar_0.txt";
	tileMap[1]->file = "scene3_jazzbar_1.txt";
	tileMap[2]->file = "scene3_jazzbar_2.txt";

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

	startPostion = Vector2(2820, 1810);
	floorPostion = Vector2(0, 600);

	isLightDown = true;
	isLightOn = true;
	LightOffTime = 0.0f;


	GM->player->Init();
	GM->player->SetPosition(startPostion);
}

void Scene3_jazzBar::Release()
{
}

void Scene3_jazzBar::Update()
{
	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());
	ImGui::Text("player_posX : %f\n", GM->player->GetCollider()->GetWorldPos().x);
	ImGui::Text("player_posY : %f\n", GM->player->GetCollider()->GetWorldPos().y);

	ImGui::Text("onFloor : %d\n", GM->player->onFloor);
	ImGui::Text("onWall : %d\n", GM->player->onWall);

	// ī�޶� ��ġ
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	for (auto& map : tileMap)
		map->Update();
	lightRoom->Update();
	lightCeiling->Update();
	GM->player->Update();
}

void Scene3_jazzBar::LateUpdate()
{
	// ��Ÿ�� �浹 ó��

	


	
	// ���� �ε�������
	if (OnWall())
	{
		// ���� �پ��ִ� ����
		GM->player->onWall = true;
		// �������̸�
		if (GM->player->GetState() == PlayerState::JUMP)
			GM->player->OnWallSlideAction();
		// �������� �ƴϸ�
		else 
			GM->player->OnWallAction();
	}
	else GM->player->onWall = false;

	// �ٴ�Ÿ�� �浹 ó��
	//if (OnFloor()) GM->player->OnFloorAction();
	//else GM->player->onFloor = false;


	// generator a function Player colliders and wall colliders no longer move forward when they collide
	/*if (GM->player->onWall)
	{
		if (GM->player->GetState() == PlayerState::WALLSLIDE)
		{
			if (GM->player->GetCollider()->GetWorldPos().x < GM->player->GetWallCollider()->GetWorldPos().x)
			{
				GM->player->GetCollider()->SetWorldPos(Vector2(GM->player->GetWallCollider()->GetWorldPos().x - 50, GM->player->GetCollider()->GetWorldPos().y));
			}
			else if (GM->player->GetCollider()->GetWorldPos().x > GM->player->GetWallCollider()->GetWorldPos().x)
			{
				GM->player->GetCollider()->SetWorldPos(Vector2(GM->player->GetWallCollider()->GetWorldPos().x + 50, GM->player->GetCollider()->GetWorldPos().y));
			}
		}
		else if (GM->player->GetState() == PlayerState::WALL)
		{
			if (GM->player->GetCollider()->GetWorldPos().x < GM->player->GetWallCollider()->GetWorldPos().x)
			{
				GM->player->GetCollider()->SetWorldPos(Vector2(GM->player->GetWallCollider()->GetWorldPos().x - 50, GM->player->GetCollider()->GetWorldPos().y));
			}
			else if (GM->player->GetCollider()->GetWorldPos().x > GM->player->GetWallCollider()->GetWorldPos().x)
			{
				GM->player->GetCollider()->SetWorldPos(Vector2(GM->player->GetWallCollider()->GetWorldPos().x + 50, GM->player->GetCollider()->GetWorldPos().y));
			}
		}
	}*/
}

void Scene3_jazzBar::Render()
{
	tileMap[0]->Render();
	tileMap[1]->Render();
	if (GM->DEBUG_MODE) tileMap[2]->Render();

	if (isLightOn)
	{
		lightRoom->Render();
		lightCeiling->Render();
	}

	GM->player->Render();
}

void Scene3_jazzBar::ResizeScreen()
{
}

bool Scene3_jazzBar::OnFloor()
{
	Int2 playerlndex;
	if (tileMap[2]->WorldPosToTileIdx(GM->player->GetFoot(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_FLOOR)
		{
			return true;
		}
	}
	return false;
}

bool Scene3_jazzBar::OnWall()
{
	Int2 playerlndex;
	// TOP �浹 üũ
	if (tileMap[2]->WorldPosToTileIdx(GM->player->GetHead(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALL)
		{
			return true;
		}
	}
	// BOT �浹 üũ
	if (tileMap[2]->WorldPosToTileIdx(GM->player->GetFoot(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALL)
		{
			return true;
		}
	}


	return false;
}
