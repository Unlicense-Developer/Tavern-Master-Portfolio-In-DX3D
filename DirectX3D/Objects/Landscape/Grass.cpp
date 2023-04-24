#include "Framework.h"

Grass::Grass()
    :ModelInstancing("Grass")
{
    for (float x = 0; x < SIZE; x++)
    {
        Transform* transform = Add();
        transform->Pos() = { 0.0f, 0.0f, 0.0f };
        transform->Load();
    }
}

Grass::~Grass()
{
}

void Grass::Update()
{
    ModelInstancing::Update();
}

void Grass::Render()
{
    ModelInstancing::Render();
}

void Grass::GUIRender()
{
    ImGui::SliderInt("ID", &instanceID, 0, 100);

    ModelInstancing::GUIRender();
}
