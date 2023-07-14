#include "framework.h"
#include "MapManager.h"

MapManager::~MapManager()
{
    for (auto i = scenes.begin();
        i != scenes.end(); i++)
    {
        SafeDelete(i->second);
    }
    scenes.clear();
}

bool MapManager::AddScene(string key, Scene* value)
{
    auto iter = scenes.find(key);

    if (iter != scenes.end())
    {
        return false;
    }
    scenes[key] = value;

    return true;
}

bool MapManager::DeleteScene(string key)
{
    auto iter = scenes.find(key);

    if (iter == scenes.end())
    {
        return false;
    }

    SafeDelete(iter->second);
    scenes.erase(iter);

    return true;
}

Scene* MapManager::ChangeScene(string key, float changingTime)
{
    Scene* temp = GetScene(key);

    if (temp)
    {
        nextScene = temp;
        this->changingTime = changingTime;

        if (changingTime <= 0.0f)
        {
            isChanging = true;
            //¾À ºÒ·¯¿Ã ¶§ 
            SafeRelease(currentScene);
            //¾À ¹Ù²ð ¶§
            nextScene->Init();
        }
    }
    return temp;
}

Scene* MapManager::GetScene(string key)
{
    auto iter = scenes.find(key);

    if (iter == scenes.end())
    {
        return nullptr;
    }

    return iter->second;
}

Scene* MapManager::GetCurrentScene()
{
    return currentScene;
}

void MapManager::Release()
{
    if (currentScene)currentScene->Release();
}

void MapManager::Update()
{
    if (changingTime > 0.0f)
    {
        changingTime -= DELTA;

        if (changingTime <= 0.0f)
        {
            isChanging = true;
            SafeRelease(currentScene);
            nextScene->Init();
        }
    }


    if (isChanging)
    {
        currentScene = nextScene;
        isChanging = false;
    }
    currentScene->Update();
}

void MapManager::LateUpdate()
{
    if (isChanging)return;
    currentScene->LateUpdate();
}

void MapManager::Render()
{
    if (isChanging)return;
    currentScene->Render();
}

void MapManager::ResizeScreen()
{
    if (isChanging || !currentScene)return;
    currentScene->ResizeScreen();
}
