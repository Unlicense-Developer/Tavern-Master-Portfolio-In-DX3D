#include "Framework.h"

Environment::Environment()
{
    CreateProjection();
    CreateState();

    mainCamera = new Camera();
    lightBuffer = new LightBuffer();
    uiViewBuffer = new ViewBuffer();    
}

Environment::~Environment()
{
    delete projectionBuffer;  
    delete lightBuffer;
    delete uiViewBuffer;

    delete mainCamera;

    delete samplerState;
    delete rasterizerState[0];
    delete rasterizerState[1];    
    delete blendState[0];
    delete blendState[1];
}

void Environment::Update()
{
    if (KEY_DOWN(VK_F1))
        isWireMode = !isWireMode;

    if (KEY_DOWN(VK_F2))
        Collider::RenderOnOff();

    mainCamera->Update();
    //DayTimeLapse();
}

void Environment::GUIRender()
{
    if (ImGui::TreeNode("Environment"))
    {
        mainCamera->GUIRender();
        ImGui::Text("LightOption");

        if (ImGui::Button("Add"))
            lightBuffer->Get().lightCount++;

        for (UINT i = 0; i < lightBuffer->Get().lightCount; i++)
        {
            string name = "Light_" + to_string(i);
            if (ImGui::TreeNode(name.c_str()))
            {
                LightBuffer::Light& light = lightBuffer->Get().lights[i];

                ImGui::Checkbox("Active", (bool*)&light.active);

                const char* list[] = { "Directional", "Point", "Spot", "Capsule" };
                ImGui::Combo("Type", &light.type, list, 4);

                ImGui::ColorEdit3("Color", (float*)&light.color, ImGuiColorEditFlags_PickerHueWheel);
                ImGui::SliderFloat3("Dir", (float*)&light.direction, -1, 1);

                ImGui::DragFloat3("Pos", (float*)&light.pos);
                ImGui::SliderFloat("Range", &light.range, 1, 1000);

                ImGui::SliderFloat("Inner", &light.inner, 0, light.outer);
                ImGui::SliderFloat("Outer", &light.outer, light.inner, 180.0f);
                ImGui::SliderFloat("Length", &light.length, 1, 1000);

                ImGui::TreePop();
            }
        }
        
        ImGui::ColorEdit3("AmbientLight", (float*)&lightBuffer->Get().ambientLight, ImGuiColorEditFlags_PickerHueWheel);
        ImGui::ColorEdit3("AmbientCeil", (float*)&lightBuffer->Get().ambientCeil, ImGuiColorEditFlags_PickerHueWheel);
        ImGui::TreePop();
    }    
}

void Environment::Set()
{
    SetViewport();
    SetPerspective();

    mainCamera->SetView();

    if (isWireMode)
        rasterizerState[1]->SetState();
    else
        rasterizerState[0]->SetState();

    blendState[0]->SetState();
    depthStencilState[0]->SetState();

    lightBuffer->SetPS(0);
}

void Environment::PostSet()
{
    uiViewBuffer->SetVS(1);
    SetOrthographic();

    blendState[1]->SetState();
    depthStencilState[1]->SetState();
}

void Environment::SetViewport(UINT width, UINT height)
{
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    DC->RSSetViewports(1, &viewport);
}

void Environment::SetPerspective()
{
    projectionBuffer->Set(perspective);
    projectionBuffer->SetVS(2);
    projectionBuffer->SetPS(2);
}

void Environment::SetOrthographic()
{
    projectionBuffer->Set(orthographic);
    projectionBuffer->SetVS(2);
    projectionBuffer->SetPS(2);
}

LightBuffer::Light* Environment::AddLight(int& candleIndex)
{
    candleIndex = lightBuffer->Get().lightCount++;

    return GetLight(candleIndex);
}

void Environment::CreateProjection()
{
    orthographic = XMMatrixOrthographicOffCenterLH(
        0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);
    
    perspective = XMMatrixPerspectiveFovLH(XM_PIDIV4,
        (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 5000.0f);    

    projectionBuffer = new MatrixBuffer();    
}

void Environment::CreateState()
{
    samplerState = new SamplerState();
    samplerState->SetState();

    rasterizerState[0] = new RasterizerState();
    rasterizerState[1] = new RasterizerState();
    rasterizerState[1]->FillMode(D3D11_FILL_WIREFRAME);

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->Alpha(true);

    depthStencilState[0] = new DepthStencilState();
    depthStencilState[1] = new DepthStencilState();
    depthStencilState[1]->DepthEnable(false);
}

void Environment::RemoveLight(UINT index)
{
    for (int i = 0; i < lightBuffer->Get().lightCount - index + 1; i++) // 옮기는 횟수
    {
        lightBuffer->Get().lights[index] = lightBuffer->Get().lights[index + 1];
    }

    lightBuffer->Get().lightCount--;
}

void Environment::DayTimeLapse()
{
    time += DELTA;

    if (time >= TIME_INTERVAL)
    {
        dayTime++;

        if (DAYLIGHT->direction.y == 1.0f) // pm 7시 ~ am 6시
            DAYLIGHT->direction.x -= 2.0f / 12.0f;
        else // am 7시 ~ pm 6시
            DAYLIGHT->direction.x += 2.0f / 12.0f;

        if (DAYLIGHT->direction.x >= 1.0f)
        {
            DAYLIGHT->active = false;
            DAYLIGHT->direction.y = 1.0f;
        }
        else if (DAYLIGHT->direction.x <= -1.0f)
        {
            DAYLIGHT->active = true;
            DAYLIGHT->direction.y = -1.0f;
        }

        if (dayTime == 24)
            dayTime = 0;

        time = 0.0f;
    }
}
