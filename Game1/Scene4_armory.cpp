#include "stdafx.h"
#include "Player.h"
#include "Player_kill.h"
#include "Scene4_armory.h"

Scene4_armory::Scene4_armory()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	nextMap = new ObRect();
	previousMap = new ObRect();
	stair = new ObRect();
}

Scene4_armory::~Scene4_armory()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];
	delete nextMap;
	delete previousMap;
	delete stair;
}

void Scene4_armory::Init()
{
	tileMap[0]->file = "scene4_armory_0.txt";
	tileMap[1]->file = "scene4_armory_1.txt";
	tileMap[2]->file = "scene4_armory_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	previousMap->SetWorldPos(Vector2(550, 600));
	previousMap->scale = Vector2(100, 100);
	previousMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	previousMap->isFilled = true;

	nextMap->SetWorldPos(Vector2(3350, 650));
	nextMap->scale = Vector2(100, 100);
	nextMap->color = Vector4(0.5, 0.5, 0.5, 0.3);
	nextMap->isFilled = true;

	stair->SetWorldPos(Vector2(3225, 575));
	stair->scale = Vector2(50, 50);
	stair->color = Vector4(0.5, 0.5, 0.5, 0.3);
	stair->isFilled = true;

	startPostion = Vector2(600, 600);
	returnPosition = Vector2(600, 600);
	//GM->player->Init();
	GM->player->SetPosition(startPostion);
}

void Scene4_armory::Release()
{
}

void Scene4_armory::Update()
{
	ImGui::Text("FPS : %d\n", (int)TIMER->GetFramePerSecond());
	ImGui::Text("player_posX : %f\n", GM->player->GetCollider()->GetWorldPos().x);
	ImGui::Text("player_posY : %f\n", GM->player->GetCollider()->GetWorldPos().y);

	ImGui::Text("onFloor : %d\n", GM->player->onFloor);
	ImGui::Text("onWall : %d\n", GM->player->onWall);
	ImGui::Text("onWallside : %d\n", GM->player->onWallSlide);

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 이전 맵 이동
	if (previousMap->Intersect(GM->player->GetCollider()))
	{
		SCENE->ChangeScene("sc3");
	}

	// 다음 맵 이동
	if (nextMap->Intersect(GM->player->GetCollider()))
	{
		SCENE->ChangeScene("sc2");
	}


	if (stair->Intersect(GM->player->GetCollider()))
	{
		if (GM->player->GetDirection() == RIGHT && GM->player->GetState() == PlayerState::RUN)
		{
			GM->player->GetCollider()->MoveWorldPos(UP * 200 * DELTA);
		}
	}

	for (auto& map : tileMap)
		map->Update();
	previousMap->Update();
	nextMap->Update();
	stair->Update();
	GM->player->Update();
}

void Scene4_armory::LateUpdate()
{
	// 벽(TILE_WALL)과 부딪쳤으면
	if (OnWall())
	{
		// 바닥에 붙어있는 상태
		GM->player->OnWallAction();
	}
	else GM->player->onWall = false;

	// 벽면(TILE_WALLSIDE)과 부딪쳤으면
	if (OnWallside())
	{
		// 벽에 붙어있는 상태
		GM->player->onWallSlide = true;

		// 점프중이면
		if (GM->player->GetState() == PlayerState::JUMP)
			GM->player->OnWallSlideAction();
		// 점프중이 아니면
		else
			GM->player->GoBack();
	}
	else GM->player->onWallSlide = false;

	// 바닥(TILE_FLOOR)과 부딪쳤으면
	if (OnFloor())
	{
		GM->player->OnFloorAction();
	}
	else GM->player->onFloor = false;
}

void Scene4_armory::Render()
{
	tileMap[0]->Render();
	tileMap[1]->Render();
	if (GM->DEBUG_MODE)
	{
		tileMap[2]->Render();
		previousMap->Render();
		nextMap->Render();
		stair->Render();
	}

	GM->player->Render();
}

void Scene4_armory::ResizeScreen()
{

}

bool Scene4_armory::OnFloor()
{
	// 하강중에만 충돌 체크
	if (GM->player->isLanding)
	{
		Int2 playerlndex;
		if (tileMap[2]->WorldPosToTileIdx(GM->player->GetFoot(), playerlndex))
		{
			if (tileMap[2]->GetTileState(playerlndex) == TILE_FLOOR)
			{
				return true;
			}
		}
	}
	return false;
}

bool Scene4_armory::OnWall()
{
	Int2 playerlndex;
	// TOP 충돌 체크
	if (tileMap[2]->WorldPosToTileIdx(GM->player->GetHead(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALL)
		{
			GM->player->GoBack();
			//return true;
		}
	}
	// BOT 충돌 체크
	if (tileMap[2]->WorldPosToTileIdx(GM->player->GetFoot(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALL)
		{
			return true;
		}
	}

	return false;	
}

bool Scene4_armory::OnWallside()
{
	Int2 playerlndex;
	// TOP 충돌 체크
	if (tileMap[2]->WorldPosToTileIdx(GM->player->GetHead(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALLSIDE)
		{
			return true;
		}
	}
	// BOT 충돌 체크
	if (tileMap[2]->WorldPosToTileIdx(GM->player->GetFoot(), playerlndex))
	{
		if (tileMap[2]->GetTileState(playerlndex) == TILE_WALLSIDE)
		{
			return true;
		}
	}
	return false;
}

