#include "stdafx.h"
#include "PathTrail.h"

PathTrail::PathTrail()
{
    pathLine.resize(0);
    for (auto it = pathLine.begin(); it != pathLine.end(); it++)
    {
        (*it) = new ObRect();
    }
}

PathTrail::~PathTrail()
{
    for (auto it = pathLine.begin(); it != pathLine.end(); it++)
    {
        delete (*it);
    }
}

void PathTrail::Init()
{
    for (auto it = pathLine.begin(); it != pathLine.end(); it++)
    {
        (*it)->pivot = OFFSET_B;
        (*it)->scale.x = 50;
        (*it)->scale.y = 5;
        (*it)->color = Vector4(0.5, 1, 0.75, 0.5);
    }
}

void PathTrail::Update()
{


    for (auto it = pathLine.begin(); it != pathLine.end(); it++)
    {
        (*it)->Update();
    }
}

void PathTrail::Render()
{
    for (auto it = pathLine.begin(); it != pathLine.end(); it++)
    {
        (*it)->Render();
    }
}

void PathTrail::Resize(int value, vector<Tile*>& way)
{
    // 기존 잔상을 다 지우고
    for (auto it = pathLine.begin(); it != pathLine.end(); it++)
    {
        delete (*it);
    }

    // 새로운 사이즈와 객체 할당
    pathLine.resize(value);
    int i = 0;
    for (auto it = pathLine.begin(); it != pathLine.end(); it++)
    {
        (*it) = new ObRect();
        (*it)->SetWorldPos(way[i++]->Pos);
        //(*it)->pivot = OFFSET_B;
        (*it)->scale.x = 50;
        (*it)->scale.y = 50;
        (*it)->color = Vector4(0.5, 1, 0.75, 0.2);
    }
}
