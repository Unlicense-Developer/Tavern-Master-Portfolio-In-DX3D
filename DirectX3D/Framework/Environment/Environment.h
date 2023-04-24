#pragma once

class Environment : public Singleton<Environment>
{
private:
    friend class Singleton;

    const float TIME_INTERVAL = 4.0f;

    Environment();
    ~Environment();

public:

    void Update();
    void GUIRender();

    void Set();
    void PostSet();

    void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
    void SetPerspective();
    void SetOrthographic();

    LightBuffer::Light* AddLight(int& candleIndex);

    Camera* GetMainCamera() { return mainCamera; }
    Matrix GetProjection() { return perspective; }
    LightBuffer::Light* GetLight(UINT index) { return &lightBuffer->Get().lights[index]; }
    
    void RemoveLight(UINT index);

    void DayTimeLapse();
    int GetDayTime() { return dayTime; }

private:
    void CreateProjection();
    void CreateState();

private:
    MatrixBuffer* projectionBuffer;       
    LightBuffer* lightBuffer;
    ViewBuffer* uiViewBuffer;
    
    SamplerState* samplerState;
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];
    DepthStencilState* depthStencilState[2];

    Camera* mainCamera;

    D3D11_VIEWPORT viewport;

    bool isWireMode = false;
    int dayTime = 7;
    float time = 0.0f;

    Matrix perspective;
    Matrix orthographic;
};