#include "stdafx.h"
#include "HUD.h"
#include "Player.h"
#include "Player_kill.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "redHairRat.h"
#include "Scene3_jazzBar.h"

Scene3_jazzBar::Scene3_jazzBar()
{
	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	for (int i = 0; i < 2; i++)
		nextMap[i] = new ObRect();
	stairLeft = new ObRect();
	stairRight = new ObRect();
}

Scene3_jazzBar::~Scene3_jazzBar()
{
	for (int i = 0; i < 3; i++)
		delete[] tileMap[i];

	for (int i = 0; i < 2; i++)
		delete nextMap[i];

	delete stairLeft;
}

void Scene3_jazzBar::Init()
{

	tileMap[0]->file = "scene3_jazzbar_0.txt";
	tileMap[1]->file = "scene3_jazzbar_1.txt";
	tileMap[2]->file = "scene3_jazzbar_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	nextMap[0]->SetWorldPos(Vector2(4300, 1850));
	nextMap[1]->SetWorldPos(Vector2(4300, 1150));
	for (int i = 0; i < 2; i++)
	{
		nextMap[i]->scale = Vector2(100, 100);
		nextMap[i]->color = Vector4(0.5, 0.5, 0.5, 0.3);
		nextMap[i]->isFilled = true;
	}

	// 계단(왼쪽)
	stairLeft->SetWorldPos(Vector2(3075, 1175));
	stairLeft->scale = Vector2(50, 50);
	stairLeft->color = Vector4(0.5, 0.5, 0.5, 0.3);
	stairLeft->isFilled = true;
	
	// 계단(오른쪽)
	stairRight->SetWorldPos(Vector2(4025, 1125));
	stairRight->scale = Vector2(50, 50);
	stairRight->color = Vector4(0.5, 0.5, 0.5, 0.3);
	stairRight->isFilled = true;

	startPostion = Vector2(2820, 1850);

	GM->player->SetPosition(startPostion);

	GM->monster->AddMonster(new redHairRat(Vector2(3500, 1800)));
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
	ImGui::Text("onWallside : %d\n", GM->player->onWallSlide);

	// 카메라 위치
	CAM->position.x = GM->player->GetCollider()->GetWorldPos().x;
	CAM->position.y = GM->player->GetCollider()->GetWorldPos().y + 200;

	// 다음	맵으로 이동
	for (auto& next : nextMap)
	{
		if (next->Intersect(GM->player->GetCollider()))
		{
			SCENE->ChangeScene("sc4");
		}
	}

	// 계단(왼쪽)
	if (stairLeft->Intersect(GM->player->GetCollider()))
	{
		if (GM->player->GetDirection() == LEFT && GM->player->GetState() == PlayerState::RUN)
		{
			GM->player->GetCollider()->MoveWorldPos(UP * 200 * DELTA);
		}
	}

	// 계단(오른쪽)
	if (stairRight->Intersect(GM->player->GetCollider()))
	{
		if (GM->player->GetDirection() == LEFT && GM->player->GetState() == PlayerState::RUN)
		{
			GM->player->GetCollider()->MoveWorldPos(UP * 200 * DELTA);
		}
	}

	for (auto& map : tileMap)
		map->Update();
	nextMap[0]->Update();
	nextMap[1]->Update();
	stairLeft->Update();
	stairRight->Update();

	GM->monster->Update();
	GM->player->Update();
	GM->hud->Update();
}

void Scene3_jazzBar::LateUpdate()
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

void Scene3_jazzBar::Render()
{
	tileMap[0]->Render();
	tileMap[1]->Render();
	if (GM->DEBUG_MODE)
	{
		tileMap[2]->Render();
		nextMap[0]->Render();
		nextMap[1]->Render();
		stairLeft->Render();
		stairRight->Render();
	}

	GM->monster->Render();
	GM->player->Render();
	GM->hud->Render();
}

void Scene3_jazzBar::ResizeScreen()
{
	GM->hud->Init();
}

bool Scene3_jazzBar::OnFloor()
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

bool Scene3_jazzBar::OnWall()
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

bool Scene3_jazzBar::OnWallside()
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