#include "Framework.h"

Candle::Candle(string name)
	:Structure(name)
{
    candleLight = Environment::Get()->AddLight(candleLightIndex);
    candleLight->type = 1;
    candleLight->range = LIGHT_RANGE;
    candleLight->color = CANDLELIGHT_COLOR;

    candleFlame = new Sprite(L"Textures/Effect/Candleflame.png", 0.1, 0.11, 1, 1, true);
}

Candle::~Candle()
{
    delete candleFlame;
}

void Candle::Update()
{
    //candleLight->pos = Pos();

    if (UIManager::Get()->GetStructureEditor()->GetSampleModel() == this)
        candleLight->pos = Pos();

    if (flamePos == Vector3(0, 0, 0))
    {
        if (Rot().y == -XM_PIDIV2)
        {
            flamePos = { 0.28f, 0.3f, 0 };
            candleLight->pos = Pos() + Vector3(2, 0, 0);
        }
        else if (Rot().y == XM_PIDIV2)
        {
            flamePos = { -0.28f, 0.3f, 0 };
            candleLight->pos = Pos() + Vector3(-2, 0, 0);
        }
        else if (Rot().y == XM_PIDIV2 * 2.0f)
        {
            flamePos = { 0, 0.3f, 0.28f };
            candleLight->pos = Pos() + Vector3(0, 0, 2);
        }
        else
        {
            flamePos = { 0, 0.3f, -0.28f };
            candleLight->pos = Pos() + Vector3(0, 0, -2);
        }
    }

    Structure::Update();

    if(!candleFlame->IsActive() && name == "Wall_Candle")
        candleFlame->Play(Pos() + flamePos + Vector3(Random(0.0f, 0.01f), Random(0.0f, 0.01f), Random(0.0f, 0.01f)));

    //candleFlame->Play(Vector3());

    candleFlame->Update();
}

void Candle::Render()
{
    Structure::Render();
    candleFlame->Render();
}

void Candle::GUIRender()
{
    Structure::GUIRender();
}
