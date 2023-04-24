#include "Framework.h"

Skybox::Skybox(wstring textureFile)
{
    material->SetShader(L"Landscape/Skybox.hlsl");

    cubeMap = Texture::Add(textureFile);

    rasterizerState[0] = new RasterizerState();
    rasterizerState[1] = new RasterizerState();
    rasterizerState[1]->FrontCounterClockwise(true);

    depthStencilState[0] = new DepthStencilState();
    depthStencilState[1] = new DepthStencilState();
    depthStencilState[1]->DepthEnable(false);

    colorBuffer = new ColorBuffer();
}

Skybox::~Skybox()
{
    delete rasterizerState[0];
    delete rasterizerState[1];

    delete depthStencilState[0];
    delete depthStencilState[1];

    delete colorBuffer;
}

void Skybox::Update()
{
    //ChangeNight();
}

void Skybox::Render()
{
    cubeMap->PSSet(10);
    colorBuffer->SetPS(1);

    rasterizerState[1]->SetState();
    depthStencilState[1]->SetState();

    Sphere::Render();

    rasterizerState[0]->SetState();
    depthStencilState[0]->SetState();
}

void Skybox::ChangeNight()
{
    int time = Environment::Get()->GetDayTime();
    lightTime += DELTA;
    
    if (time >= 7 &&
        time <= 18)
    {
        cubeMap = Texture::Add(L"Textures/Landscape/Sky.dds");
    }
    else
    {
        cubeMap = Texture::Add(L"Textures/Landscape/Night.dds");
    }

    /*if (time >= 7 &&
       time <= 18)
   {
       if (time <= 12)
           timeValue = (lightTime + 12.0f) / 24.0f;
       else
           timeValue = (24.0f - lightTime) / 24.0f;

       timeValue = Clamp(0.5f, 1.0f, timeValue);

       colorBuffer->Get() = { timeValue, timeValue , timeValue , 1.0f };
       
       cubeMap = Texture::Add(L"Textures/Landscape/Sky.dds");
   }
   else
   {
       if( time >= 19 || time == 0 )
           timeValue = (lightTime + 12.0f) / 24.0f;
       else if (time > 0 &&
           time < 7)
           timeValue = (24.0f - lightTime) / 24.0f;

       timeValue = Clamp(0.5f, 1.0f, timeValue);

       colorBuffer->Get() = { timeValue, timeValue , timeValue , 1.0f };

       cubeMap = Texture::Add(L"Textures/Landscape/Night.dds");
   }

    if (lightTime > 12.0f)
        lightTime = 0.0f;*/
}
