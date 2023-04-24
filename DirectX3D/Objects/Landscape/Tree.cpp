#include "Framework.h"

Tree::Tree()
	:ModelInstancing("Tree")
{
    for (float x = 0; x < SIZE; x++)
    {
        Transform* transform = Add();
        transform->Pos() = { 0.0f, 0.0f, 0.0f };
        transform->Scale() = { Scale().x * 0.01f, Scale().y * Random(0.005f, 0.015f), Scale().z * 0.01f };
        transform->Load();
    }
}

Tree::~Tree()
{
}

void Tree::Update()
{
    ModelInstancing::Update();
}

void Tree::Render()
{
    ModelInstancing::Render();
}

void Tree::GUIRender()
{
    ImGui::SliderInt("ID", &instanceID, 0, 100);

    ModelInstancing::GUIRender();
}
