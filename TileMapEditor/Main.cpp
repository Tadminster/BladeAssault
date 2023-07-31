#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	tileSize[0] = Int2(20, 20);
	tileSize[1] = Int2(20, 20);
	tileSize[2] = Int2(20, 20);

	tileMap[0] = new ObTileMap();
	tileMap[1] = new ObTileMap();
	tileMap[2] = new ObTileMap();

	//tileMap[0]->file = "scene2_hankroom_0.txt";
	//tileMap[1]->file = "scene2_hankroom_1.txt";
	//tileMap[2]->file = "scene2_hankroom_2.txt";
	
	//tileMap[0]->file = "scene3_jazzbar_0.txt";
	//tileMap[1]->file = "scene3_jazzbar_1.txt";
	//tileMap[2]->file = "scene3_jazzbar_2.txt";
	
	//tileMap[0]->file = "scene4_armory_0.txt";
	//tileMap[1]->file = "scene4_armory_1.txt";
	//tileMap[2]->file = "scene4_armory_2.txt";

	//tileMap[0]->file = "scene5_undercity1_0.txt";
	//tileMap[1]->file = "scene5_undercity1_1.txt";
	//tileMap[2]->file = "scene5_undercity1_2.txt";

	//tileMap[0]->file = "scene6_undercity2_0.txt";
	//tileMap[1]->file = "scene6_undercity2_1.txt";
	//tileMap[2]->file = "scene6_undercity2_2.txt";

	tileMap[0]->file = "scene7_undercity3_0.txt";
	tileMap[1]->file = "scene7_undercity3_1.txt";
	tileMap[2]->file = "scene7_undercity3_2.txt";

	tileMap[0]->Load();
	tileMap[1]->Load();
	tileMap[2]->Load();

	tileMap[0]->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
	tileMap[1]->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
	tileMap[2]->color = Color(0.5f, 0.5f, 0.5f, 0.5f);

	brushState[0] = 0;
	brushState[1] = 0;
	brushState[2] = 0;

	LineX = new ObRect();
	LineX->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	LineX->pivot = OFFSET_N;
	LineX->scale.x = 20000.0f;
	LineX->scale.y = 5.0f;

	LineY = new ObRect();
	LineY->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
	LineY->pivot = OFFSET_N;
	LineY->scale.x = 5.0f;
	LineY->scale.y = 20000.0f;

	brushImgIdx = 0;
	brushFrame.x = 0;
	brushFrame.y = 0;
	brushColor = Color(0.5f, 0.5f, 0.5f, 0.5f);

	layer = 0;
}

Main::~Main()
{
}

void Main::Init()
{
}

void Main::Release()
{

}

