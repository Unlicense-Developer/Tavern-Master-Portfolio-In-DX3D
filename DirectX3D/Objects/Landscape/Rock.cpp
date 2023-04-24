#include "Framework.h"

Rock::Rock(string name)
    :ModelInstancing(name)
{
    for (float x = 0; x < SIZE; x++)
    {
        Transform* transform = Add();
        transform->Pos() = { 0.0f, 0.0f, 0.0f };
        transform->Load();
    }
}

Rock::~Rock()
{
}

void Rock::Update()
{
    ModelInstancing::Update();
}

void Rock::Render()
{
    ModelInstancing::Render();
}

void Rock::GUIRender()
{
    ImGui::SliderInt("ID", &instanceID, 0, 100);

    ModelInstancing::GUIRender();
}
