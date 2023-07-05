#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	tileMap[0] = new ObTileMap();
	tileMap[0]->file = "map1.txt";
	tileMap[0]->Load();
	tileMap[0]->color = Color(0.5f, 0.5f, 0.5f, 0.5f);

	tileMap[1] = new ObTileMap();
	tileMap[1]->file = "map2.txt";
	tileMap[1]->Load();
	tileMap[1]->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
	tileSize = Int2(20, 20);

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
	brushState = 0;

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
		}

		if (ImGui::MenuItem("\xef\x81\xbc" " Open", "Ctrl + O"))
		{
			//tileMap[layer]->file = "tileMap[layer]1.txt";
			tileMap[0]->Load();
			tileMap[1]->Load();
			//OpenProject(lua, assetManager, renderer, canvas, tileSize);
		}

		//if (ImGui::MenuItem("\xef\x83\x87" " Save As..", "Ctrl + Shift + S"))
		//{
			// Get the file path from the file dialog
			//std::string filename = mFileDialog->SaveFile();

			// Check to see if we got the filepath from the dialog
			// The user may have cancelled the save 
			//if (filename == "")
				//return;

			// Change the filename to the dialog path 
			//mFileName = filename;
			// Call the save project function 
			//mFileLoader->SaveProject(mFileName, mLoadedTilesets, mTilesetLocations, canvas->GetWidth(), canvas->GetHeight(), tileSize);
		//}

		if (ImGui::MenuItem("Exit"))
			exit(1);

		ImGui::EndMenu();
	}

	ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());

	if (INPUT->KeyPress('W'))
	{
		CAM->position += UP * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('S'))
	{
		CAM->position += DOWN * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('A'))
	{
		CAM->position += LEFT * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('D'))
	{
		CAM->position += RIGHT * 300.0f * DELTA;
	}

	//TileSize
	if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 100))
	{
		tileMap[0]->ResizeTile(tileSize);
		tileMap[1]->ResizeTile(tileSize);
	}

	// TileScale
	//ImGui::SliderFloat2("TileScale", (float*)&tileMap[layer]->scale, 1.0f, 200.0f);
	if (ImGui::InputFloat("TileScale", (float*)&tileMap[0]->scale.x, 1.0f, 200.0f))
	{
		tileMap[0]->scale.y = tileMap[0]->scale.x;
		tileMap[1]->scale.x = tileMap[0]->scale.x;
		tileMap[1]->scale.y = tileMap[0]->scale.x;
	}

	// TilePos
	Vector2 pos = tileMap[layer]->GetWorldPos();
	if (ImGui::SliderFloat2("TilePos", (float*)&pos, -1000.0f, 1000.0f))
	{
		tileMap[0]->SetWorldPos(pos);
		tileMap[1]->SetWorldPos(pos);
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

	//"감바스";
	//L"감바스";
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
	const char* items[] = { "0", "1" };
	static int item_current = 0;
	if (ImGui::Combo("Layer", &item_current, items, IM_ARRAYSIZE(items)))
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
	ImGui::SliderInt("TileState", &brushState, TILE_NONE, TILE_SIZE - 1);
	//TileColor
	ImGui::ColorEdit4("TileColor", (float*)&brushColor, ImGuiColorEditFlags_PickerHueWheel);
	


	if (INPUT->KeyPress(VK_LBUTTON))
	{
		Int2 Idx;
		//?
		if (tileMap[layer]->WorldPosToTileIdx(INPUT->GetWorldMousePos(), Idx))
		{
			tileMap[layer]->SetTile(Idx, brushFrame, brushImgIdx, brushState, brushColor);
		}

	}

	tileMap[0]->Update();
	tileMap[1]->Update();
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