void Main::Update()
{
	if (ImGui::BeginMenu("\xef\x87\x86" " File"))
	{

		//if (ImGui::MenuItem("\xef\x85\x9b" " New", "Ctrl + N"))
		//{
		//	//tileMap[layer]->file = "tileMap[layer]_defalut.txt";
		//	tileMap[0]->Load();
		//	tileMap[1]->Load();
		//}



		if (ImGui::MenuItem("\xef\x83\x87" " Save", "Ctrl + S"))
		{
			tileMap[0]->Save();
			tileMap[1]->Save();
			tileMap[2]->Save();
		}

		if (ImGui::MenuItem("\xef\x81\xbc" " Open", "Ctrl + O"))
		{
			//tileMap[layer]->file = "tileMap[layer]1.txt";
			tileMap[0]->Load();
			tileMap[1]->Load();
			tileMap[2]->Load();
			//OpenProject(lua, assetManager, renderer, canvas, tileSize);
		}
		if (ImGui::MenuItem("Exit"))
			exit(1);

		ImGui::EndMenu();
	}

	ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());

	if (INPUT->KeyPress('W'))
	{
		CAM->position += UP * 400.0f * DELTA;
	}
	if (INPUT->KeyPress('S'))
	{
		CAM->position += DOWN * 400.0f * DELTA;
	}
	if (INPUT->KeyPress('A'))
	{
		CAM->position += LEFT * 400.0f * DELTA;
	}
	if (INPUT->KeyPress('D'))
	{
		CAM->position += RIGHT * 400.0f * DELTA;
	}


	
	// TileSize
	tileSize[layer].x = tileMap[layer]->GetTileSize().x;
	tileSize[layer].y = tileMap[layer]->GetTileSize().y;
	if (ImGui::DragInt2("TileSize", (int*)&tileSize[layer], 1.0f, 1, 1000))
	{
		tileMap[layer]->ResizeTile(tileSize[layer]);
	}

	// TileScale
	if (ImGui::InputFloat("TileScaleX", (float*)&tileMap[layer]->scale.x, 1.0f, 200.0f))
	{
	}
	if (ImGui::InputFloat("TileScaleY", (float*)&tileMap[layer]->scale.y, 1.0f, 200.0f))
	{
	}
 

	// TilePos
	for (int i = 0; i < 3; i++)
	{
		TilePos[layer].x = tileMap[layer]->GetWorldPos().x;
		TilePos[layer].y = tileMap[layer]->GetWorldPos().y;
	}

	if (ImGui::DragInt2("TilePos", (int*)&TilePos[layer], 1.0f, -1000, 1000))
	{
		tileMap[layer]->SetWorldPos(Vector2(TilePos[layer].x, TilePos[layer].y));
	}

	for (int i = 0; i < 4; i++)
	{
		string str = "Texture" + to_string(i);
		if (GUI->FileImGui(str.c_str(), str.c_str(),
			".jpg,.png,.bmp,.dds,.tga", "../Contents/Images"))
		{
			string path = ImGuiFileDialog::Instance()->GetFilePathName();
			Utility::Replace(&path, "\\", "/");
			size_t tok = path.find("/Images/") + 8;
			path = path.substr(tok, path.length());
			SafeDelete(tileMap[layer]->tileImages[i]);
			wstring wImgFile = L"";
			wImgFile.assign(path.begin(), path.end());
			tileMap[layer]->tileImages[i] = new ObImage(wImgFile);
			break;
		}
		if (i < 3)
		{
			ImGui::SameLine();
		}
	}

	//ImgIdx
	if (ImGui::InputInt("ImgIdx", &brushImgIdx))
	{
		brushImgIdx = Utility::Saturate(brushImgIdx, 0, 3);

		if (not tileMap[layer]->tileImages[brushImgIdx])
		{
			brushImgIdx = 0;
		}
	}
	//maxFrame
	ImGui::InputInt2("maxFrame", (int*)&tileMap[layer]->tileImages[brushImgIdx]->maxFrame);

	// Layer
	const char* itemsLayer[] = { "0", "1", "2" };
	static int item_current = 0;
	if (ImGui::Combo("Layer", &item_current, itemsLayer, IM_ARRAYSIZE(itemsLayer)))
	{
		layer = item_current;
	}

	Int2 MF = tileMap[layer]->tileImages[brushImgIdx]->maxFrame;
	ImVec2 size;
	size.x = 300.0f / (float)MF.x;
	size.y = 300.0f / (float)MF.y;
	ImVec2 LT, RB;
	int index = 0;
	for (UINT i = 0; i < MF.y; i++)
	{
		for (UINT j = 0; j < MF.x; j++)
		{
			if (j != 0)
			{
				//같은줄에 배치
				ImGui::SameLine();
			}
			//텍스쳐 좌표
			LT.x = 1.0f / MF.x * j;
			LT.y = 1.0f / MF.y * i;
			RB.x = 1.0f / MF.x * (j + 1);
			RB.y = 1.0f / MF.y * (i + 1);

			ImGui::PushID(index);
			if (ImGui::ImageButton((void*)tileMap[layer]->tileImages[brushImgIdx]->GetSRV()
				, size, LT, RB))
			{
				brushFrame.x = j;
				brushFrame.y = i;
			}
			index++;
			ImGui::PopID();
		}
	}


	//TileState
	const char* itemsState[] = { "NONE", "WALL", "WALLSIDE", "FLOOR", "DOOR", "TRAP", "WATER"};
	if (ImGui::BeginListBox("TileState"))
	{
		for (int n = 0; n < IM_ARRAYSIZE(itemsState); n++)
		{
			const bool is_selected = (brushState[layer] == n);
			if (ImGui::Selectable(itemsState[n], is_selected))
				brushState[layer] = n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	//TileColor
	ImGui::ColorEdit4("TileColor", (float*)&brushColor, ImGuiColorEditFlags_PickerHueWheel);



	if (INPUT->KeyPress(VK_RBUTTON))
	{
		Int2 Idx;
		//?
		if (tileMap[layer]->WorldPosToTileIdx(INPUT->GetWorldMousePos(), Idx))
		{
			tileMap[layer]->SetTile(Idx, brushFrame, brushImgIdx, brushState[layer], brushColor);
		}

	}

	tileMap[0]->Update();
	tileMap[1]->Update();
	tileMap[2]->Update();
	LineX->Update();
	LineY->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	tileMap[0]->Render();
	tileMap[1]->Render();
	tileMap[2]->Render();

	LineX->Render();
	LineY->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"MapEditor");
    app.SetInstance(instance);
	app.InitWidthHeight(1600.f,900.0f);
    app.background = Color(0.3, 0.3, 0.3);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}