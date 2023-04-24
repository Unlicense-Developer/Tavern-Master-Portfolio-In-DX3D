#pragma once

class Skybox : public Sphere
{
public:
    Skybox(wstring textureFile);
    ~Skybox();

    void Update();
    void Render();

private:
    void ChangeNight();

private:
    Texture* cubeMap;

    RasterizerState* rasterizerState[2];
    DepthStencilState* depthStencilState[2];

    ColorBuffer* colorBuffer;

    float lightTime = 0.0f;
    int time = 7;
    float timeValue = 0.0f;
};